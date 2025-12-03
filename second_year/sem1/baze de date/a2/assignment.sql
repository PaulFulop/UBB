
-- inserts
INSERT INTO Av_Country VALUES ('Hungary')
INSERT INTO Av_Country VALUES ('Spain')
INSERT INTO Customer 
VALUES ('andrei@gmail.com', 'Andrei', 'andr321', 'Romania', 'Bistrita', 21, 'Palm Street 77, 33101')
INSERT INTO Review VALUES ('andrei@gmail.com', 5, 'damn i like this so much')
INSERT INTO Cart VALUES ('andrei@gmail.com')
INSERT INTO [Order] VALUES ('andrei@gmail.com', 3, 'Imparatu Traian 45, 12000', 'completed')
INSERT INTO [Delivery_Service] VALUES ('NoName', NULL)
INSERT INTO [Review] VALUES ('kbkant@gmail.com', 5, 'i love it much')
 
--Violation of PRIMARY KEY constraint 'PK__Order__CB3E4F3111CB5E17'.
--Cannot insert duplicate key in object 'dbo.Order'.
--The duplicate key value is (andrei@gmail.com).
INSERT INTO [Order] VALUES ('andrei@gmail.com', 4, 'Imparatu Traian 45, 12000', 'completed')


-- updates

-- decrement all the review stars from people that have a gmail account
UPDATE Review 
SET Stars = Stars - 1 
WHERE [Uid] LIKE '%_@gmail.__%' 

-- make a 20% sale on all equipment and accessory items 
UPDATE Item 
SET Price = Price - (Price / 5)
WHERE Tid IN (1, 3)

-- increase price by 5% on all clothing items that have a price not between 100 and 200
UPDATE Item 
SET Price = Price + (Price * 0.05)
WHERE Tid = 2 AND Price NOT BETWEEN 100 AND 200;

-- set 'No Website' where no website was provided for the delivery service
UPDATE Delivery_Service
SET Website = 'No Website' WHERE Website IS NULL

-- deletes

-- delete all the users that are not over 18 or over 79 or they live india
DELETE FROM Customer
WHERE Age < 18 OR Age >= 80 OR Country = 'India'
-- DOESNT WORK YET BECAUSE I DON'T DELETE CASCADE so i hav to alter 

-- delete hateful reviews (1 star)
DELETE FROM Review
WHERE Stars <= 2 AND Stars <> 2 -- doesnt make sense but just so that i use every operator  described in the assignment


-- QUERIES

-- a -> see only the equipment and accesorries in the shop
SELECT [Name] FROM Item WHERE Tid = 1
UNION ALL 
SELECT [Name] FROM Item WHERE Tid = 3

SELECT [Name] FROM Item 
WHERE Tid = 1 OR Tid = 3 


-- b -> see all the customers from romania and poland that left a good review on the website
SELECT Email FROM Customer
WHERE Country IN ('Romania', 'Poland')
INTERSECT
SELECT [Uid] FROM Review
WHERE Stars >= 3

-- -> see all the customers from Romania and Russia that have placed an order which was successful
SELECT Email FROM Customer
WHERE Country IN ('Romania', 'Russia')
INTERSECT
SELECT [Oid] FROM [Order]
WHERE [Status] = 'completed'


-- c -> see all customers that have (at least) placed an order and they re from france or poland
SELECT [Oid] FROM [Order]
EXCEPT
SELECT Email FROM Customer
WHERE Country NOT IN ('France', 'Poland')

-- -> see all clothing items id's which no one has placed in their cart by now
SELECT [Iid] FROM Item
WHERE [Tid] NOT IN (1, 3)
EXCEPT
SELECT [Iid] FROM Cart_Item


-- d -> see the name and quantity of each item that is in a cart,
-- and also the email of the person who put it there
SELECT c.[Email], i.[Name] as [item name], ci.[Quantity]
FROM Customer as c
INNER JOIN [Cart_Item] as ci ON ci.[Cid] = c.[Email]
INNER JOIN [Item] as i ON ci.[Iid] = i.[Iid]

-- -> see all customers but also the ones that have placed an order
SELECT c.[Email], o.[Status]
FROM Customer as c
LEFT JOIN [Order] as o ON o.[Oid] = c.[Email]

-- -> see all items but also see the total quantity in all the carts 
SELECT i.[Name], SUM(ci.[Quantity]) as [In Carts]
FROM Cart_Item as ci
RIGHT JOIN Item as i ON i.[Iid] = ci.[Iid]
GROUP BY i.[Name]
ORDER BY i.[Name]

-- -> shows all carts (the cart id is the email of the owner of that cart) with all items
SELECT c.[Cid] as [Owner of Cart], i.[Name] as [Item Name] 
FROM Cart as c
FULL JOIN Cart_Item as ci ON c.[Cid] = ci.[Cid]
FULL JOIN Item as i ON i.[Iid] = ci.[Iid]


-- e -> see all customers that have left at least a review on the website
SELECT [Name] FROM Customer
WHERE [Email] IN (SELECT [Uid] FROM Review)

