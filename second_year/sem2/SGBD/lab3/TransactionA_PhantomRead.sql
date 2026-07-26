BEGIN TRANSACTION;
INSERT INTO Bundle(Name, Price) VALUES ('Phantom Bundle', 9);
COMMIT;

DELETE FROM Bundle WHERE [Name] = 'Phantom Bundle' -- cleanup
SELECT * FROM Bundle