-- CREATING THE TABLE STRUCTURE

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRuns]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tests]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Views]

GO



CREATE TABLE [Tables] (

	[TableID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunTables] (

	[TestRunID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunViews] (

	[TestRunID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRuns] (

	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,

	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,

	[StartAt] [datetime] NULL ,

	[EndAt] [datetime] NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestTables] (

	[TestID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[NoOfRows] [int] NOT NULL ,

	[Position] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestViews] (

	[TestID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Tests] (

	[TestID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Views] (

	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



ALTER TABLE [Tables] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 

	(

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Tests] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 

	(

		[TestID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Views] WITH NOCHECK ADD 

	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 

	(

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] ADD 

	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestRunViews] ADD 

	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestTables] ADD 

	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestViews] ADD 

	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	),

	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	)

GO

-- TABLES: Customer (one pk, no fk), Review (one pk, at least one fk), Cart_Item (multi-column pk)


-- CREATING THE VIEWS

-- -> see only the equipment and accesorries in the shop
ALTER VIEW Equipment_Accessories_View AS
SELECT [Name] FROM Item 
WHERE Tid = 1 OR Tid = 3 
GO

-- -> see all customers but also the ones that have placed an order
ALTER VIEW Customer_OrderStatus_View AS
SELECT c.[Email], o.[Status]
FROM Customer as c
LEFT JOIN [Order] as o ON o.[Oid] = c.[Email]
GO

-- -> see all items but also see the total quantity in all the carts 
ALTER VIEW Items_TotalCartQuantity_View AS
SELECT i.[Name], SUM(ci.[Quantity]) as [In Carts]
FROM Cart_Item as ci
RIGHT JOIN Item as i ON i.[Iid] = ci.[Iid]
GROUP BY i.[Name]
GO 





-- INITIALIZING DATA

INSERT INTO Tables VALUES ('Customer'), ('Review'), ('Cart_Item')
SELECT * FROM Tables
DBCC CHECKIDENT ('Tables', RESEED, 0);
DELETE FROM Tables

INSERT INTO Views VALUES ('Equipment_Accessories_View'), ('Customer_OrderStatus_View'), ('Items_TotalCartQuantity_View')
SELECT * FROM Views

-- Tests: Should represent complete test scenarios
DELETE FROM Tests;
SELECT * FROM Tests
INSERT INTO Tests VALUES 
    ('Test_Small_100'),      -- Test with 100 rows
    ('Test_Medium_500'),     -- Test with 500 rows
    ('Test_Large_1000');     -- Test with 1000 rows

-- TestTables: Link tests to tables with their order and row counts
-- Position determines INSERT order (and reverse for DELETE)

DELETE FROM TestTables;
SELECT * FROM TestTables

-- TestTables: Link tests to tables with their order and row counts
-- Position determines INSERT order (and reverse for DELETE)

-- Test 1: SMALL (100 rows scale)
INSERT INTO TestTables VALUES 
    (1, 1, 100, 1),  -- Test 1: Customer, 100 rows, position 1
    (1, 2, 50, 2),   -- Test 1: Review, 50 rows, position 2
    (1, 3, 10, 3);   -- Test 1: Cart_Item, 10 rows, position 3

-- Test 2: MEDIUM (500 rows scale)
INSERT INTO TestTables VALUES 
    (2, 1, 500, 1),   -- Test 2: Customer, 500 rows, position 1
    (2, 2, 250, 2),   -- Test 2: Review, 250 rows, position 2
    (2, 3, 50, 3);    -- Test 2: Cart_Item, 50 rows, position 3

-- Test 3: LARGE (1000 rows scale)
INSERT INTO TestTables VALUES 
    (3, 1, 1000, 1),  -- Test 3: Customer, 1000 rows, position 1
    (3, 2, 500, 2),   -- Test 3: Review, 500 rows, position 2
    (3, 3, 100, 3);   -- Test 3: Cart_Item, 100 rows, position 3



DELETE FROM TestViews;
SELECT * FROM TestViews;

-- TestViews: Link tests to views (all tests evaluate all views)
INSERT INTO TestViews VALUES 
    (1, 1), (1, 2), (1, 3),  -- Test 1 evaluates all 3 views
    (2, 1), (2, 2), (2, 3),  -- Test 2 evaluates all 3 views
    (3, 1), (3, 2), (3, 3);  -- Test 3 evaluates all 3 views





-- PROCEDURES

-- REMOVE -> run_remove_test(test_id) -> looks in table values where test_id matches -> gets the table name from there, and does a remove on them 
--										in descending order

GO
ALTER PROCEDURE run_remove_test
	@test_id int
AS
BEGIN
	DECLARE @table_name nvarchar(50)
	DECLARE @sql nvarchar(100)

-- look for the table names that correspond for the test id, order desc

	DECLARE remove_cursor CURSOR FOR 
		SELECT t.[Name] FROM 
		[TestTables] as tt
		INNER JOIN [Tables] as t
		ON tt.TableID = t.TableID WHERE tt.TestID = @test_id
		ORDER BY tt.Position DESC

	OPEN remove_cursor

-- delete everything from the tables in descending order

	FETCH NEXT FROM remove_cursor INTO @table_name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @sql = 'DELETE FROM ' + @table_name
		EXEC sp_executesql @sql
		FETCH NEXT FROM remove_cursor INTO @table_name
	END

	CLOSE remove_cursor
	DEALLOCATE remove_cursor
END
GO


-- INSERT TABLES -> insert_tables(test_id):
ALTER PROCEDURE insert_tables
	@test_id int
AS
BEGIN
	DECLARE @table_name nvarchar(50)
	DECLARE @no_of_rows int
	DECLARE @sql nvarchar(100)
	DECLARE @start_time datetime2
	DECLARE @end_time datetime2
	DECLARE @test_run_id int
	DECLARE @table_id int

-- Get the current TestRunID
    SELECT @test_run_id = MAX(TestRunID) FROM TestRuns;

-- look for the table names that correspond for the test id, order asc
	DECLARE insert_cursor CURSOR FOR 
		SELECT t.[TableID], t.[Name], tt.[NoOfRows] FROM 
		[TestTables] as tt
		INNER JOIN [Tables] as t
		ON tt.TableID = t.TableID WHERE tt.TestID = @test_id
		ORDER BY tt.Position

	OPEN insert_cursor

	FETCH NEXT FROM insert_cursor INTO @table_id, @table_name, @no_of_rows
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @start_time = SYSUTCDATETIME()
		EXEC insert_table @table_name, @no_of_rows
		SET @end_time = SYSUTCDATETIME()
		
		INSERT INTO TestRunTables VALUES (@test_run_id, @table_id, @start_time, @end_time)
		FETCH NEXT FROM insert_cursor INTO @table_id, @table_name, @no_of_rows
	END

	CLOSE insert_cursor
	DEALLOCATE insert_cursor
END
GO


-- INSERT INTO TABLE -> insert_table(table_name, no_of_rows): TO BE SEEN TOMORROW

ALTER PROCEDURE insert_table 
	@table_name nvarchar(50),
	@no_of_rows int
AS
BEGIN
    DECLARE @ColumnName NVARCHAR(100);
    DECLARE @DataType NVARCHAR(50);
    DECLARE @IsNullable NVARCHAR(3);
    DECLARE @IsIdentity BIT;
    DECLARE @IsPrimaryKey BIT;
    DECLARE @IsForeignKey BIT;
    DECLARE @FKTable NVARCHAR(128);
    DECLARE @FKColumn NVARCHAR(128);
    
    DECLARE @ColumnList NVARCHAR(MAX) = '';
    DECLARE @ValuesList NVARCHAR(MAX) = '';
    DECLARE @SQL NVARCHAR(MAX);
    DECLARE @n INT = 1;

	-- Temporary table to store column metadata
    CREATE TABLE #ColumnInfo (
        ColumnName VARCHAR(100),
        DataType VARCHAR(50),
        IsNullable VARCHAR(3),
        IsIdentity BIT,
        IsPrimaryKey BIT,
        IsForeignKey BIT,
        FKTable VARCHAR(100),
        FKColumn VARCHAR(100),
        OrdinalPosition INT
    );
	
	-- Get column information
	INSERT INTO #ColumnInfo
	SELECT 
		c.COLUMN_NAME,
		c.DATA_TYPE,
		c.IS_NULLABLE,
		COLUMNPROPERTY(OBJECT_ID(@table_name), c.COLUMN_NAME, 'IsIdentity') AS IsIdentity,
		dbo.is_pk(@table_name, c.COLUMN_NAME) AS IsPrimaryKey,
		dbo.is_fk(@table_name, c.COLUMN_NAME) AS IsForeignKey,
		dbo.find_FKTable(@table_name, c.COLUMN_NAME) AS FKTable,
		dbo.find_FKColumn(@table_name, c.COLUMN_NAME) AS FKColumn,
		c.ORDINAL_POSITION
	FROM INFORMATION_SCHEMA.COLUMNS AS c
	WHERE c.TABLE_NAME = @table_name
	ORDER BY c.ORDINAL_POSITION;

	-- Build column list (excluding identity columns)
    SELECT @ColumnList = STRING_AGG(QUOTENAME(ColumnName), ', ')
    FROM #ColumnInfo
    WHERE IsIdentity = 0;

	-- Insert rows
    WHILE @n <= @no_of_rows
	BEGIN
		SET @ValuesList = '';

		-- Build values for this row
        DECLARE col_cursor CURSOR FOR
            SELECT ColumnName, DataType, IsForeignKey, FKTable, FKColumn, IsIdentity
            FROM #ColumnInfo
            WHERE IsIdentity = 0
            ORDER BY OrdinalPosition;

		OPEN col_cursor;
        FETCH NEXT FROM col_cursor INTO @ColumnName, @DataType, @IsForeignKey, @FKTable, @FKColumn, @IsIdentity;

		WHILE @@FETCH_STATUS = 0
		BEGIN
			DECLARE @CurrentValue NVARCHAR(500) = '';
    
			-- Build the current value based on type
			IF @IsForeignKey = 1
			BEGIN
				DECLARE @FKValue NVARCHAR(100);
				DECLARE @FKSql NVARCHAR(500);
				SET @FKSql = 'SELECT TOP 1 @val = CAST(' + QUOTENAME(@FKColumn) + ' AS NVARCHAR(100)) FROM ' + 
							 QUOTENAME(@FKTable) + ' ORDER BY NEWID()';
				EXEC sp_executesql @FKSql, N'@val NVARCHAR(100) OUTPUT', @FKValue OUTPUT;
				IF @FKValue IS NULL
					SET @CurrentValue = 'NULL';
				ELSE IF @DataType IN ('varchar', 'nvarchar', 'char', 'nchar', 'text')
					SET @CurrentValue = '''' + REPLACE(@FKValue, '''', '''''') + '''';  -- Returns: 'Hungary'
				ELSE
					SET @CurrentValue = @FKValue;  -- For numeric FKs like CustomerID
			END
			ELSE IF @DataType IN ('int', 'bigint', 'smallint', 'tinyint')
			BEGIN
				SET @CurrentValue = CAST(@n AS VARCHAR(20));
			END
			ELSE IF @DataType IN ('varchar', 'nvarchar', 'char', 'nchar', 'text')
			BEGIN
				SET @CurrentValue = '''' + @ColumnName + CAST(@n AS VARCHAR(20)) + '''';
			END
			ELSE IF @DataType IN ('datetime', 'datetime2', 'smalldatetime', 'timestamp')
			BEGIN
				SET @CurrentValue = 'GETDATE()';
			END
			ELSE IF @DataType = 'date'
			BEGIN
				SET @CurrentValue = 'CAST(GETDATE() AS DATE)';
			END
			ELSE IF @DataType IN ('decimal', 'numeric', 'float', 'real', 'money')
			BEGIN
				SET @CurrentValue = CAST(@n * 1.5 AS VARCHAR(20));
			END
			ELSE IF @DataType = 'bit'
			BEGIN
				SET @CurrentValue = CAST(@n % 2 AS VARCHAR(1));
			END
			ELSE
			BEGIN
				SET @CurrentValue = 'NULL';
			END
    
			-- NOW add comma if this isn't the first value
			IF @ValuesList != ''
				SET @ValuesList = @ValuesList + ', ';
    
			--THEN append the current value
			SET @ValuesList = @ValuesList + @CurrentValue;
    
			FETCH NEXT FROM col_cursor INTO @ColumnName, @DataType, @IsForeignKey, @FKTable, @FKColumn, @IsIdentity;
		END

		CLOSE col_cursor;
        DEALLOCATE col_cursor;

		 -- Execute INSERT
        SET @SQL = 'INSERT INTO ' + QUOTENAME(@table_name) + ' (' + @ColumnList + ') VALUES (' + @ValuesList + ')';
		EXEC sp_executesql @SQL; 
		SET @n = @n + 1;
	END
	DROP TABLE #ColumnInfo;
END
GO

-- FUNCTION TO DETERMINE THE TABLE NAME THAT CONTAINS THE PK WHICH IS FK (@column_name) IN @table_name
GO
ALTER FUNCTION find_FKTable(@table_name nvarchar(50), @column_name nvarchar(50))
RETURNS nvarchar(128)
AS
BEGIN
	DECLARE @result NVARCHAR(128)
	SELECT TOP 1 @result = OBJECT_NAME(fkc.referenced_object_id)
			FROM sys.foreign_key_columns AS fkc
			WHERE fkc.parent_object_id = OBJECT_ID(@table_name)
			AND COL_NAME(fkc.parent_object_id, fkc.parent_column_id) = @column_name

	RETURN @result
END
GO

-- FUNCTION TO DETERMINE THE COLUMN NAME THAT CONTAINS THE PK WHICH IS FK (@column_name) IN @table_name
GO
ALTER FUNCTION find_FKColumn(@table_name nvarchar(50), @column_name nvarchar(50))
RETURNS nvarchar(128)
AS
BEGIN
	DECLARE @result NVARCHAR(128)
	SELECT TOP 1 @result = COL_NAME(fkc.referenced_object_id, fkc.referenced_column_id)
			FROM sys.foreign_key_columns AS fkc
			WHERE fkc.parent_object_id = OBJECT_ID(@table_name)
			AND COL_NAME(fkc.parent_object_id, fkc.parent_column_id) = @column_name

	RETURN @result
END
GO

-- FUNCTION TO VERIFY IF A COLUMN IN A TABLE IS A PK
GO
ALTER FUNCTION is_pk(@table_name nvarchar(50),@column_name nvarchar(50))
RETURNS BIT
AS
BEGIN
	IF EXISTS(
		SELECT kcu.COLUMN_NAME FROM
	(SELECT * FROM CalisthenicsShop.INFORMATION_SCHEMA.KEY_COLUMN_USAGE) AS kcu
	JOIN (SELECT * FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS) AS tc ON kcu.CONSTRAINT_NAME = tc.CONSTRAINT_NAME
	WHERE tc.TABLE_NAME = @table_name AND kcu.COLUMN_NAME = @column_name AND tc.CONSTRAINT_TYPE = 'PRIMARY KEY')
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO


-- FUNCTION TO VERIFY IF A COLUMN IN A TABLE IS A FK
GO
ALTER FUNCTION is_fk(	@table_name nvarchar(50),@column_name nvarchar(50))
RETURNS BIT
AS
BEGIN
	IF EXISTS(
		SELECT kcu.COLUMN_NAME FROM
	(SELECT * FROM CalisthenicsShop.INFORMATION_SCHEMA.KEY_COLUMN_USAGE) AS kcu
	JOIN (SELECT * FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS) AS tc ON kcu.CONSTRAINT_NAME = tc.CONSTRAINT_NAME
	WHERE tc.TABLE_NAME = @table_name AND kcu.COLUMN_NAME = @column_name AND tc.CONSTRAINT_TYPE = 'FOREIGN KEY')
	BEGIN
		RETURN 1
	END
	RETURN 0
END
GO



-- SELECT -> select_views(test_id): looks in test views, gets the name of the views that are in the given test and does a select on them
--								    also compute the given time it takes to run and insert into TestRunViews

GO
ALTER PROCEDURE run_views_test 
	@test_id int
AS
BEGIN
	DECLARE @view_name nvarchar(50)
	DECLARE @sql nvarchar(100)
	DECLARE @start_time datetime2
	DECLARE @end_time datetime2
	DECLARE @test_run_id INT;
	DECLARE @view_id INT;
    
    -- Get the current TestRunID
    SELECT @test_run_id = MAX(TestRunID) FROM TestRuns;

	-- look for the view names that correspond for the test id
	DECLARE select_cursor CURSOR FOR 
		SELECT v.[ViewID], v.[Name] FROM 
		[TestViews] as tv
		INNER JOIN [Views] as v
		ON tv.ViewID = v.ViewID WHERE tv.TestID = @test_id

	OPEN select_cursor
	
	-- test each select on all the corresponding views and insert into TestRunViews the corresponding values
	FETCH NEXT FROM select_cursor INTO @view_id, @view_name
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @start_time = SYSUTCDATETIME()
		SET @sql = 'SELECT * FROM ' + @view_name
		EXEC sp_executesql @sql
		SET @end_time = SYSUTCDATETIME()

		INSERT INTO TestRunViews VALUES (@test_run_id, @view_id, @start_time, @end_time)

		FETCH NEXT FROM select_cursor INTO @view_id, @view_name
	END
	CLOSE select_cursor
	DEALLOCATE select_cursor
END
GO




-- RUN TEST -> run_test(test_id): get description (name of the test), execute delete, insert,
--									then select using this test_id. also compute the duration of whole test


ALTER PROCEDURE run_test
    @TestID INT
AS
BEGIN
    DECLARE @StartTime DATETIME;
    DECLARE @EndTime DATETIME;
    DECLARE @TestRunID INT;
    DECLARE @Description VARCHAR(255);

    -- Get test description
    SELECT @Description = [Name] FROM Tests WHERE TestID = @TestID;
    
    -- Record overall test start
    SET @StartTime = SYSUTCDATETIME()
    
    -- Insert into TestRuns
    INSERT INTO TestRuns ([Description], StartAt)
    VALUES (@Description, @StartTime);
    
    SET @TestRunID = SCOPE_IDENTITY();
    
    PRINT '========================================';
    PRINT 'Starting Test: ' + @Description;
    PRINT '========================================';
    
    -- PHASE 1: DELETE
    PRINT 'Phase 1: Deleting data...';
    EXEC  run_remove_test @TestID;
    
    -- PHASE 2: INSERT
    PRINT 'Phase 2: Inserting data...';
    EXEC insert_tables @TestID;
    
    -- PHASE 3: EVALUATE VIEWS
    PRINT 'Phase 3: Evaluating views...';
    EXEC run_views_test @TestID;
    
    -- Record overall test end
    SET @EndTime = SYSUTCDATETIME()
    UPDATE TestRuns 
    SET EndAt = @EndTime 
    WHERE TestRunID = @TestRunID;
    
    PRINT '========================================';
    PRINT 'Test Complete! Duration: ' + 
          CAST(DATEDIFF(MILLISECOND, @StartTime, @EndTime) AS VARCHAR(10)) + ' ms';
    PRINT '========================================';
END
GO

EXEC run_test 1;

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews

SELECT * FROM TestTables

SELECT * FROM Customer
SELECT * FROM Review
SELECT * FROM Cart_Item

DELETE FROM TestRuns
DELETE FROM TestRunTables
DELETE FROM TestRunViews
DBCC CHECKIDENT ('TestRuns', RESEED, 0)
DBCC CHECKIDENT ('TestRunTables', RESEED, 0)
DBCC CHECKIDENT ('TestRunViews', RESEED, 0)