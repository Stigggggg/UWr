DROP TABLE IF EXISTS BankAccount;

CREATE TABLE BankAccount (
	AccountID INT IDENTITY(1, 1),
	Balance INT
);

INSERT INTO BankAccount (Balance) VALUES (1000);

--dirty read - transaction reads data that has been modified by another transaction but has not yet been commited
--transaction A
BEGIN TRANSACTION;
UPDATE BankAccount SET Balance = 500 WHERE AccountID = 1;
--transaction B
SELECT Balance FROM BankAccount WHERE AccountID = 1;
--back to A
ROLLBACK TRANSACTION;
--result after all
SELECT * FROM BankAccount;

--non-repeatable read - transaction reads the same row twice and finds different values because another transaction has modified it between the reads
--transaction A
BEGIN TRANSACTION;
SELECT Balance FROM BankAccount WHERE AccountID = 1;
--transaction B
BEGIN TRANSACTION;
UPDATE BankAccount SET Balance = 1200 WHERE AccountID = 1;
COMMIT TRANSACTION;
--back to A
SELECT Balance FROM BankAccount WHERE AccountID = 1
COMMIT TRANSACTION;
--result after all
SELECT * FROM BankAccount;

--phantom read - transaction reads a set of rows that match a condition, but a second one inserts or deletes rows that cause the first transaction to return different set of rows when executed again
--transaction A
BEGIN TRANSACTION;
SELECT * FROM BankAccount WHERE Balance = 500;
--transaction B
BEGIN TRANSACTION;
INSERT INTO BankAccount (Balance) VALUES (1200);
COMMIT TRANSACTION;
--back to A
SELECT * FROM BankAccount WHERE Balance = 1200;
COMMIT TRANSACTION;
--result after all
SELECT * FROM BankAccount;
