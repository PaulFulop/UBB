CREATE TABLE Do_Procedures(
[ProcId] INT IDENTITY(1,1),
[Name] varchar(50) NOT NULL,
PRIMARY KEY([ProcId])
)

CREATE TABLE Undo_Procedures(
[ProcId] INT IDENTITY(1,1),
[Name] varchar(50) NOT NULL,
PRIMARY KEY([ProcId])
)


GO
-- 1

-- a
CREATE PROCEDURE AlterNameColumn
AS
BEGIN
	ALTER TABLE [Cart]
	ALTER COLUMN [Name] NVARCHAR(255)
END;
GO

CREATE PROCEDURE UndoNameColumn
AS
BEGIN
	ALTER TABLE [Cart]
	ALTER COLUMN [Name] varchar(50)
END;
GO

-- EXEC AlterNameColumn
-- EXEC UndoNameColumn

-- b
CREATE PROCEDURE AddRandomColumn
AS
BEGIN
	ALTER TABLE [Cart]
	ADD [Random] bit
END;
GO


CREATE PROCEDURE RemoveRandomColumn
AS
BEGIN
	ALTER TABLE [Cart]
	DROP COLUMN [Random]
END;
GO

--EXEC AddRandomColumn
--EXEC RemoveRandomColumn

-- c
CREATE PROCEDURE AddDefaultNameConstraint -- name is int so
AS
BEGIN
	ALTER TABLE [Cart]
	ADD CONSTRAINT default_name DEFAULT 1 FOR [Name]
END;
GO

CREATE PROCEDURE RemoveDefaultNameConstraint -- name is int so
AS
BEGIN
	ALTER TABLE [Cart]
	DROP CONSTRAINT default_name
END;
GO

--INSERT INTO [Cart] ([Cid]) VALUES ('ioana@gmail.com')
--DELETE FROM [Cart] WHERE [Cid] = 'ioana@gmail.com'
--EXEC AddDefaultNameConstraint
--EXEC RemoveDefaultNameConstraint

-- d

CREATE TABLE Employees (
Eid int NOT NULL,
[Name] varchar(50),
Salary int NOT NULL
)

INSERT INTO Employees VALUES (1, 'Cosmin', 5000)
SELECT * FROM Employees

GO
CREATE PROCEDURE AddEmployeePK
AS
BEGIN
	ALTER TABLE [Employees]
	ADD CONSTRAINT pk_Employee PRIMARY KEY (Eid)
END;
GO

CREATE PROCEDURE RemoveEmployeePK
AS
BEGIN
	ALTER TABLE [Employees]
	DROP CONSTRAINT pk_Employee
END;
GO

--EXEC AddEmployeePK
--EXEC RemoveEmployeePK

-- e

CREATE PROCEDURE AddUniqueCartName
AS
BEGIN
	ALTER TABLE [Cart]
	ADD CONSTRAINT uk_Name UNIQUE([Name])
END;
GO

CREATE PROCEDURE RemoveUniqueCartName
AS
BEGIN
	ALTER TABLE [Cart]
	DROP CONSTRAINT uk_Name
END;
GO

--INSERT INTO [Drops] VALUES ('summer drop', 1)
--INSERT INTO [Drops] VALUES ('winter drop', 1)
--SELECT * FROM [Drops]

--EXEC AddUniqueCartName
--EXEC RemoveUniqueCartName

INSERT INTO Do_Procedures VALUES ('AddUniqueDropName')
INSERT INTO Undo_Procedures VALUES ('RemoveUniqueDropName')
GO
-- f

CREATE PROCEDURE AddCartFK
AS
BEGIN
	ALTER TABLE [Cart]
	ADD CONSTRAINT FK_Customer_Cart FOREIGN KEY(Cid) REFERENCES Customer(Email)
END;
GO

CREATE PROCEDURE RemoveCartFK
AS
BEGIN
	ALTER TABLE [Cart]
	DROP CONSTRAINT FK_Customer_Cart 
END;
GO

--EXEC AddCartFK
--EXEC RemoveCartFK

INSERT INTO Do_Procedures VALUES ('AddCartFK')
INSERT INTO Undo_Procedures VALUES ('RemoveCartFK')
GO
-- g

CREATE PROCEDURE CreateDropsTable
AS
BEGIN
CREATE TABLE Drops(
Did int PRIMARY KEY IDENTITY(1,1),
[Name] varchar(50),
Upcoming bit
)
END;
GO

CREATE PROCEDURE DropDropsTable
AS
DROP TABLE [Drops]
GO

--EXEC CreateDropsTable
--EXEC DropDropsTable

-- 2

SELECT * FROM Do_Procedures
SELECT * FROM Undo_Procedures

UPDATE Undo_Procedures
SET [Name] = 'RemoveUniqueCartName'
WHERE [ProcId] = 5

CREATE TABLE [Version](
[version] int 
)

SELECT * FROM [Version]
INSERT INTO [Version] VALUES (0) -- default version
GO

GO
ALTER PROCEDURE main 
	@toVersion INT
AS
BEGIN
	DECLARE @currentVer INT = (SELECT TOP 1 [version] FROM [Version]) -- i always have 1 row
	DECLARE @procName varchar(50)
	DECLARE @sql nvarchar(100)
	DECLARE @procId INT

	IF @currentVer > @toVersion 
	BEGIN
		DECLARE cs_undo CURSOR SCROLL FOR (SELECT [Name] FROM Undo_Procedures)
		OPEN cs_undo

		FETCH ABSOLUTE @currentVer FROM cs_undo INTO @procName
		SET @sql = 'EXEC ' + @procName
		EXEC sp_executesql @sql

		WHILE @currentVer != @toVersion AND @@FETCH_STATUS = 0
		BEGIN
			 FETCH RELATIVE -1 FROM cs_undo INTO @procName;
			 SET @sql = 'EXEC ' + @procName
			 EXEC sp_executesql @sql
			 SET @currentVer = @currentVer - 1
		END

		CLOSE cs_undo
		DEALLOCATE cs_undo
	END
	ELSE
	BEGIN
		IF @currentVer != @toVersion
		BEGIN
			DECLARE cs_do CURSOR SCROLL FOR (SELECT [Name] FROM Do_Procedures)
			OPEN cs_do

			SET @currentVer = @currentVer + 1
			FETCH ABSOLUTE @currentVer FROM cs_do INTO @procName
			SET @sql = 'EXEC ' + @procName
			EXEC sp_executesql @sql

			WHILE @currentVer != @toVersion AND @@FETCH_STATUS = 0
			BEGIN
				SET @currentVer = @currentVer + 1
				FETCH RELATIVE 1 FROM cs_do INTO @procName
				SET @sql = 'EXEC ' + @procName
				EXEC sp_executesql @sql
			END

			CLOSE cs_do
			DEALLOCATE cs_do
		END
	END

	UPDATE [Version]
	SET [version] = @toVersion
END;
GO

EXEC main 0
SELECT * FROM [Cart]
SELECT * FROM [Version]

UPDATE [Version]
SET [version] = 7