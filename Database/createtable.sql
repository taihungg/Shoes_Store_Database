CREATE TABLE customer (
	customer_id CHAR(8) PRIMARY KEY,
	first_name VARCHAR(30) NOT NULL,
	last_name VARCHAR(30),
	address VARCHAR(50),
	city VARCHAR(30),
	district VARCHAR(30),
	phone_number VARCHAR(10) UNIQUE NOT NULL,
	email VARCHAR(40) UNIQUE,
	credit_card VARCHAR(30),
	dob DATE,
	gender CHAR(1) CHECK (gender IN ('F', 'M')),
	username VARCHAR(30) UNIQUE NOT NULL,
	password VARCHAR(20) NOT NULL
);

CREATE TABLE category (
    category_id CHAR(4) PRIMARY KEY,
    category_name VARCHAR(30) NOT NULL
);

CREATE TABLE brand (
    brand_id CHAR(4) PRIMARY KEY,
    brand_name CHAR(100) NOT NULL,
    country_of_origin VARCHAR(40),
    brand_description TEXT
);

CREATE TABLE product (
    product_id CHAR(8) PRIMARY KEY,
    category_id CHAR(4),
    brand_id CHAR(4),
    product_name VARCHAR(200) NOT NULL,
    purchase_price DECIMAL(10,2) NOT NULL,
    selling_price DECIMAL(10,2) NOT NULL,
	material VARCHAR(50),
	product_description TEXT,
	average_rating DECIMAL(2,1) DEFAULT 0.0,
	CONSTRAINT fk_category_id FOREIGN KEY (category_id) REFERENCES category(category_id),
	CONSTRAINT fk_brand_id FOREIGN KEY (brand_id) REFERENCES brand(brand_id)
);

CREATE TABLE variant (
	variant_id CHAR(8) PRIMARY KEY,
	product_id CHAR(8) NOT NULL,
	color VARCHAR(20) NOT NULL,
	size DECIMAL(3,1) NOT NULL,
	stock_quantity INTEGER NOT NULL,
	CONSTRAINT fk_product_id FOREIGN KEY (product_id) REFERENCES product(product_id)
);

CREATE TABLE employee (
	employee_id CHAR(8) PRIMARY KEY,
	first_name VARCHAR(20),
	last_name VARCHAR(20),
	dob DATE,
	phone_number CHAR(10),
	email VARCHAR(40),
	username VARCHAR(30) UNIQUE NOT NULL,
	password VARCHAR(20) NOT NULL
);

CREATE TABLE "order" (
	order_id CHAR(8) PRIMARY KEY,
	customer_id CHAR(8) NOT NULL,
	employee_id CHAR(8),
	total_amount DECIMAL(10,2) DEFAULT 0.0,
	total_discount DECIMAL(10,2) DEFAULT 0.0,
	final_amount DECIMAL(10,2) DEFAULT 0.0,
	order_date DATE,
	status VARCHAR(20) CHECK (status IN ('PENDING', 'PACKAGING', 'ON DELIVERY', 'DELIVERED', 'CANCELLED')) DEFAULT 'PENDING',
	payment_method VARCHAR(20) CHECK (payment_method IN ('CASH', 'CREDIT CARD', 'VISA CARD', 'E-WALLET', 'BANK TRANSFER')) DEFAULT 'CASH',
	note TEXT,
	CONSTRAINT fk_customer_id FOREIGN KEY (customer_id) REFERENCES customer(customer_id),
	CONSTRAINT fk_employee_id FOREIGN KEY (employee_id) REFERENCES employee(employee_id)
);

CREATE TABLE orderdetail (
	orderdetail_id CHAR(8) PRIMARY KEY,
	order_id CHAR(8) NOT NULL,
	variant_id CHAR(8) NOT NULL,
	order_quantity INTEGER NOT NULL,
	unit_price DECIMAL(10,2) DEFAULT 0.0,
	discount DECIMAL(10,2) DEFAULT 0.0,
	sub_total DECIMAL(10,2) DEFAULT 0.0,
	CONSTRAINT fk_order_id FOREIGN KEY (order_id) REFERENCES "order"(order_id),
	CONSTRAINT fk_variant_id FOREIGN KEY (variant_id) REFERENCES variant(variant_id)
);

CREATE TABLE feedback (
	feedback_id CHAR(8) PRIMARY KEY,
	orderdetail_id CHAR(8) NOT NULL,
	feedback TEXT,
	rating DECIMAL(1,0),
	feedback_date DATE,
	CONSTRAINT fk_orderdetail_id FOREIGN KEY (orderdetail_id) REFERENCES orderdetail(orderdetail_id)
);
