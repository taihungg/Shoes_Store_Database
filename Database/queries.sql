SET client_encoding = 'UTF8';
-- Nguyễn Tài Hưng
-- 1. Tìm kiếm sản phẩm theo khoảng giá
SELECT * 
FROM available_products 
WHERE selling_price 
BETWEEN 40 AND 50
ORDER BY selling_price ASC
LIMIT 10;

-- 2. Tìm kiếm sản phẩm theo size
SELECT DISTINCT p.* 
FROM available_products p
JOIN variant v 
USING (product_id)
WHERE v.size = 44
ORDER BY p.selling_price ASC
LIMIT 10;

-- 3. Lấy tất cả đánh giá của một sản phẩm
SELECT v.product_id, v.variant_id, v.color, f.rating, f.feedback, f.feedback_date, CONCAT(c.first_name, ' ', c.last_name) customer_name
FROM feedback f
JOIN orderdetail od 
ON f.orderdetail_id = od.orderdetail_id
JOIN variant v 
ON od.variant_id = v.variant_id
JOIN "order" o
ON od.order_id = o.order_id
JOIN customer c 
ON o.customer_id = c.customer_id
WHERE v.product_id = 'PD000020';

-- 4. Tìm kiếm các sản phẩm đang được bán theo một chuỗi
SELECT * FROM fn_search_products('sport');

-- 5. Tạo một đơn hàng mới với một vài biến thể
SELECT fn_create_order(
    'CUS00001',
    'Cash',
    'hehehe!',
    '[{"variant_id": "V0000020", "quantity": 5}, {"variant_id": "V0000040", "quantity": 3}]'::JSONB
);

-- 6. Xem chi tiết một đơn hàng
SELECT o.*, p.product_name, v.color, v.size, od.order_quantity, od.unit_price
FROM "order" o
JOIN orderdetail od ON o.order_id = od.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
WHERE o.order_id = 'ORD00308';

-- 7. Lấy lịch sử đơn hàng của một khách hàng cụ thể
SELECT order_id, order_date, final_amount, status
FROM "order"
WHERE customer_id = 'CUS00001' -- Thay bằng ID của khách hàng đang đăng nhập
ORDER BY order_date DESC;

-- 8. Lấy danh sách các đơn hàng ở trạng thái "PENDING" để nhân viên vào xử lý
SELECT order_id, customer_id, final_amount, order_date, payment_method
FROM "order"
WHERE status IN ('pending', 'processing')
ORDER BY order_date ASC; -- Ưu tiên xử lý đơn cũ trước

--9. Tìm kiếm đơn hàng theo thông tin khách hàng (SĐT hoặc Tên)
SELECT o.order_id, o.order_date, o.status, o.final_amount, c.first_name, c.last_name, c.phone_number
FROM "order" o
JOIN customer c ON o.customer_id = c.customer_id
WHERE c.phone_number = '0987654321' OR c.first_name ILIKE '%Hung%'; 

--10. Lấy danh sách sản phẩm cần đóng gói cho các đơn đang xử lý
SELECT p.product_id, p.product_name, v.color, v.size, SUM(od.order_quantity) AS total_quantity_to_pack
FROM orderdetail od
JOIN "order" o ON od.order_id = o.order_id
JOIN variant v ON od.variant_id = v.variant_id
JOIN product p ON v.product_id = p.product_id
WHERE o.status = 'PENDING'
GROUP BY p.product_id, p.product_name, v.color, v.size
ORDER BY p.product_name;

--11. Xem lịch sử thay đổi trạng thái của một đơn hàng
SELECT s.date_changed, s.status, e.first_name || ' ' || e.last_name AS employee_name
FROM status_history s
LEFT JOIN employee e ON s.employee_id = e.employee_id
WHERE s.order_id = 'OD000001'
ORDER BY s.date_changed ASC;

--12. Liệt kê các đơn hàng bị treo quá lâu
SELECT order_id, customer_id, order_date, status
FROM "order"
WHERE status = 'PENDING' AND order_date < NOW() - INTERVAL '3 days';

