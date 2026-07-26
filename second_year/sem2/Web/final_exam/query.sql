create database ExamDB

use ExamDB

create table [Users] (
	id int not null primary key identity(1,1),
	username nvarchar(20) not null
);

create table Ingredient (
	id int not null primary key identity(1,1),
	[name] nvarchar(20) not null,
	unit nvarchar(50) not null,
	caloriesPer100g int not null
);

create table Recipe (
	id int not null primary key identity(1,1),
	userId int not null references [Users](id),
	title nvarchar(20) not null,
	totalCalories int not null
);

create table RecipeStep (
	id int not null primary key identity(1,1),
	recipeId int not null references Recipe(id),
	stepNumber int not null,
	[description] nvarchar(20) not null,
	ingredientIds nvarchar(50) not null
);

select * from Users
select * from Recipe
select * from RecipeStep