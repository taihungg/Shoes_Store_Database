-- ====================================================================
-- Phần 1: Truy vấn Cơ bản (Đơn giản)
-- ====================================================================

-- Query 1: Lấy danh sách tất cả khách hàng.
-- Mục đích: Xem thông tin của tất cả khách hàng trong cơ sở dữ liệu.
SELECT * FROM customer;

-- Query 2: Lấy danh sách sản phẩm có giá bán trên 1,000,000.
-- Mục đích: Lọc các sản phẩm có giá trị cao.
SELECT product_id, product_name, selling_price
FROM product
WHERE selling_price > 1000000;

-- Query 3: Tìm các đơn hàng đang trong quá trình "ON DELIVERY".
-- Mục đích: Theo dõi tình trạng của các đơn hàng đang được giao.
SELECT order_id, customer_id, order_date, final_amount
FROM "order"
WHERE status = 'ON DELIVERY';

-- Query 4: Liệt kê các thành phố (không trùng lặp) nơi khách hàng sinh sống.
-- Mục đích: Thống kê các khu vực địa lý có khách hàng.
SELECT DISTINCT city FROM customer;

-- Query 5: Lấy danh sách sản phẩm và sắp xếp theo đánh giá trung bình giảm dần.
-- Mục đích: Tìm ra những sản phẩm được đánh giá cao nhất.
SELECT product_id, product_name, average_rating
FROM product
ORDER BY average_rating DESC;


-- ====================================================================
-- Phần 2: Truy vấn với JOIN (Trung bình)
-- ====================================================================

-- Query 6: Lấy danh sách đơn hàng kèm theo tên đầy đủ của khách hàng.
-- Mục đích: Xem thông tin đơn hàng một cách trực quan hơn với tên khách hàng.
SELECT o.order_id, c.first_name || ' ' || c.last_name AS full_name, o.final_amount, o.order_date
FROM "order" o
JOIN customer c ON o.customer_id = c.customer_id;

-- Query 7: Liệt kê tên sản phẩm cùng với tên danh mục và tên thương hiệu.
-- Mục đích: Xem thông tin chi tiết của sản phẩm.
SELECT p.product_name, c.category_name, b.brand_name
FROM product p
JOIN category c ON p.category_id = c.category_id
JOIN brand b ON p.brand_id = b.brand_id;

-- Query 8: Xem chi tiết một đơn hàng cụ thể (ví dụ: order_id = 'ORD00001').
-- Mục đích: Kiểm tra các sản phẩm, số lượng, và giá tiền trong một đơn hàng.
SELECT p.product_name, v.color, v.size, od.order_quantity, od.unit_price, od.sub_total
FROM orderdetail od
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
WHERE od.order_id = 'ORD00001';

-- Query 9: Tìm 5 đơn hàng có giá trị cuối cùng cao nhất.
-- Mục đích: Xác định các đơn hàng giá trị nhất.
SELECT order_id, customer_id, final_amount
FROM "order"
ORDER BY final_amount DESC
LIMIT 5;

-- Query 10: Lấy tất cả các phản hồi (feedback) và xếp hạng (rating) cho một sản phẩm cụ thể (ví dụ: product_id = 'PROD0001').
-- Mục đích: Phân tích đánh giá của khách hàng về một sản phẩm.
SELECT f.rating, f.feedback, f.feedback_date
FROM feedback f
JOIN orderdetail od ON f.orderdetail_id = od.orderdetail_id
JOIN variant v ON od.variant_id = v.variant_id
WHERE v.product_id = 'PROD0001';


-- ====================================================================
-- Phần 3: Truy vấn với Aggregate Functions (Phức tạp)
-- ====================================================================

-- Query 11: Đếm số lượng sản phẩm trong mỗi danh mục.
-- Mục đích: Thống kê quy mô của từng danh mục sản phẩm.
SELECT c.category_name, COUNT(p.product_id) AS number_of_products
FROM product p
JOIN category c ON p.category_id = c.category_id
GROUP BY c.category_name
ORDER BY number_of_products DESC;