-- -> the item types that are present in all carts more than x times (based on quantity)
-- ex: all customers might have more than 10 clothing items in their carts in total
SELECT [Name] FROM [Type]
WHERE [Tid] IN (SELECT [Tid] FROM Item
	WHERE [Iid] IN (SELECT [Iid] FROM Cart_Item
		GROUP BY [Iid] HAVING SUM(Quantity) > 2))


--f -> see only the countries that the registered customers live in, not all avaliable countries
SELECT * FROM [Av_Country]
WHERE EXISTS
(SELECT [Country] FROM Customer WHERE Av_Country.Name = Customer.Country)

-- -> see only the countries that are avaliable but none of the customers currently live there
SELECT * FROM [Av_Country]
WHERE NOT EXISTS
(SELECT [Country] FROM Customer WHERE Av_Country.Name = Customer.Country)

-- -> see the password of each customer that left a bad review
SELECT [Password] FROM [Customer]
WHERE EXISTS 
(SELECT [Uid] FROM Review WHERE [Review].[Uid] = [Customer].[Email] AND [Stars] < 3)

-- g -> see the countries that appear more frequently (more than 2 times)
SELECT Countries.Country
FROM (
	SELECT [Country], COUNT([Country]) AS Frequency
	FROM Customer 
	GROUP BY [Country]
) AS Countries
WHERE Countries.Frequency > 2

-- -> name and review count of the customers that have placed at least 2 reviews
SELECT *
FROM (
	SELECT c.[Name], COUNT(r.[Uid]) as [Review Count]
	FROM [Customer] as c
	JOIN [Review] as r ON c.[Email] = r.[Uid]
	GROUP BY c.[Name]
) AS Orders
WHERE Orders.[Review Count] >= 2

-- h -> see the most various type/s of items

SELECT MAX([Count]) AS [Most Various Item] FROM 
(SELECT t.[Name], tc.[Count] FROM
(SELECT [Tid], COUNT([Tid]) AS [Count]
FROM [Item]
GROUP BY [Tid]) AS tc
JOIN [Type] as t ON t.[Tid] = tc.[Tid]) AS [Type Counts]

-- -> see the email of the customers having more than 4 items in their cart in total
SELECT [Cid] FROM [Cart_Item]
GROUP BY [Cid]
HAVING SUM([Quantity]) > 4

-- -> select all item types that have a greater sum of prices than the average of all prices
SELECT [Tid], SUM([Price]) AS [Total price sum of all items of this type] FROM [Item]
GROUP BY [Tid]
HAVING SUM([Price]) > (SELECT AVG(Price) as average FROM [Item])

-- -> see all item types that contain more items than the average value of items
SELECT [Tid], COUNT([Tid]) as Counts FROM [Item]
GROUP BY [Tid]
HAVING COUNT([Tid]) > (SELECT AVG(ic.[Counts]) AS [Avg] FROM
		(SELECT [Tid], COUNT([Tid]) AS [Counts] FROM [Item]
			GROUP BY [Tid]) AS ic)


-- i -> see the first 3 customers in alphabetical order (by name) that left a review with
     -- an even number of stars (can't be 0)
SELECT DISTINCT TOP 3 [Name], [Age] FROM [Customer] WHERE
[Email] = ANY (SELECT [Uid] FROM [Review] WHERE [Stars] % 2 = 0 AND [Stars] > 0)
ORDER BY [Name]

-- equivalent with IN
SELECT DISTINCT TOP 3 [Name], [Age] FROM [Customer] WHERE
[Email] IN (SELECT [Uid] FROM [Review] WHERE [Stars] % 2 = 0 AND [Stars] > 0)
ORDER BY [Name]

-- -> see the first 3 customers in alphabetical order (by name) that left a review with
   -- an odd number of stars 
SELECT DISTINCT TOP 3 [Name], [Age] FROM [Customer] WHERE
[Email] = ANY (SELECT [Uid] FROM [Review] WHERE NOT [Stars] % 2 = 0)
ORDER BY [Name]

-- equivalent with IN
SELECT DISTINCT TOP 3 [Name], [Age] FROM [Customer] WHERE
[Email] IN (SELECT [Uid] FROM [Review] WHERE NOT [Stars] % 2 = 0)
ORDER BY [Name]

-- -> select the item types for which all items of that type are greater than
	-- a certain value (distinct if theres duplicate types even though there might not be)
SELECT DISTINCT [Name] FROM [Type] AS t
WHERE NOT 50 > ANY (SELECT [Price] FROM [Item] AS i
	WHERE t.[Tid] = i.[Tid])

--equivalent with aggregate
SELECT DISTINCT [Name] FROM [Type] AS t
WHERE 50 < (SELECT MIN([Price]) FROM [Item] AS i
	WHERE t.[Tid] = i.[Tid])
-- if the minimum price of an item mathing a certain type is > 50 => all of them are

-- -> select the item types for which the price of all items (that have an even price)
	-- of that type are smaller than
	-- a certain value 
SELECT [Name] FROM [Type] AS t
WHERE 50 > ALL (SELECT [Price] FROM [Item] AS i
	WHERE t.[Tid] = i.[Tid] AND [Price] % 2 = 0)

-- eqivalent with aggregate
SELECT [Name] FROM [Type] AS t
WHERE 50 > (SELECT MAX([Price]) FROM [Item] AS i
	WHERE t.[Tid] = i.[Tid] AND [Price] % 2 = 0)