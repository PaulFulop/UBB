create database IdeasDB

use IdeasDB

create table [User] (
	id int not null primary key identity(1,1),
	username nvarchar(50) not null,
	lastSeen dateTime not null
);


create table Idea (
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	title nvarchar(50) not null,
	body nvarchar(100) not null,
	postedAt datetime not null,
	votes nvarchar(9) not null
)

create table Comment (
	id int not null primary key identity(1,1),
	ideaId int not null references Idea(id),
	userId int not null references [User](id),
	body nvarchar(100) not null,
	postedAt datetime not null,
)