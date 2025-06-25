--Tài Hưng
--1. Tính tổng final_amount cho mỗi payment_method trong bảng order.
--Hiển thị payment_method và tổng doanh thu, sắp xếp giảm dần theo tổng doanh thu.
SELECT payment_method, SUM(final_amount) total_amount_by_payment_method
FROM "order"
GROUP BY payment_method
ORDER BY total_amount_by_payment_method DESC;

--2. Xác định sản phẩm đã được bán với số lượng tổng cộng cao nhất trên tất cả các đơn hàng.
WITH total_quantity_by_product AS (
    SELECT p.product_id, SUM(od.order_quantity) total_quantity_sold
    FROM orderdetail od
    JOIN variant v
    USING (variant_id)
    JOIN product p
    USING (product_id)
    GROUP BY p.product_id
)
SELECT p.product_id, p.product_name, b.brand_name, ts.total_quantity_sold
FROM product p
JOIN total_quantity_by_product ts
USING (product_id)
JOIN brand b
USING (brand_id)
WHERE ts.total_quantity_sold = (
    SELECT MAX(total_quantity_sold)
    FROM total_quantity_by_product
)
ORDER BY p.product_id ASC;

--3. Tìm product_id, product_name, purchase_price, selling_price, và tính phần trăm lợi nhuận 
--cho mỗi sản phẩm. Sắp xếp kết quả theo phần trăm lợi nhuận giảm dần.
SELECT product_id, product_name, purchase_price, selling_price, ROUND(((selling_price - purchase_price) / purchase_price * 100), 2) profit_margin
FROM product
ORDER BY profit_margin DESC
LIMIT 10;

--4. Tìm thông tin khách hàng và tổng số tiền đã chi tiêu (final_amount) của khách hàng đã chi tiêu nhiều tiền nhất trên tất cả các đơn hàng của họ.
WITH customer_spent AS(
    SELECT c.customer_id, CONCAT(c.first_name, ' ', c.last_name) customer_name, SUM(o.final_amount) total_spent
    FROM customer c
    JOIN "order" o
    USING (customer_id)
    GROUP BY customer_id
)
SELECT customer_id, customer_name, total_spent
FROM customer_spent
WHERE total_spent = (
    SELECT MAX(total_spent)
    FROM customer_spent
);

--5. Liệt kê product_name và số lượng variant mà mỗi sản phẩm có. Sắp xếp kết quả giảm dần theo số lượng biến thể.
SELECT product_id, product_name, COUNT(variant_id) number_of_variants
FROM product 
JOIN variant
USING (product_id)
GROUP BY product_id
ORDER BY number_of_variants DESC
LIMIT 10;

--6. Cho product_id là 'PD000001', liệt kê tất cả các category_name mà sản phẩm này thuộc về.
CREATE OR REPLACE FUNCTION find_product_category(input_product_id CHAR(8))
RETURNS TABLE (category_name VARCHAR(30))
AS $$
BEGIN
    RETURN QUERY
    SELECT c.category_name 
    FROM product_category pc
    JOIN category c
    USING(category_id)
    JOIN product p
    USING (product_id)
    WHERE p.product_id = input_product_id;
END;
$$ LANGUAGE plpgsql;

SELECT find_product_category('PD000001');

--7. Liệt kê variant_id và stock_quantity của các biến thể chưa từng xuất hiện trong bất kỳ orderdetail nào.
SELECT v.variant_id, v.stock_quantity
FROM variant v
LEFT JOIN orderdetail od
USING(variant_id)
WHERE orderdetail_id is NULL
ORDER BY stock_quantity DESC
LIMIT 10;

--8. Hiển thị thông tin sản phẩm và tổng số lượng tồn kho của sản phẩm.
SELECT p.product_id, SUM(v.stock_quantity) total_stock_quantity
FROM product p 
JOIN variant v
USING (product_id)
GROUP BY product_id
ORDER BY total_stock_quantity ASC
LIMIT 10;

--9. Tìm order_id, order_date, và status của các đơn hàng có ít nhất một variant trong orderdetail mà stock_quantity của biến thể đó bằng 0.
WITH order_has_soldout_variant AS (
    SELECT o.order_id, v.variant_id
    FROM "order" o
    JOIN orderdetail od
    USING (order_id)
    JOIN variant v
    USING (variant_id)
    WHERE v.stock_quantity = 0
)
SELECT o.order_id, o.order_date, o.status, COUNT(ov.variant_id) number_of_soldout_variant
FROM "order" o
JOIN order_has_soldout_variant ov
USING(order_id)
GROUP BY o.order_id
ORDER BY o.order_id;

