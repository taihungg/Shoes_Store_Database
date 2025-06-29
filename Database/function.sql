-- Hàm check stock của một variant còn bao nhiêu
CREATE OR REPLACE FUNCTION fn_check_stock(p_variant_id CHAR(8))
RETURNS INTEGER AS $$
DECLARE
    v_stock_quantity INTEGER;
BEGIN
    SELECT
        stock_quantity
    INTO
        v_stock_quantity
    FROM
        variant
    WHERE
        variant_id = p_variant_id;
    RETURN COALESCE(v_stock_quantity, 0);
END;
$$ LANGUAGE plpgsql;

-- Hàm tìm kiếm sản phẩm dựa trên một chuỗi đầu vào
CREATE OR REPLACE FUNCTION fn_search_products(p_search_term TEXT)
RETURNS TABLE(product_id CHAR(8)) AS $$
BEGIN
    RETURN QUERY
    SELECT DISTINCT
        p.product_id
    FROM
        product p
    JOIN
        brand b ON p.brand_id = b.brand_id
    LEFT JOIN
        variant v ON p.product_id = v.product_id
    WHERE
        p.product_name ILIKE '%' || p_search_term || '%' OR
        b.brand_name ILIKE '%' || p_search_term || '%' OR
        p.product_description ILIKE '%' || p_search_term || '%' OR
        v.color ILIKE '%' || p_search_term || '%';
END;
$$ LANGUAGE plpgsql;

-- Hàm tạo order, đóng gói toàn bộ vào một giao dịch
CREATE OR REPLACE FUNCTION fn_create_order(
    p_customer_id CHAR(8),
    p_payment_method VARCHAR(20),
    p_note TEXT,
    p_cart_items JSONB -- '[{"variant_id": "V0000001", "quantity": 2}, ...]'
)
RETURNS CHAR(8) AS $$
DECLARE
    v_new_order_id CHAR(8);
    v_item JSONB;
    v_current_stock INTEGER;
    v_product_price DECIMAL(10, 2);
    v_total_amount DECIMAL(10, 2) := 0;
    v_final_amount DECIMAL(10, 2) := 0;
BEGIN
    FOR v_item IN SELECT * FROM jsonb_array_elements(p_cart_items)
    LOOP
        v_current_stock := fn_check_stock((v_item->>'variant_id')::CHAR(8));

        IF v_current_stock < (v_item->>'quantity')::INTEGER THEN
            RAISE EXCEPTION 'Insufficient inventory with variant %. The remaining quantity is %', v_item->>'variant_id', v_current_stock;
        END IF;
    END LOOP;

    INSERT INTO "order" (customer_id, payment_method, note, status, order_date)
    VALUES (p_customer_id, p_payment_method, p_note, 'PENDING', NOW())
    RETURNING order_id INTO v_new_order_id; 

    FOR v_item IN SELECT * FROM jsonb_array_elements(p_cart_items)
    LOOP
        SELECT p.selling_price INTO v_product_price
        FROM variant v
        JOIN product p ON v.product_id = p.product_id
        WHERE v.variant_id = (v_item->>'variant_id')::CHAR(8);

        INSERT INTO orderdetail (order_id, variant_id, order_quantity, unit_price, discount, sub_total)
        VALUES (
            v_new_order_id,
            (v_item->>'variant_id')::CHAR(8),
            (v_item->>'quantity')::INTEGER,
            v_product_price,
            0, 
            v_product_price * (v_item->>'quantity')::INTEGER
        );

        UPDATE variant
        SET stock_quantity = stock_quantity - (v_item->>'quantity')::INTEGER
        WHERE variant_id = (v_item->>'variant_id')::CHAR(8);
    END LOOP;

    SELECT
        SUM(unit_price * order_quantity),
        SUM(sub_total)
    INTO
        v_total_amount, v_final_amount
    FROM orderdetail
    WHERE order_id = v_new_order_id;

    UPDATE "order"
    SET
        total_amount = v_total_amount,
        final_amount = v_final_amount
    WHERE order_id = v_new_order_id;

    RETURN v_new_order_id;
END;
$$ LANGUAGE plpgsql;

-- Hàm tính tổng doanh thu của một brand
CREATE OR REPLACE FUNCTION brand_revenue(bid CHAR(4))
RETURNS NUMERIC AS $$
DECLARE
  revenue NUMERIC;
BEGIN
  SELECT SUM(od.sub_total) INTO revenue
  FROM orderdetail od
  JOIN variant v ON od.variant_id = v.variant_id
  JOIN product p ON v.product_id = p.product_id
  WHERE p.brand_id = bid;
  RETURN COALESCE(revenue, 0);
END;
$$ LANGUAGE plpgsql;

-- Lấy trung bình đánh giá của một sản phẩm 
CREATE OR REPLACE FUNCTION get_average_rating(pid CHAR(8))
RETURNS NUMERIC(2,1) AS $$
DECLARE
    avg_rating NUMERIC(2,1);
BEGIN
    SELECT average_rating INTO avg_rating FROM product WHERE product_id = pid;
    RETURN avg_rating;
END;
$$ LANGUAGE plpgsql;