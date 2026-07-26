create database BookingDB
use BookingDB

create table [User] (
	id int not null primary key identity(1,1),
	username nvarchar(20) not null,
	membershipType nvarchar(20) not null check(membershipType in ('Basic', 'Premium')),
);

create table Class (
	id int not null primary key identity(1,1),
	className nvarchar(10) not null,
	instructorName nvarchar(20) not null,
	classDate datetime not null,
	maxCapacity int not null,
);

create table Booking (
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	classId int not null references Class(id),
	bookedAt datetime not null,
	cancelled bit
);

create table WaitList (
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	classId int not null references Class(id),
	addedAt datetime not null
);