CREATE DATABASE CalisthenicsShop

CREATE TABLE Type(
	Tid int IDENTITY(1,1) PRIMARY KEY,
	Name varchar(50) NOT NULL,
	Description varchar(256) NULL
)

CREATE TABLE Item(
	Iid int IDENTITY(1,1) PRIMARY KEY,
	Tid int NOT NULL,
	Name varchar(50) NOT NULL,
	Price int NOT NULL,
	CONSTRAINT FK_Type_Item FOREIGN KEY (Tid) REFERENCES Type(Tid)
)

CREATE TABLE Av_Country(
	Name varchar(50) NOT NULL PRIMARY KEY
)

CREATE TABLE Customer(
	Email varchar(50) NOT NULL PRIMARY KEY,
	Name varchar(50) NOT NULL,
	Password varchar(50) NOT NULL,
	Country varchar(50) NOT NULL,
	City varchar(50) NULL,
	Age int NOT NULL,
	Billing_Address varchar(256) NOT NULL,
	CONSTRAINT FK_Country_User FOREIGN KEY(Country) REFERENCES Av_Country(Name)
)

CREATE TABLE Review(
	Rid int IDENTITY(1,1) PRIMARY KEY,
	Uid varchar(50) NOT NULL,
	Stars int NULL,
	Description varchar(256) NULL,
	CONSTRAINT FK_Customer_Review FOREIGN KEY(Uid) REFERENCES Customer(Email)
)

CREATE TABLE Cart(
	Cid varchar(50) NOT NULL PRIMARY KEY,
	CONSTRAINT FK_Customer_Cart FOREIGN KEY (Cid) REFERENCES Customer(Email)
)

CREATE TABLE Pref_Language(
	LanguageName varchar(50) NOT NULL PRIMARY KEY
)

CREATE TABLE Delivery_Service(
	Sid int IDENTITY(1,1) PRIMARY KEY,
	Name varchar(50) NOT NULL,
	Website varchar(256) NULL
)

CREATE TABLE [Order] (
	Oid varchar(50) NOT NULL PRIMARY KEY,
	Sid int NOT NULL,
	Delivery_Address varchar(256) NOT NULL,
	Status varchar(20) NOT NULL,
	CONSTRAINT FK_DeliveryServices_Order FOREIGN KEY(Sid) REFERENCES Delivery_Service(Sid),
	CONSTRAINT FK_Cart_Order FOREIGN KEY(Oid) REFERENCES Cart(Cid)
)

CREATE TABLE Cart_Item(
	Cid varchar(50) NOT NULL,
	Iid int NOT NULL,
	Quantity int NOT NULL,
	CONSTRAINT FK_Cart_CartItem FOREIGN KEY(Cid) REFERENCES Cart(Cid),
	CONSTRAINT FK_Item_CartItem FOREIGN KEY(Iid) REFERENCES Item(Iid),
	CONSTRAINT PK_CartItem PRIMARY KEY (Cid, Iid)
)