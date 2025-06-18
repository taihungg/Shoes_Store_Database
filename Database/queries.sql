-- complex_queries.sql

-- 1. Tìm tất cả khách hàng đã đặt hàng sản phẩm thuộc danh mục 'SHOES' và đơn hàng của họ đang ở trạng thái 'DELIVERED'.
SELECT DISTINCT c.first_name, c.last_name, o.order_id
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
JOIN category cat ON p.category_id = cat.category_id
WHERE cat.category_name = 'SHOES' AND o.status = 'DELIVERED';

-- 2. Lấy tên sản phẩm, màu sắc, kích thước và số lượng tồn kho của các biến thể có số lượng tồn kho dưới mức trung bình của tất cả các biến thể.
SELECT p.product_name, v.color, v.size, v.stock_quantity
FROM product p
JOIN variant v ON p.product_id = v.product_id
WHERE v.stock_quantity < (SELECT AVG(stock_quantity) FROM variant);

-- 3. Tìm các khách hàng đã đặt nhiều hơn một đơn hàng và tổng số tiền của tất cả các đơn hàng của họ lớn hơn 1000.
SELECT c.first_name, c.last_name, COUNT(o.order_id) AS total_orders, SUM(o.final_amount) AS total_spent
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(o.order_id) > 1 AND SUM(o.final_amount) > 1000;

-- 4. Lấy tên sản phẩm, giá bán, và tên thương hiệu của các sản phẩm có giá bán cao hơn giá bán trung bình của tất cả các sản phẩm cùng thương hiệu.
SELECT p.product_name, p.selling_price, b.brand_name
FROM product p
JOIN brand b ON p.brand_id = b.brand_id
WHERE p.selling_price > (SELECT AVG(p2.selling_price) FROM product p2 WHERE p2.brand_id = p.brand_id);

-- 5. Tìm các đơn hàng có ít nhất một sản phẩm mà giá mua cao hơn 200.
SELECT DISTINCT o.order_id, o.order_date, o.total_amount
FROM "order" o
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
WHERE p.purchase_price > 200.00;

-- 6. Lấy thông tin nhân viên đã xử lý các đơn hàng có tổng số tiền lớn nhất trong một ngày cụ thể.
SELECT e.first_name, e.last_name, o.order_id, o.total_amount, o.order_date
FROM employee e
JOIN "order" o ON e.employee_id = o.employee_id
WHERE o.order_date = '2025-06-17' AND o.total_amount = (SELECT MAX(total_amount) FROM "order" WHERE order_date = '2025-06-17');

-- 7. Tìm các khách hàng chưa đặt bất kỳ đơn hàng nào.
SELECT c.first_name, c.last_name
FROM customer c
LEFT JOIN "order" o ON c.customer_id = o.customer_id
WHERE o.order_id IS NULL;

-- 8. Lấy tên sản phẩm và tên danh mục của các sản phẩm có ít nhất 2 biến thể khác nhau.
SELECT p.product_name, c.category_name
FROM product p
JOIN category c ON p.category_id = c.category_id
JOIN variant v ON p.product_id = v.product_id
GROUP BY p.product_id, p.product_name, c.category_name
HAVING COUNT(v.variant_id) >= 2;

-- 9. Tìm các thương hiệu không có bất kỳ sản phẩm nào được bán.
SELECT b.brand_name
FROM brand b
LEFT JOIN product p ON b.brand_id = p.brand_id
LEFT JOIN variant v ON p.product_id = v.product_id
LEFT JOIN orderdetail od ON v.variant_id = od.variant_id
WHERE od.orderdetail_id IS NULL
GROUP BY b.brand_name;

-- 10. Lấy tên khách hàng, tên sản phẩm đã mua và số lượng đặt hàng cho các đơn hàng có tổng số tiền lớn hơn 500.
SELECT c.first_name, p.product_name, od.order_quantity, o.total_amount
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
WHERE o.total_amount > 500;

-- 11. Tìm các sản phẩm có xếp hạng trung bình cao nhất.
SELECT product_name, average_rating
FROM product
WHERE average_rating = (SELECT MAX(average_rating) FROM product);

-- 12. Đếm số lượng đơn hàng cho mỗi tháng trong năm 2025.
SELECT STRFTIME('%Y-%m', order_date) AS order_month, COUNT(order_id) AS order_count
FROM "order"
WHERE STRFTIME('%Y', order_date) = '2025'
GROUP BY order_month
ORDER BY order_month;

