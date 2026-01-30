-- LAB 5 INDEXES

-- TABLES TO WORK ON

-- TA
CREATE TABLE [Bundle](
[Bid] int IDENTITY(1,1) PRIMARY KEY, -- clustered index
[Name] nvarchar(50) UNIQUE NOT NULL, -- unique non-clustered
[Price] int NOT NULL
)

INSERT INTO [Bundle] VALUES
('Intermediate Calisthenics Bundle', 400),
('Christmas Bundle',200),
('Easter Bundle', 200),
('Beginner Bundle', 150), 
('Gymnastics Bundle', 300),
('Full Cali Bundle', 250)

-- TC
CREATE TABLE [Item_Bundle](
[ItemBundleID] int IDENTITY(1,1) PRIMARY KEY, 
[Iid] int NOT NULL,
[Bid] int NOT NULL,
CONSTRAINT FK_Item_ItemBundle FOREIGN KEY ([Iid]) REFERENCES Item(Iid),
CONSTRAINT FK_Bundle_ItemBundle FOREIGN KEY ([Bid]) REFERENCES Bundle(Bid)
)

INSERT INTO [Item_Bundle] VALUES
(1,1),
(2,1),
(3,1),
(6,1),
(2,2),
(1,2),
(4,2),
(5,2),
(1,4),
(2,4),
(3,4)

-- TB -> Item table

SELECT * FROM [Item]
SELECT * FROM [Bundle]
SELECT * FROM [Item_Bundle]

-- a

-- clustered index scan
SELECT * FROM Bundle WHERE Bid % 2 = 0 -- cannot use the index efficiently

-- clustered index seek
SELECT * FROM Bundle WHERE Bid = 2 -- specific value => fast search
SELECT * FROM Bundle with(index (PK__Bundle__C6D111C921BA65D0)) WHERE Bid = 2 -- to force the index, not mandatory

-- non-clustered index scan
SELECT [Name] FROM Bundle WHERE [Name] LIKE '%Cali%' -- cannot use the index efficiently

-- non-clustered index seek
SELECT [Name] FROM Bundle WHERE [Name] = 'Christmas Bundle'

-- key lookup
SELECT * FROM Bundle WHERE [Name] = 'Easter Bundle'
-- selecting columns that are not included in the same index => it needs to find the record in the real table
-- gets Bid = 3 -> jumps to row with Bid = 3 -> retrieves Price, Bid etc.


-- b

SELECT [Name] FROM Item WHERE [Name] = 'high bars'

-- for testing performance
IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='N_Index_Item_Name')
DROP INDEX N_Index_Item_Name ON Item
CREATE NONCLUSTERED INDEX N_Index_Item_Name ON Item([Name])


-- c

-- join on Ta and Tc (Bundle and Item_Bundle)
-- see all items and in which bundle they are included (not all of them are included in a bundle)

-- create index for the fk in Item_Bundle
IF EXISTS (SELECT NAME FROM sys.indexes WHERE name='IX_ItemBundle_ItemID')
DROP INDEX IX_ItemBundle_ItemID ON Item_Bundle
CREATE NONCLUSTERED INDEX IX_ItemBundle_ItemID ON Item_Bundle([Iid])

EXEC sp_helpindex 'Item_Bundle';
SELECT * FROM Item_Bundle
SELECT * FROM Item

-- non clustered index scan if the columns included in the select are present. otherwise, it is not necessary
GO
ALTER VIEW Items_Bundles_View
AS
SELECT i.[Name] [Item Name], ib.[Iid] [Item Id]
FROM [Item] AS i
INNER JOIN [Item_Bundle] as ib ON i.[Iid] = ib.[Iid] -- seek on Item, scan on Item_Table
--														(needs to look at all fk that match the pk in Item)
GO
DROP VIEW Items_Bundles_View
SELECT * FROM Items_Bundles_View