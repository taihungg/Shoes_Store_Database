CREATE OR REPLACE FUNCTION calculate_orderdetail_prices_trigger_function()
RETURNS TRIGGER AS $$
DECLARE
    v_selling_price NUMERIC(10, 2);
BEGIN
    SELECT p.selling_price
    INTO v_selling_price
    FROM product AS p
    JOIN variant AS v ON p.product_id = v.product_id
    WHERE v.variant_id = NEW.variant_id;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Product variant with ID % not found.', NEW.variant_id;
    END IF;

    NEW.unit_price = v_selling_price;

    NEW.sub_total = NEW.unit_price * NEW.order_quantity * (1 - NEW.discount / 100.00);

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_set_orderdetail_prices
BEFORE INSERT ON orderdetail
FOR EACH ROW
EXECUTE FUNCTION calculate_orderdetail_prices_trigger_function();

CREATE OR REPLACE FUNCTION update_order_totals_function()
RETURNS TRIGGER AS $$
DECLARE
    v_order_id CHAR(8);
    v_total_amount NUMERIC(10, 2);
    v_total_discount_calculated NUMERIC(10, 2);
    v_final_amount_calculated NUMERIC(10, 2);
BEGIN
    IF TG_OP = 'DELETE' THEN
        v_order_id = OLD.order_id;
    ELSE
        v_order_id = NEW.order_id;
    END IF;

    SELECT
        SUM(od.order_quantity * od.unit_price),
        SUM(od.order_quantity * od.unit_price * od.discount / 100.00),
        SUM(od.sub_total)
    INTO
        v_total_amount,
        v_total_discount_calculated,
        v_final_amount_calculated
    FROM
        orderdetail od
    WHERE
        od.order_id = v_order_id;

    UPDATE "order"
    SET
        total_amount = v_total_amount,
        total_discount = v_total_discount_calculated,
        final_amount = v_final_amount_calculated
    WHERE
        order_id = v_order_id;

    IF TG_OP = 'DELETE' THEN
        RETURN OLD;
    ELSE
        RETURN NEW;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_after_orderdetail_change
AFTER INSERT OR UPDATE OR DELETE ON orderdetail
FOR EACH ROW
EXECUTE FUNCTION update_order_totals_function();

CREATE OR REPLACE FUNCTION log_order_status_change()
RETURNS TRIGGER AS $$
DECLARE
    v_employee_id CHAR(8);
BEGIN
    v_employee_id = NEW.last_updated_by_employee_id;

    IF OLD.status IS DISTINCT FROM NEW.status THEN
        INSERT INTO status_history (
            employee_id,
            order_id,
            date_changed,
            status
        ) VALUES (
            v_employee_id,
            NEW.order_id,
            CURRENT_DATE,
            NEW.status
        );
    END IF;

    -- Trigger AFTER UPDATE phải trả về NEW
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_log_order_status_change
AFTER UPDATE ON "order"
FOR EACH ROW
EXECUTE FUNCTION log_order_status_change();
CREATE OR REPLACE FUNCTION update_stock_quantity_function()
RETURNS TRIGGER AS $$
DECLARE
    v_stock_quantity INT;
    v_quantity_change INT;
BEGIN
    SELECT stock_quantity INTO v_stock_quantity
    FROM variant
    WHERE variant_id = COALESCE(NEW.variant_id, OLD.variant_id);

    IF TG_OP = 'INSERT' THEN
        IF v_stock_quantity < NEW.order_quantity THEN
            RAISE EXCEPTION 'Không đủ số lượng tồn kho cho sản phẩm có variant_id %. Chỉ còn % sản phẩm.', NEW.variant_id, v_stock_quantity;
        END IF;
        UPDATE variant
        SET stock_quantity = stock_quantity - NEW.order_quantity
        WHERE variant_id = NEW.variant_id;

    ELSIF TG_OP = 'DELETE' THEN
        UPDATE variant
        SET stock_quantity = stock_quantity + OLD.order_quantity
        WHERE variant_id = OLD.variant_id;

    ELSIF TG_OP = 'UPDATE' THEN
        v_quantity_change = NEW.order_quantity - OLD.order_quantity;

        -- Kiểm tra nếu số lượng tồn kho không đủ cho sự thay đổi
        IF v_stock_quantity < v_quantity_change THEN
             RAISE EXCEPTION 'Không đủ số lượng tồn kho để tăng số lượng cho sản phẩm có variant_id %. Chỉ còn % sản phẩm.', NEW.variant_id, v_stock_quantity;
        END IF;
        UPDATE variant
        SET stock_quantity = stock_quantity - v_quantity_change
        WHERE variant_id = NEW.variant_id;
    END IF;
    IF TG_OP = 'DELETE' THEN
        RETURN OLD;
    ELSE
        RETURN NEW;
    END IF;

END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_before_orderdetail_change_update_stock
BEFORE INSERT OR UPDATE OR DELETE ON orderdetail
FOR EACH ROW
EXECUTE FUNCTION update_stock_quantity_function();

CREATE OR REPLACE FUNCTION update_product_average_rating_function()
RETURNS TRIGGER AS $$
DECLARE
    v_product_id CHAR(8);
    v_avg_rating NUMERIC(2,1);
BEGIN
    SELECT v.product_id INTO v_product_id
    FROM orderdetail od
    JOIN variant v ON od.variant_id = v.variant_id
    WHERE od.orderdetail_id = COALESCE(NEW.orderdetail_id, OLD.orderdetail_id);

    SELECT AVG(fb.rating) INTO v_avg_rating
    FROM feedback fb
    JOIN orderdetail od ON fb.orderdetail_id = od.orderdetail_id
    JOIN variant v ON od.variant_id = v.variant_id
    WHERE v.product_id = v_product_id;

    UPDATE product
    SET average_rating = v_avg_rating
    WHERE product_id = v_product_id;
    IF TG_OP = 'DELETE' THEN
        RETURN OLD;
    ELSE
        RETURN NEW;
    END IF;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_after_feedback_change
AFTER INSERT OR UPDATE OR DELETE ON feedback
FOR EACH ROW
EXECUTE FUNCTION update_product_average_rating_function();
