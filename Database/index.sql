CREATE INDEX idx_order_status_date ON "order"(status, order_date ASC);
CREATE INDEX idx_order_customer_date ON "order"(customer_id, order_date DESC);
CREATE INDEX idx_variant_product_stock ON variant(product_id, stock_quantity);
CREATE INDEX idx_variant_size ON variant(size);