-- 10. Đối với mỗi category_name, tìm thông tin của sản phẩm có tổng số lượng bán cao nhất trong danh mục đó.
WITH total_quantity_by_product AS (
    SELECT p.product_id, p.product_name, SUM(od.order_quantity) total_quantity_sold, pc.category_id
    FROM orderdetail od
    JOIN variant v
    USING (variant_id)
    JOIN product p
    USING (product_id)
    JOIN product_category pc
    USING (product_id)
    GROUP BY p.product_id, pc.category_id
), 
top_sales AS (
    SELECT category_id, MAX(total_quantity_sold) max_sales
    FROM total_quantity_by_product
    GROUP BY category_id
)
SELECT ts.category_id, c.category_name, ts.max_sales
FROM top_sales ts
JOIN category c
USING (category_id)
ORDER BY ts.max_sales;


--Nguyễn Trung Kiên
-- 1. Lấy danh sách tất cả khách hàng (customer_id, họ tên, thành phố, số điện thoại)
SELECT customer_id, first_name || ' ' || last_name AS full_name, city, phone_number
FROM customer
LIMIT 10;

-- 2. Liệt kê 10 sản phẩm có giá bán cao nhất (product_id, product_name, selling_price)
SELECT product_id, product_name, selling_price
FROM product
ORDER BY selling_price DESC
LIMIT 10;

-- 3. Tìm các khách hàng đã từng mua hàng ở Hà Nội
SELECT DISTINCT c.customer_id, c.first_name, c.last_name
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
WHERE c.city = 'Hà Nội';

-- 4. Liệt kê các sản phẩm chưa từng được bán (không xuất hiện trong orderdetail)
SELECT p.product_id, p.product_name
FROM product p
LEFT JOIN variant v ON p.product_id = v.product_id
LEFT JOIN orderdetail od ON v.variant_id = od.variant_id
WHERE od.orderdetail_id IS NULL
LIMIT 10;

-- 5. Tìm khách hàng đã mua ít nhất một sản phẩm ở mọi danh mục (category)
SELECT c.customer_id, c.first_name, c.last_name
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product_category pc ON v.product_id = pc.product_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(DISTINCT pc.category_id) = (SELECT COUNT(*) FROM category);

-- 6. Liệt kê các khách hàng đã đặt từ 3 đơn hàng trở lên trong năm 2024
SELECT c.customer_id, c.first_name, c.last_name, COUNT(o.order_id) AS total_orders
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
WHERE EXTRACT(YEAR FROM o.order_date) = 2024
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(o.order_id) >= 3
ORDER BY total_orders DESC;

-- 7. Tính tổng số lượng bán của từng sản phẩm, lấy top 5 sản phẩm bán chạy nhất
WITH product_sales AS (
  SELECT p.product_id, p.product_name, SUM(od.order_quantity) AS total_sold
  FROM product p
  JOIN variant v ON p.product_id = v.product_id
  JOIN orderdetail od ON v.variant_id = od.variant_id
  GROUP BY p.product_id, p.product_name
)
SELECT * FROM product_sales
ORDER BY total_sold DESC
LIMIT 5;

-- 8. WITH: Tính tổng doanh thu từng tháng trong năm 2024
WITH monthly_revenue AS (
  SELECT EXTRACT(MONTH FROM order_date) AS month, SUM(final_amount) AS revenue
  FROM "order"
  WHERE EXTRACT(YEAR FROM order_date) = 2024
  GROUP BY month
)
SELECT * FROM monthly_revenue
ORDER BY month;

-- 9. FUNCTION: Trả về tổng số đơn hàng của một khách hàng theo customer_id
CREATE OR REPLACE FUNCTION total_orders_by_customer(cid CHAR(8))
RETURNS INTEGER AS $$
DECLARE
  result INTEGER;
BEGIN
  SELECT COUNT(*) INTO result FROM "order" WHERE customer_id = cid;
  RETURN result;
END;
$$ LANGUAGE plpgsql;

-- Gọi thử:
SELECT customer_id, first_name, last_name, total_orders_by_customer(customer_id) AS total_orders
FROM customer
WHERE customer_id = 'CUS00001';

-- 10. FUNCTION: Trả về tổng doanh thu của một thương hiệu theo brand_id
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

-- Gọi thử:
SELECT brand_id, brand_name, brand_revenue(brand_id) AS total_revenue
FROM brand
ORDER BY total_revenue DESC
LIMIT 5;


