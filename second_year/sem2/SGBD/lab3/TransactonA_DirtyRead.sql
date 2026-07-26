BEGIN TRANSACTION;
UPDATE Bundle SET Price = 9999 WHERE Name = 'Summer Bundle';
WAITFOR DELAY '00:00:08';
ROLLBACK;-- transaction A changed its mind. 9999.99 never existed. But B already read it.
COMMIT;