create database ShopDB

use ShopDB

create table [User](
	id int not null primary key identity(1,1),
	username nvarchar(50)
);

create table [Product](
	id int not null primary key identity(1,1),
	[name] nvarchar(50),
	price decimal
);

create table [Order] (
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	totalPrice decimal
);

create table OrderItem (
	id int not null primary key identity(1,1),
	orderId int not null references [Order](id),
	productId int not null references [Product](id),
);