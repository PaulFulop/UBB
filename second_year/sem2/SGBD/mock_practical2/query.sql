create database HospitalDB

use HospitalDB

create table Doctor (
	did int not null primary key identity(1,1),
	[name] nvarchar(50) not null,
	date_of_birth datetime not null,
	specialties nvarchar(200) not null,
);

create table Treatment (
	tid int not null primary key identity(1,1),
	[name] nvarchar(50) not null,
);

create table Patient (
	pid int not null primary key identity(1,1),
	did int not null references Doctor(did),
	f_name nvarchar(50) not null,
	l_name nvarchar(50) not null,
	[address] nvarchar(100) not null,
	phone_number nvarchar(50) not null
);

create table Patient_Treatment (
    pid     int     not null references Patient(pid),
    tid     int     not null references Treatment(tid),
    constraint PK_Patient_Treatment primary key(pid, tid)
);


create table Nurse (
	nid int not null primary key identity(1,1),
	did int not null references Doctor(did),
	[name] nvarchar(50) not null,
	date_of_birth datetime not null,
);

create table Appointment (
	aid int not null primary key identity(1,1),
	pid int not null references Patient(pid),
	did int not null references Doctor(did),
	[date] datetime not null,
	reason nvarchar(100) not null,
);

create table Medication (
	mid int not null primary key identity(1,1),
	[name] nvarchar(50) not null,
	instructions nvarchar(150) not null,
);

create table Treatment_Medication(
	tid int not null references Treatment(tid),
	mid int not null references Medication(mid),
	dosage int not null,
	constraint PK_Treatment_Medication primary key(tid, mid)
);

create table Payment(
	pmid int not null primary key identity(1,1),
	pid int not null references Patient(pid),
	method nvarchar(50),
	[date] datetime not null,
	status nvarchar(20) not null
);