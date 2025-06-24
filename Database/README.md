# Shoes_Store_Database
Project Database Lab 2024.2

Import shoestore database in PostgreSQL:

To import a database, the following methods can be used:

--- METHOD 1: executing commands in psql ----
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

	1.5 Execute all commands in the "createtable.sql" file:
		\i <pathfile to createtable.sql> 
		(E.g. \i C:/Users/admin/Desktop/createtable.sql)

	1.6 Execute all commands in the "shoestore.sql" file:
		\i <pathfile to shoestore.sql> 
		(E.g. \i C:/Users/admin/Desktop/shoestore.sql)

	1.6 Connect to the database "shoestore" and see the database content

--- METHOD 2: using restore database in PgAdmin4 ----
=================================================
0. Connect to the PgAdmin4
1. Restore database
	1.1 Create new user "admin_shoestore"
	1.2 Create new database "shoestore"
		Choose it's owner is "admin_shoestore"
	1.3 Restore for database "shoestore"
		Left click on "shoestore"
		Choose "Restore"
		Choose directory of file "backupdtb.backup"
		Click "Restore"
		Done!