-- 13. Tính tổng doanh thu (final_amount) cho mỗi phương thức thanh toán.
SELECT payment_method, SUM(final_amount) AS total_revenue
FROM "order"
GROUP BY payment_method;

-- 14. Tìm các khách hàng có số lượng phản hồi ít nhất 2.
SELECT c.first_name, c.last_name, COUNT(f.feedback_id) AS feedback_count
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN feedback f ON od.orderdetail_id = f.orderdetail_id
GROUP BY c.customer_id, c.first_name, c.last_name
HAVING COUNT(f.feedback_id) >= 2;

-- 15. Lấy tên danh mục và tổng giá trị tồn kho (selling_price * stock_quantity) cho mỗi danh mục, chỉ hiển thị các danh mục có tổng giá trị lớn hơn 10000.
SELECT cat.category_name, SUM(p.selling_price * v.stock_quantity) AS total_stock_value
FROM category cat
JOIN product p ON cat.category_id = p.category_id
JOIN variant v ON p.product_id = v.product_id
GROUP BY cat.category_name
HAVING SUM(p.selling_price * v.stock_quantity) > 10000;

-- 16. Tìm ngày có số lượng đơn hàng được giao nhiều nhất.
SELECT order_date, COUNT(order_id) AS delivered_orders
FROM "order"
WHERE status = 'DELIVERED'
GROUP BY order_date
ORDER BY delivered_orders DESC
LIMIT 1;

-- 17. Tính tổng số lượng sản phẩm đã bán cho mỗi thương hiệu.
SELECT b.brand_name, SUM(od.order_quantity) AS total_products_sold
FROM brand b
JOIN product p ON b.brand_id = p.brand_id
JOIN variant v ON p.product_id = v.product_id
JOIN orderdetail od ON v.variant_id = od.variant_id
GROUP BY b.brand_name;

-- 18. Lấy các sản phẩm có màu sắc 'Black' và tổng số lượng tồn kho của màu 'Black' cho sản phẩm đó.
SELECT p.product_name, SUM(v.stock_quantity) AS total_black_stock
FROM product p
JOIN variant v ON p.product_id = v.product_id
WHERE v.color = 'Black'
GROUP BY p.product_name
HAVING SUM(v.stock_quantity) > 0;

-- 19. Tìm khách hàng có số lượng sản phẩm khác nhau đã mua nhiều nhất.
SELECT c.first_name, c.last_name, COUNT(DISTINCT p.product_id) AS distinct_products_bought
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY distinct_products_bought DESC
LIMIT 1;

-- 20. Tính tổng chiết khấu đã được áp dụng cho mỗi đơn hàng.
SELECT order_id, SUM(discount) AS total_discount_applied
FROM orderdetail
GROUP BY order_id;

-- 21. Lấy thông tin về sản phẩm và biến thể của chúng, bao gồm cả số lượng tồn kho và thông tin chi tiết về sản phẩm (mô tả, giá).
SELECT p.product_name, p.product_description, p.selling_price, v.color, v.size, v.stock_quantity
FROM product p
JOIN variant v ON p.product_id = v.product_id;

-- 22. Tìm tên khách hàng và email của họ, cùng với tổng số đơn hàng mà họ đã đặt và tổng số tiền đã chi tiêu.
SELECT c.first_name, c.email, COUNT(o.order_id) AS num_orders, SUM(o.final_amount) AS total_spent
FROM customer c
LEFT JOIN "order" o ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.first_name, c.email;

-- 23. Lấy tên sản phẩm, giá bán, và tên thương hiệu của các sản phẩm có giá bán cao hơn giá bán trung bình của tất cả các sản phẩm.
SELECT p.product_name, p.selling_price, b.brand_name
FROM product p
JOIN brand b ON p.brand_id = b.brand_id
WHERE p.selling_price > (SELECT AVG(selling_price) FROM product);

-- 24. Tìm các khách hàng đã đặt hàng trong tháng 5 năm 2025 và tổng số tiền của các đơn hàng đó.
SELECT c.first_name, c.last_name, SUM(o.total_amount) AS total_spent_may_2025
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
WHERE STRFTIME('%Y-%m', o.order_date) = '2025-05'
GROUP BY c.customer_id, c.first_name, c.last_name;

-- 25. Lấy danh sách các sản phẩm chưa có bất kỳ phản hồi nào.
SELECT p.product_name
FROM product p
LEFT JOIN variant v ON p.product_id = v.product_id
LEFT JOIN orderdetail od ON v.variant_id = od.variant_id
LEFT JOIN feedback f ON od.orderdetail_id = f.orderdetail_id
WHERE f.feedback_id IS NULL
GROUP BY p.product_id, p.product_name;

