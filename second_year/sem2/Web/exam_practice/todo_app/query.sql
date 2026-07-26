create database TaskManagement

use TaskManagement

create table [User](
	id int not null primary key identity(1,1),
	username nvarchar(50)
);

create table Task(
	id int not null primary key identity(1,1),
	title nvarchar(50),
	[status] nvarchar(50) check ([status] in ('todo', 'in_progress', 'done')),
	assignedTo int references [User](id),
	lastUpdated datetime
);

create table TaskLog(
	id int not null primary key identity(1,1),
	taskId int references Task(id),
	userId int references [User](id),
	oldStatus nvarchar(50),
	newStatus nvarchar(50),
	[timestamp] datetime
);