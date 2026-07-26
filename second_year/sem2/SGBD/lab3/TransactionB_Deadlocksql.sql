BEGIN TRANSACTION;
UPDATE Bundle SET Price = Price + 1 WHERE Name = 'Beginner Bundle';
-- B now holds a lock on Beginner Bundle. Switch to Session A.

UPDATE Bundle SET Price = Price + 1 WHERE Name = 'Summer Bundle';
COMMIT
-- B WAITS. Summer Bundle is locked by A.
-- DEADLOCK. SQL Server will kill one session within ~5 seconds.
-- The killed session gets error 1205.

-- FIX -> same order

SELECT * FROM Bundle