-- 26. Tìm tên nhân viên và số lượng đơn hàng mà họ đã xử lý, chỉ hiển thị những nhân viên đã xử lý ít nhất 5 đơn hàng.
SELECT e.first_name, e.last_name, COUNT(o.order_id) AS handled_orders
FROM employee e
JOIN "order" o ON e.employee_id = o.employee_id
GROUP BY e.employee_id, e.first_name, e.last_name
HAVING COUNT(o.order_id) >= 5;

-- 27. Lấy tên sản phẩm, tên danh mục và tên thương hiệu cho tất cả các sản phẩm.
SELECT p.product_name, cat.category_name, b.brand_name
FROM product p
JOIN category cat ON p.category_id = cat.category_id
JOIN brand b ON p.brand_id = b.brand_id;

-- 28. Tìm các đơn hàng có giá trị cuối cùng lớn hơn tổng giá trị trung bình của tất cả các đơn hàng.
SELECT order_id, final_amount
FROM "order"
WHERE final_amount > (SELECT AVG(final_amount) FROM "order");

-- 29. Lấy tên khách hàng, tổng số tiền đã chi tiêu và tổng số lượng sản phẩm đã mua.
SELECT c.first_name, c.last_name, SUM(o.final_amount) AS total_spent, SUM(od.order_quantity) AS total_items_bought
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
JOIN orderdetail od ON o.order_id = od.order_id
GROUP BY c.customer_id, c.first_name, c.last_name;

-- 30. Tìm các biến thể có số lượng tồn kho thấp hơn 20 và đã được đặt hàng ít nhất một lần.
SELECT DISTINCT v.variant_id, p.product_name, v.color, v.size, v.stock_quantity
FROM variant v
JOIN product p ON v.product_id = p.product_id
JOIN orderdetail od ON v.variant_id = od.variant_id
WHERE v.stock_quantity < 20;

-- 31. Xếp hạng các sản phẩm theo giá bán giảm dần.
SELECT product_id, product_name, selling_price,
       RANK() OVER (ORDER BY selling_price DESC) AS price_rank
FROM product;

-- 32. Tính tổng số tiền đang chạy (running total) của các đơn hàng theo ngày.
SELECT order_id, order_date, total_amount,
       SUM(total_amount) OVER (ORDER BY order_date) AS running_total
FROM "order"
ORDER BY order_date;

-- 33. Lấy tên sản phẩm, tên danh mục, và giá bán, đồng thời hiển thị giá bán trung bình của các sản phẩm trong cùng danh mục.
SELECT p.product_name, c.category_name, p.selling_price,
       AVG(p.selling_price) OVER (PARTITION BY c.category_id) AS avg_category_price
FROM product p
JOIN category c ON p.category_id = c.category_id;

-- 34. Tìm 3 sản phẩm có giá bán cao nhất trong mỗi danh mục.
WITH RankedProducts AS (
    SELECT p.product_name, c.category_name, p.selling_price,
           ROW_NUMBER() OVER (PARTITION BY c.category_id ORDER BY p.selling_price DESC) AS rn
    FROM product p
    JOIN category c ON p.category_id = c.category_id
)
SELECT product_name, category_name, selling_price
FROM RankedProducts
WHERE rn <= 3;

-- 35. Lấy chi tiết đơn hàng, và hiển thị tổng số lượng của tất cả các sản phẩm trong cùng một đơn hàng.
SELECT order_id, variant_id, order_quantity,
       SUM(order_quantity) OVER (PARTITION BY order_id) AS total_quantity_in_order
FROM orderdetail;

-- 36. Tạo báo cáo doanh thu hàng tháng theo danh mục sản phẩm.
SELECT
    STRFTIME('%Y-%m', o.order_date) AS sales_month,
    c.category_name,
    SUM(od.sub_total) AS monthly_revenue
FROM "order" o
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
JOIN category c ON p.category_id = c.category_id
GROUP BY sales_month, c.category_name
ORDER BY sales_month, c.category_name;

-- 37. Liệt kê các khách hàng có sinh nhật trong tháng hiện tại.
SELECT first_name, last_name, dob
FROM customer
WHERE STRFTIME('%m', dob) = STRFTIME('%m', 'now');

