create database HotelDB

use HotelDB

create table [User] (
	id int not null primary key identity(1,1),
	username nvarchar(50) not null,
	[password] nvarchar(50) not null
);

create table HotelRoom (
	id int not null primary key identity(1,1),
	roomNumber nvarchar(10),
	capacity int not null,
	basePrice int not null
);

create table Reservation (
	id int not null primary key identity(1,1),
	userId int references [User](id),
	roomId int references HotelRoom(id),
	checkInDate datetime not null,
	checkOutDate datetime not null,
	numberOfGuests int not null,
	totalPrice int not null
);