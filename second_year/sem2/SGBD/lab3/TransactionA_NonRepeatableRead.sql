BEGIN TRANSACTION;
UPDATE Bundle SET Price = 100 WHERE Name = 'Summer Bundle';
COMMIT;
-- Committed immediately. Switch back to Session B.