-- 38. Tìm các sản phẩm bán chạy nhất (dựa trên tổng số lượng bán ra).
SELECT p.product_name, SUM(od.order_quantity) AS total_sold_quantity
FROM product p
JOIN variant v ON p.product_id = v.product_id
JOIN orderdetail od ON v.variant_id = od.variant_id
GROUP BY p.product_name
ORDER BY total_sold_quantity DESC
LIMIT 10;

-- 39. Tính lợi nhuận ròng cho mỗi sản phẩm (tổng selling_price - tổng purchase_price).
SELECT p.product_name,
       SUM(od.order_quantity * p.selling_price) - SUM(od.order_quantity * p.purchase_price) AS net_profit
FROM product p
JOIN variant v ON p.product_id = v.product_id
JOIN orderdetail od ON v.variant_id = od.variant_id
GROUP BY p.product_name
ORDER BY net_profit DESC;

-- 40. Lấy tổng số lượng đơn hàng, tổng số tiền và tổng chiết khấu cho mỗi ngày.
SELECT order_date, COUNT(order_id) AS total_orders, SUM(total_amount) AS total_revenue, SUM(total_discount) AS total_discount_given
FROM "order"
GROUP BY order_date
ORDER BY order_date;

-- 41. Lấy tất cả các email từ khách hàng và nhân viên.
SELECT email FROM customer WHERE email IS NOT NULL
UNION ALL
SELECT email FROM employee WHERE email IS NOT NULL;

-- 42. Liệt kê tên của tất cả các cá nhân (khách hàng và nhân viên) có sinh nhật trong tháng 1.
SELECT first_name, last_name, 'Customer' AS role
FROM customer
WHERE STRFTIME('%m', dob) = '01'
UNION ALL
SELECT first_name, last_name, 'Employee' AS role
FROM employee
WHERE STRFTIME('%m', dob) = '01'
ORDER BY first_name, last_name;

-- 43. Cập nhật trạng thái của tất cả các đơn hàng 'PACKAGING' sang 'ON DELIVERY' sau một ngày nhất định.
UPDATE "order"
SET status = 'ON DELIVERY'
WHERE status = 'PACKAGING' AND order_date < '2025-06-10';

-- 44. Tăng giá bán của tất cả các sản phẩm thuộc danh mục 'SHOES' thêm 10%.
UPDATE product
SET selling_price = selling_price * 1.10
WHERE category_id = (SELECT category_id FROM category WHERE category_name = 'SHOES');

-- 45. Giảm số lượng tồn kho của các biến thể đã được đặt hàng trong các đơn hàng 'PROCESSING'.
UPDATE variant
SET stock_quantity = variant.stock_quantity - od.order_quantity
FROM orderdetail od
JOIN "order" o ON od.order_id = o.order_id
WHERE variant.variant_id = od.variant_id AND o.status = 'PROCESSING';


-- 46. Xóa tất cả các đơn hàng cũ hơn 2 năm đã hoàn thành (DELIVERED).
DELETE FROM "order"
WHERE status = 'DELIVERED' AND order_date < DATE('now', '-2 years');

-- 47. Xóa các khách hàng không có bất kỳ đơn hàng nào và không có địa chỉ email.
DELETE FROM customer
WHERE customer_id NOT IN (SELECT customer_id FROM "order") AND email IS NULL;

-- 48. Tìm các sản phẩm mà đã có ít nhất một phản hồi.
SELECT p.product_name
FROM product p
WHERE EXISTS (
    SELECT 1
    FROM variant v
    JOIN orderdetail od ON v.variant_id = od.variant_id
    JOIN feedback f ON od.orderdetail_id = f.orderdetail_id
    WHERE v.product_id = p.product_id
);

-- 49. Lấy danh sách các nhân viên chưa được gán cho bất kỳ đơn hàng nào.
SELECT e.first_name, e.last_name
FROM employee e
WHERE NOT EXISTS (
    SELECT 1
    FROM "order" o
    WHERE o.employee_id = e.employee_id
);

-- 50. Tìm các khách hàng đã đặt hàng tất cả các sản phẩm có màu 'Red'.
SELECT c.first_name, c.last_name
FROM customer c
WHERE NOT EXISTS (
    SELECT v.variant_id
    FROM variant v
    WHERE v.color = 'Red'
    AND NOT EXISTS (
        SELECT 1
        FROM "order" o
        JOIN orderdetail od ON o.order_id = od.order_id
        WHERE o.customer_id = c.customer_id AND od.variant_id = v.variant_id
    )
);