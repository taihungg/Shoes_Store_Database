# Shoes_Store_Database
Project Database Lab 2024.2

Import shoestore database in PostgreSQL:

To import a database, the following methods can be used:

--- METHOD 1: using client tool applications ----
=================================================

0. Open terminal, move to the bin directory in the PostgreSQL Installation Directory

1. create an admin user for shoestore database

	./createuser -h localhost -p 5432 -U postgres -P admin_shoestore

2. drop shoestore database if it exists

	./dropdb -h localhost -p 5432 -U postgres shoestore 

3. create a database named shoestore, its ownwer is admin_shoestore

	./createdb -h localhost -p 5432 -U postgres -O admin_shoestore  shoestore

4. Connect to the database shoestore on the server (localhost) using admin_shoestore account

	./psql -h localhost -p 5432 -f <pathfile to dellstore2-normal-1.0.sql> shoestore admin_shoestore 

	Vi du:
	./psql -h localhost -p 5432 -f ~/shoestore.sql shoestore admin_shoestore  


5. Connect to the database "shoestore" and see the database content


--- METHOD 2: executing commands in psql ----
=================================================

0. Connect to the server via psql using superuser postgres

	psql –h localhost  postgres postgres

1. Execute the following commands in psql:
	1.1 Create a new database "shoestore"

		create database shoestore;

	1.2 Create a new user "admin_shoestore" with password "486405"

		create role admin_shoestore login password '486405';

	1.3 Give all privilliges on the database "dellstore" to the user "admin_shoestore"

		grant all PRIVILEGES on database dellstore to admin_shoestore;
		grant all privileges on schema public to admin_shoestore;

	1.4 Connect to the "shoestore" database using the new user "admin_shoestore"

		\c shoestore admin_shoestore 

	1.5 Execute all commands in the "shoestore.sql" file:
		\i <pathfile to shoestore.sql> 
		(E.g. \i ‘C:Documents\\shoestore.sql’)

	1.6 Connect to the database "shoestore" and see the database content
