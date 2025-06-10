CREATE TABLE customer (
	customer_id INTEGER NOT NULL,
	first_name VARCHAR(30) NOT NULL,
	last_name VARCHAR(30) NOT NULL,
	address VARCHAR(50) NOT NULL,
	city VARCHAR(30) NOT NULL,
	district VARCHAR(30),
	phone_number VARCHAR(30) NOT NULL,
	email VARCHAR(50) NOT NULL,
	credit_card VARCHAR(30) NOT NULL,
	dob DATE NOT NULL,
	gender CHAR(1) CHECK (gender IN ('F', 'M')),
	username VARCHAR(30) NOT NULL,
	password VARCHAR(20) NOT NULL,
	CONSTRAINT pk_customer_id PRIMARY KEY (customer_id)
);