--13. Top 10 khách hàng chi tiêu nhiều nhất
SELECT c.customer_id, c.first_name, c.last_name, c.email, COUNT(o.order_id) AS total_orders, SUM(o.final_amount) AS total_spent
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
WHERE o.status = 'completed'
GROUP BY c.customer_id, c.first_name, c.last_name, c.email
ORDER BY total_spent DESC
LIMIT 10;

--14. Tính tổng giá trị của hàng tồn kho hiện tại
SELECT SUM(v.stock_quantity * p.purchase_price) AS total_inventory_value
FROM variant v
JOIN product p ON v.product_id = p.product_id
WHERE v.stock_quantity > 0;


--Trần Việt Gia Khánh
-- 1. Báo cáo doanh thu hàng ngày/tháng/năm
-- Doanh thu theo ngày
SELECT
    order_date,
    SUM(final_amount) AS daily_revenue
FROM "order"
WHERE order_date = CURRENT_DATE -- Hoặc thay bằng 'YYYY-MM-DD' cụ thể
GROUP BY order_date
ORDER BY order_date;

-- Doanh thu theo tháng
SELECT
    TO_CHAR(order_date, 'YYYY-MM') AS month,
    SUM(final_amount) AS monthly_revenue
FROM "order"
WHERE EXTRACT(YEAR FROM order_date) = EXTRACT(YEAR FROM CURRENT_DATE) -- Hoặc thay bằng năm cụ thể
GROUP BY month
ORDER BY month;

-- Doanh thu theo năm
SELECT
    EXTRACT(YEAR FROM order_date) AS year,
    SUM(final_amount) AS yearly_revenue
FROM "order"
GROUP BY year
ORDER BY year;

-- 2. Báo cáo sản phẩm bán chạy nhất (theo số lượng hoặc doanh thu)
-- Sản phẩm bán chạy nhất theo số lượng
SELECT p.product_id, p.product_name, SUM(od.order_quantity) AS total_quantity_sold 
FROM orderdetail od 
JOIN variant v ON od.variant_id = v.variant_id 
JOIN product p ON v.product_id = p.product_id 
GROUP BY p.product_id, p.product_name 
ORDER BY total_quantity_sold DESC 
LIMIT 10;
-- Sản phẩm bán chạy nhất theo doanh thu
SELECT p.product_id, p.product_name, SUM(od.sub_total) AS total_revenue 
FROM orderdetail od 
JOIN variant v ON od.variant_id = v.variant_id 
JOIN product p ON v.product_id = p.product_id 
GROUP BY p.product_id, p.product_name ORDER BY total_revenue DESC LIMIT 10;

-- 3. Báo cáo doanh thu theo thương hiệu
SELECT b.brand_id, b.brand_name, SUM(od.sub_total) AS brand_revenue 
FROM orderdetail od 
JOIN variant v ON od.variant_id = v.variant_id 
JOIN product p ON v.product_id = p.product_id 
JOIN brand b ON p.brand_id = b.brand_id 
GROUP BY b.brand_id, b.brand_name 
ORDER BY brand_revenue DESC;

-- 4. Báo cáo doanh thu theo danh mục sản phẩm
SELECT c.category_id, c.category_name, SUM(od.sub_total) AS category_revenue 
FROM orderdetail od 
JOIN variant v ON od.variant_id = v.variant_id 
JOIN product p ON v.product_id = p.product_id 
JOIN product_category pc ON p.product_id = pc.product_id 
JOIN category c ON pc.category_id = c.category_id 
GROUP BY c.category_id, c.category_name 
ORDER BY category_revenue DESC;

-- 5. Lịch sử mua hàng của một khách hàng cụ thể
SELECT o.order_id, o.order_date, p.product_name, v.color, v.size, od.order_quantity, od.unit_price, od.sub_total 
FROM "order" o 
JOIN orderdetail od ON o.order_id = od.order_id 
JOIN variant v ON od.variant_id = v.variant_id 
JOIN product p ON v.product_id = p.product_id 
WHERE o.customer_id = 'CUST001' 
ORDER BY o.order_date DESC, o.order_id DESC;

-- 6. Danh sách khách hàng có số lượng đơn hàng cao nhất
SELECT
    c.first_name,
    c.last_name,
    COUNT(o.order_id) AS total_orders
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY total_orders DESC
LIMIT 10;

