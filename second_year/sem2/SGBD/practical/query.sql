create database Tournaments

use Tournaments

create table Courts(
	cid int not null primary key identity(1,1),
	s_type nvarchar(50) not null,
	capacity int not null
);

create table Players(
	pid int not null primary key identity(1,1),
	pname nvarchar(50) not null,
	country nvarchar(20) not null,
	ranking nvarchar(50) not null,
);

create table Chiefs(
	chid int not null primary key identity(1,1),
	[name] nvarchar(20) not null,
	[nationality] nvarchar(20) not null
);

create table Matches(
	mid int not null primary key identity(1,1),
	cid int not null references Courts(cid),
	chid int not null references Chiefs(chid),
	player1 int not null references Players(pid),
	player2 int not null references Players(pid),
	[date] datetime not null,
	[round] nvarchar(50) not null,
	flag bit not null
);

create table [Sets](
	[sid] int not null primary key identity(1,1),
	mid int not null references Matches(mid),
	set_number int not null,
	player1_score int not null,
	player2_score int not null
);

create table Coaches(
	ccid int not null primary key identity(1,1),
	[name] nvarchar(50) not null
);

create table Coaches_Players(
	ccid int not null references Coaches(ccid),
	pid int not null references PLayers(pid),
	[role] nvarchar(50) not null,
	constraint PK_Coaches_Players primary key(ccid, pid)
);