--Trần Việt Gia Khánh
-- Query 1: Liệt kê tất cả nhân viên và thông tin liên lạc của họ.
SELECT
    employee_id,
    concat(first_name || ' ' || last_name) AS full_name,
    phone_number,
    email
FROM employee;

-- Query 2: Tìm các sản phẩm được làm từ một chất liệu cụ thể 
SELECT
    product_id,
    product_name,
    material,
    selling_price
FROM product
WHERE material = 'Leather';

-- Query 3: Liệt kê các đơn hàng đã được cập nhật bởi một nhân viên cụ thể.
SELECT
    o.order_id,
    o.status,
    o.final_amount,
    concat(e.first_name || ' ' || e.last_name) AS employee_updated
FROM "order" o
JOIN employee e ON o.last_updated_by_employee_id = e.employee_id
WHERE e.employee_id = 'EMP00001'; 


-- Query 4: Tính tổng giá trị tồn kho (dựa trên giá nhập) cho mỗi thương hiệu.
SELECT
    b.brand_name,
    SUM(v.stock_quantity * p.purchase_price) AS total_inventory_value
FROM variant v
JOIN product p ON v.product_id = p.product_id
JOIN brand b ON p.brand_id = b.brand_id
GROUP BY b.brand_name
ORDER BY total_inventory_value DESC;


-- Query 5: Tìm những khách hàng đã mua hàng nhưng chưa bao giờ để lại đánh giá (feedback).
SELECT
    c.customer_id,
    c.first_name,
    c.last_name,
    c.email
FROM customer c
WHERE c.customer_id NOT IN (
    SELECT DISTINCT o.customer_id
    FROM "order" o
    JOIN orderdetail od ON o.order_id = od.order_id
    JOIN feedback f ON od.orderdetail_id = f.orderdetail_id
);


-- Query 6: Hiển thị lịch sử thay đổi trạng thái chi tiết của một đơn hàng.
SELECT
    sh.order_id,
    sh.date_changed,
    sh.status
FROM status_history sh
JOIN employee e ON sh.employee_id = e.employee_id
WHERE sh.order_id = 'ORD00002' -- Thay 'ORD00002' bằng ID đơn hàng cần xem
ORDER BY sh.date_changed ASC;

-- Query 7: Tính toán thời gian giao hàng trung bình (từ lúc đặt hàng đến lúc giao thành công).
WITH OrderCompletionTime AS (
    SELECT
        o.order_id,
        o.order_date,
        sh.date_changed AS delivery_date
    FROM "order" o
    JOIN status_history sh ON o.order_id = sh.order_id
    WHERE o.status = 'DELIVERED' AND sh.status = 'DELIVERED'
)
SELECT
    AVG(delivery_date - order_date) AS average_delivery_days
FROM OrderCompletionTime;


-- Query 8: Liệt kê 5 cặp sản phẩm thường được mua cùng nhau nhất.
SELECT
    p1.product_name AS product_1,
    p2.product_name AS product_2,
    COUNT(*) AS times_bought_together
FROM orderdetail od1
JOIN orderdetail od2 ON od1.order_id = od2.order_id AND od1.variant_id < od2.variant_id
JOIN variant v1 ON od1.variant_id = v1.variant_id
JOIN product p1 ON v1.product_id = p1.product_id
JOIN variant v2 ON od2.variant_id = v2.variant_id
JOIN product p2 ON v2.product_id = p2.product_id
GROUP BY p1.product_name, p2.product_name
ORDER BY times_bought_together DESC
LIMIT 5;


-- Query 9: Xếp hạng khách hàng trong mỗi thành phố dựa trên tổng chi tiêu.
WITH CustomerSpendingByCity AS (
    SELECT
        c.city,
        concat(c.first_name || ' ' || c.last_name) AS customer_name,
        SUM(o.final_amount) AS total_spent,
        RANK() OVER(PARTITION BY c.city ORDER BY SUM(o.final_amount) DESC) as spending_rank
    FROM customer c
    JOIN "order" o ON c.customer_id = o.customer_id
    GROUP BY c.city, customer_name
)
SELECT
    city,
    customer_name,
    total_spent,
    spending_rank
FROM CustomerSpendingByCity
WHERE spending_rank <= 3
ORDER BY city, spending_rank;


-- Query 10: Tìm ngày có doanh thu cao nhất trong lịch sử.
WITH DailyRevenue AS (
    SELECT
        order_date,
        SUM(final_amount) as daily_total
    FROM "order"
    GROUP BY order_date
)
SELECT
    order_date,
    daily_total
FROM DailyRevenue
WHERE daily_total = (SELECT MAX(daily_total) FROM DailyRevenue);