-- 7. Danh sách khách hàng có tổng giá trị mua hàng cao nhất
SELECT
    c.first_name,
    c.last_name,
    SUM(o.final_amount) AS total_spending
FROM customer c
JOIN "order" o ON c.customer_id = o.customer_id
GROUP BY c.customer_id, c.first_name, c.last_name
ORDER BY total_spending DESC
LIMIT 10;

-- 8. Các đơn hàng bị hủy
SELECT
    o.order_id,
    o.order_date,
    o.final_amount,
    o.status,
    c.first_name,
    c.last_name
FROM "order" o
JOIN customer c ON o.customer_id = c.customer_id
WHERE o.status = 'Cancelled'
ORDER BY o.order_date DESC;

-- Nguyễn Trung Kiên
-- 1. Liệt kê tất cả sản phẩm kèm tên thương hiệu và giá bán
SELECT p.product_id, p.product_name, b.brand_name, p.selling_price
FROM product p
JOIN brand b ON p.brand_id = b.brand_id
LIMIT 10;

-- 2. Liệt kê 10 sản phẩm có giá bán cao nhất (product_id, product_name, selling_price)
SELECT product_id, product_name, selling_price
FROM product
ORDER BY selling_price DESC
LIMIT 10;

-- 3. Thống kê số sản phẩm theo từng thương hiệu
SELECT b.brand_id, b.brand_name, COUNT(p.product_id) AS product_count
FROM brand b
LEFT JOIN product p ON b.brand_id = p.brand_id
GROUP BY b.brand_id, b.brand_name
ORDER BY product_count DESC;

-- 4. Liệt kê các sản phẩm chưa từng được bán (không xuất hiện trong orderdetail)
SELECT p.product_id, p.product_name
FROM product p
LEFT JOIN variant v ON p.product_id = v.product_id
LEFT JOIN orderdetail od ON v.variant_id = od.variant_id
WHERE od.orderdetail_id IS NULL
LIMIT 10;

-- 5. Thống kê số lượng sản phẩm theo từng phân loại (category)
SELECT c.category_id, c.category_name, COUNT(pc.product_id) AS product_count
FROM category c
LEFT JOIN product_category pc ON c.category_id = pc.category_id
GROUP BY c.category_id, c.category_name
ORDER BY product_count DESC;

-- 6. Thống kê số lượng sản phẩm theo từng nước xuất xứ của thương hiệu
SELECT b.country_of_origin, COUNT(p.product_id) AS product_count
FROM brand b
JOIN product p ON b.brand_id = p.brand_id
GROUP BY b.country_of_origin
ORDER BY product_count DESC;

-- 7. Liệt kê 3 thương hiệu có doanh thu cao nhất và số sản phẩm đã bán của mỗi thương hiệu
WITH BrandSales AS (
    SELECT
        b.brand_id,
        b.brand_name,
        SUM(od.sub_total) AS total_revenue,
        SUM(od.order_quantity) AS total_sold
    FROM brand b
    JOIN product p ON b.brand_id = p.brand_id
    JOIN variant v ON p.product_id = v.product_id
    JOIN orderdetail od ON v.variant_id = od.variant_id
    GROUP BY b.brand_id, b.brand_name
)
SELECT *
FROM BrandSales
ORDER BY total_revenue DESC
LIMIT 3;

-- 8. Liệt kê các thương hiệu có tổng số lượng tồn kho của tất cả sản phẩm lớn hơn 100
SELECT b.brand_id, b.brand_name, SUM(v.stock_quantity) AS total_stock
FROM brand b
JOIN product p ON b.brand_id = p.brand_id
JOIN variant v ON p.product_id = v.product_id
GROUP BY b.brand_id, b.brand_name
HAVING SUM(v.stock_quantity) > 100;

-- 9. Sử dụng function: Lấy trung bình đánh giá của một sản phẩm 
SELECT product_id, product_name, get_average_rating(product_id) AS avg_rating
FROM product
ORDER BY avg_rating DESC
LIMIT 10;

-- 10. FUNCTION: Trả về tổng doanh thu của một thương hiệu theo brand_id
SELECT brand_id, brand_name, brand_revenue(brand_id) AS total_revenue
FROM brand
ORDER BY total_revenue DESC
LIMIT 5;
