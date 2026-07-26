BEGIN TRANSACTION;
UPDATE Bundle SET Price = Price + 1 WHERE Name = 'Summer Bundle';
-- A now holds a lock on Summer Bundle. Switch to Session B.

UPDATE Bundle SET Price = Price + 1 WHERE Name = 'Beginner Bundle';
-- A WAITS. Beginner Bundle is locked by B. Switch to Session B.
COMMIT

-- Run this to see details
SELECT * FROM Logs; -- nothing logged since the transaction was killed
-- Check deadlock info:
SELECT * FROM sys.dm_exec_requests;