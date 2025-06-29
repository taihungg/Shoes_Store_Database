-- Tạo view chỉ hiện thị các các sản phẩm còn hàng
CREATE OR REPLACE VIEW available_products AS
SELECT
    p.*
FROM
    product p
WHERE
    EXISTS (
        SELECT 1
        FROM variant v
        WHERE v.product_id = p.product_id AND v.stock_quantity > 0
    );
