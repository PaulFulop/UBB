create database GymDB

use GymDB

create table [User] (
	id int not null primary key identity(1,1),
	username nvarchar(50) not null,
	[fitnessGoal] nvarchar(50) not null
);

create table [Move] (
	id int not null primary key identity(1,1),
	[name] nvarchar(50) not null,
	difficulty int not null check(difficulty in (1,2,3)),
	musclegroup nvarchar(50) not null
);

create table [Session] (
	id int not null primary key identity(1,1),
	userId int not null references [User](id),
	moveId int not null references [Move](id),
	completed bit not null
);