-- Query 12: Tính tổng doanh thu (final_amount) theo từng tháng trong năm 2023.
-- Mục đích: Báo cáo doanh thu hàng tháng.
SELECT EXTRACT(MONTH FROM order_date) AS sales_month, SUM(final_amount) AS monthly_revenue
FROM "order"
WHERE EXTRACT(YEAR FROM order_date) = 2023
GROUP BY sales_month
ORDER BY sales_month;

-- Query 13: Tìm 5 khách hàng đã chi tiêu nhiều nhất.
-- Mục đích: Xác định các khách hàng VIP.
SELECT c.customer_id, c.first_name, c.last_name, SUM(o.final_amount) AS total_spent
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY total_spent DESC
LIMIT 5;

-- Query 14: Liệt kê các thương hiệu có hơn 50 sản phẩm.
-- Mục đích: Tìm các thương hiệu lớn có nhiều dòng sản phẩm.
SELECT b.brand_name, COUNT(p.product_id) AS product_count
FROM brand b
JOIN product p ON b.brand_id = p.brand_id
GROUP BY b.brand_name
HAVING COUNT(p.product_id) > 50;

-- Query 15: Tính giá bán trung bình cho tất cả sản phẩm của mỗi thương hiệu.
-- Mục đích: So sánh mức giá trung bình giữa các thương hiệu.
SELECT b.brand_name, AVG(p.selling_price) AS average_price
FROM product p
JOIN brand b ON p.brand_id = b.brand_id
GROUP BY b.brand_name
ORDER BY average_price DESC;


-- ====================================================================
-- Phần 4: Truy vấn Nâng cao (Rất phức tạp)
-- ====================================================================

-- Query 16: Tìm các sản phẩm chưa từng được bán.
-- Mục đích: Xác định hàng tồn kho, không bán chạy.
SELECT p.product_id, p.product_name
FROM product p
LEFT JOIN variant v ON p.product_id = v.product_id
LEFT JOIN orderdetail od ON v.variant_id = od.variant_id
WHERE od.orderdetail_id IS NULL;

-- Query 17: Phân loại sản phẩm theo mức giá sử dụng CASE.
-- Mục đích: Phân nhóm sản phẩm để dễ phân tích.
SELECT
    product_name,
    selling_price,
    CASE
        WHEN selling_price < 500000 THEN 'Giá rẻ'
        WHEN selling_price BETWEEN 500000 AND 2000000 THEN 'Tầm trung'
        ELSE 'Cao cấp'
    END AS price_category
FROM product;

-- Query 18: Tìm 5 biến thể sản phẩm (variant) bán chạy nhất theo số lượng.
-- Mục đích: Xác định sản phẩm "hot" nhất để lên kế hoạch nhập hàng.
WITH VariantSales AS (
    SELECT
        v.variant_id,
        p.product_name,
        v.color,
        v.size,
        SUM(od.order_quantity) AS total_quantity_sold
    FROM orderdetail od
    JOIN variant v ON od.variant_id = v.variant_id
    JOIN product p ON v.product_id = p.product_id
    GROUP BY v.variant_id, p.product_name, v.color, v.size
)
SELECT product_name, color, size, total_quantity_sold
FROM VariantSales
ORDER BY total_quantity_sold DESC
LIMIT 5;

-- Query 19: Tìm những khách hàng đã từng mua hàng trong tháng 12/2023 nhưng chưa mua gì trong tháng 1/2024.
-- Mục đích: Tìm kiếm khách hàng có nguy cơ rời bỏ để thực hiện các chiến dịch marketing.
SELECT c.customer_id, c.first_name, c.last_name
FROM customer c
WHERE c.customer_id IN (
    SELECT customer_id FROM "order" WHERE EXTRACT(YEAR FROM order_date) = 2023 AND EXTRACT(MONTH FROM order_date) = 12
)
AND c.customer_id NOT IN (
    SELECT customer_id FROM "order" WHERE EXTRACT(YEAR FROM order_date) = 2024 AND EXTRACT(MONTH FROM order_date) = 1
);

-- Query 20: Tìm khách hàng đã mua ít nhất một sản phẩm từ mọi danh mục (category).
-- Mục đích: Xác định những khách hàng trung thành và đa dạng nhất.
SELECT c.customer_id, c.first_name, c.last_name
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(DISTINCT p.category_id) = (SELECT COUNT(*) FROM category);






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