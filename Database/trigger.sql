
-- Hàm cho trigger tự động lưu lịch sử thay đổi trạng thái đơn hàng
CREATE OR REPLACE FUNCTION fn_handle_after_update_order()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.status IS DISTINCT FROM OLD.status THEN
        INSERT INTO status_history (order_id, employee_id, date_changed, status)
        VALUES (NEW.order_id, NEW.last_update_by_employee_id, NOW(), NEW.status);
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_after_update_order
AFTER UPDATE ON "order"
FOR EACH ROW
EXECUTE FUNCTION fn_handle_after_update_order();

-- Hàm cho trigger khi có một đơn hàng bị cập nhật trạng thái thành CANCELLED
CREATE OR REPLACE FUNCTION fn_handle_order_cancellation()
RETURNS TRIGGER AS $$
BEGIN
    IF NEW.status = 'CANCELLED' AND OLD.status <> 'CANCELLED' THEN
        UPDATE variant v
        SET stock_quantity = v.stock_quantity + od.order_quantity
        FROM orderdetail od
        WHERE v.variant_id = od.variant_id AND od.order_id = NEW.order_id;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_handle_order_cancellation
AFTER UPDATE ON "order"
FOR EACH ROW
EXECUTE FUNCTION fn_handle_order_cancellation();

-- Hàm cho trigger sau khi có feedback mới
CREATE OR REPLACE FUNCTION fn_handle_after_insert_feedback()
RETURNS TRIGGER AS $$
DECLARE
    v_product_id CHAR(8);
    v_new_avg_rating DECIMAL(2,1);
BEGIN
    SELECT
        v.product_id INTO v_product_id
    FROM
        orderdetail od
    JOIN
        variant v ON od.variant_id = v.variant_id
    WHERE
        od.orderdetail_id = NEW.orderdetail_id;

    SELECT
        AVG(f.rating) INTO v_new_avg_rating
    FROM
        feedback f
    JOIN
        orderdetail od ON f.orderdetail_id = od.orderdetail_id
    JOIN
        variant v ON od.variant_id = v.variant_id
    WHERE
        v.product_id = v_product_id;

    UPDATE product
    SET average_rating = v_new_avg_rating
    WHERE product_id = v_product_id;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_after_insert_feedback
AFTER INSERT ON feedback
FOR EACH ROW
EXECUTE FUNCTION fn_handle_after_insert_feedback();

