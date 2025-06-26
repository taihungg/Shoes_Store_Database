-- Indexes trên các cột khóa ngoại
CREATE INDEX idx_product_brand_id ON product(brand_id);
CREATE INDEX idx_variant_product_id ON variant(product_id);
CREATE INDEX idx_order_customer_id ON "order"(customer_id);
CREATE INDEX idx_order_employee_id ON "order"(last_updated_by_employee_id);
CREATE INDEX idx_orderdetail_order_id ON orderdetail(order_id);
CREATE INDEX idx_orderdetail_variant_id ON orderdetail(variant_id);
CREATE INDEX idx_status_history_order_id ON status_history(order_id);
CREATE INDEX idx_status_history_employee_id ON status_history(employee_id);
CREATE INDEX idx_product_category_category_id ON product_category(category_id);

-- Indexes trên các cột tìm kiếm/lọc phổ biến
CREATE INDEX idx_product_product_name ON product(product_name);
CREATE INDEX idx_product_selling_price ON product(selling_price);
CREATE INDEX idx_order_order_date ON "order"(order_date);
CREATE INDEX idx_order_status ON "order"(status);

