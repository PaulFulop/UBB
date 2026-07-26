go
create database MiniFacebook;

use MiniFacebook


create table Users (
	[uid] int not null primary key identity(1,1),
	[name] nvarchar(50),
	city nvarchar(50) not null,
	birth_date datetime not null
);

create table Categories (
	cid int not null primary key identity(1,1),
	[description] nvarchar(250) not null
);

create table Pages (
	pid int not null primary key identity(1,1),
	cid int not null references Categories(cid),
	[name] nvarchar(50) not null
);

create table Likes (
	[uid] int not null references Users([uid]),
	pid int not null references Pages(pid),
	[date] datetime not null,
	constraint PK_uid_pid primary key([uid], pid)
);


create table Posts (
	poid int not null primary key identity(1,1),
	[uid] int not null references Users([uid]),
	[date] datetime not null,
	[text] nvarchar(100) not null,
	shares int not null
);

create table Comments (
	coid int not null primary key identity(1,1),
	poid int not null references Posts(poid),
	[text] nvarchar(100) not null,
	[date] datetime not null,
	[top] bit not null
);

