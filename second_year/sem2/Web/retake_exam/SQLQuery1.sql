create database RetakeDB

use RetakeDB

create table [User](
	id int not null primary key identity(1,1),
	username nvarchar(20) not null,
	lastSeen datetime not null
);

create table Item(
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	title nvarchar(20) not null,
	[description] nvarchar(50) not null,
	startingPrice int not null,
	currentPrice int not null
);

create table Bid(
	id int not null primary key identity(1,1),
	itemId int not null references Item(id),
	userId int not null references [User](id),
	amount int not null,
	placedAt datetime not null
);