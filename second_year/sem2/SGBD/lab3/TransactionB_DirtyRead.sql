SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;
BEGIN TRANSACTION;
SELECT Name, Price FROM Bundle WHERE Name = 'Summer Bundle';
-- You will see 9999 even though A never committed it. That's the dirty read.
WAITFOR DELAY '00:00:10';
SELECT Name, Price FROM Bundle WHERE Name = 'Summer Bundle';
COMMIT;