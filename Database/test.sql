
-- Hàm tạo order, đóng gói toàn bộ vào một giao dịch
CREATE OR REPLACE FUNCTION fn_create_order(
    p_customer_id CHAR(8),
    p_payment_method VARCHAR(20),
    p_note TEXT,
    p_cart_items JSONB -- Mảng JSON chứa các sản phẩm, ví dụ: '[{"variant_id": "V0000001", "quantity": 2}, ...]'
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
    -- =================================================================
    -- BƯỚC 1: KIỂM TRA TỒN KHO TRƯỚC KHI LÀM BẤT CỨ ĐIỀU GÌ
    -- =================================================================
    FOR v_item IN SELECT * FROM jsonb_array_elements(p_cart_items)
    LOOP
        -- Gọi hàm fn_check_stock đã tạo trước đó
        v_current_stock := fn_check_stock((v_item->>'variant_id')::CHAR(8));

        -- Nếu số lượng trong kho không đủ so với số lượng đặt mua
        IF v_current_stock < (v_item->>'quantity')::INTEGER THEN
            -- Ném ra một lỗi và dừng toàn bộ hàm. Giao dịch sẽ tự động được rollback.
            RAISE EXCEPTION 'Sản phẩm với variant_id % không đủ số lượng tồn kho. Trong kho chỉ còn: %', v_item->>'variant_id', v_current_stock;
        END IF;
    END LOOP;

    -- =================================================================
    -- BƯỚC 2: TẠO DÒNG "order" CHA
    -- Các giá trị total_amount, final_amount, status sẽ được cập nhật sau
    -- =================================================================
    -- order_id được tạo tự động nhờ DEFAULT đã thiết lập trước đó
    INSERT INTO "order" (customer_id, payment_method, note, status, order_date)
    VALUES (p_customer_id, p_payment_method, p_note, 'PENDING', NOW())
    RETURNING order_id INTO v_new_order_id; -- Lấy order_id vừa tạo và lưu vào biến

    -- =================================================================
    -- BƯỚC 3: THÊM CÁC DÒNG "orderdetail" VÀ GIẢM KHO
    -- =================================================================
    FOR v_item IN SELECT * FROM jsonb_array_elements(p_cart_items)
    LOOP
        -- Lấy giá bán của sản phẩm
        SELECT p.selling_price INTO v_product_price
        FROM variant v
        JOIN product p ON v.product_id = p.product_id
        WHERE v.variant_id = (v_item->>'variant_id')::CHAR(8);

        -- Thêm dòng chi tiết đơn hàng
        -- orderdetail_id được tạo tự động nhờ DEFAULT
        INSERT INTO orderdetail (order_id, variant_id, order_quantity, unit_price, discount, sub_total)
        VALUES (
            v_new_order_id,
            (v_item->>'variant_id')::CHAR(8),
            (v_item->>'quantity')::INTEGER,
            v_product_price,
            0, -- Giả sử discount = 0 cho đơn giản
            v_product_price * (v_item->>'quantity')::INTEGER -- sub_total
        );

        -- Giảm số lượng tồn kho
        UPDATE variant
        SET stock_quantity = stock_quantity - (v_item->>'quantity')::INTEGER
        WHERE variant_id = (v_item->>'variant_id')::CHAR(8);
    END LOOP;

    -- =================================================================
    -- BƯỚC 4: CẬP NHẬT LẠI TỔNG TIỀN CHO ĐƠN HÀNG CHA
    -- =================================================================
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

    -- =================================================================
    -- BƯỚC 5: TRẢ VỀ ID CỦA ĐƠN HÀNG MỚI ĐỂ BACKEND SỬ DỤNG
    -- =================================================================
    RETURN v_new_order_id;
END;
$$ LANGUAGE plpgsql;
