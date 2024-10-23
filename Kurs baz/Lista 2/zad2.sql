DROP TABLE IF EXISTS firstnames;
DROP TABLE IF EXISTS lastnames;
DROP TABLE IF EXISTS fldata;

CREATE TABLE firstnames (
	id INT PRIMARY KEY IDENTITY(1,1),
	firstname NVARCHAR(100)
);

CREATE TABLE lastnames (
	id INT PRIMARY KEY IDENTITY(1,1),
	lastname NVARCHAR(100)
);

CREATE TABLE fldata (
	firstname NVARCHAR(100),
	lastname NVARCHAR(100)
	PRIMARY KEY (firstname, lastname)
);

INSERT INTO firstnames VALUES ('Frodo'), ('Sam'), ('Merry'), ('Pippin'), ('Gandalf');
INSERT INTO lastnames VALUES ('Baggins'), ('Gamgee'), ('Brandybuck'), ('Tuk'), ('Grey');

DROP PROCEDURE IF EXISTS Zad2;

CREATE PROCEDURE Zad2 @n INT AS
BEGIN
	DECLARE @number_of_firstnames INT
	SET @number_of_firstnames = (SELECT COUNT(id) FROM firstnames) 
	DECLARE @number_of_lastnames INT
	SET @number_of_lastnames = (SELECT COUNT(id) FROM lastnames) 
	DECLARE @number_of_possible_pairs INT
	SET @number_of_possible_pairs = @number_of_firstnames * @number_of_lastnames
	IF (@n > @number_of_possible_pairs)
	BEGIN
		THROW 50000, 'Number of possible pairs exceeded', 1
	END
	TRUNCATE TABLE fldata
	DECLARE @i INT
	DECLARE @firstname NVARCHAR(100)
	DECLARE @lastname NVARCHAR(100)
	SET @i = 1
	WHILE (@i <= @n)
	BEGIN
		SET @firstname = (SELECT TOP 1 firstname FROM firstnames ORDER BY NEWID())
		SET @lastname = (SELECT TOP 1 lastname FROM lastnames ORDER BY NEWID())
		IF NOT EXISTS (SELECT firstname, lastname FROM fldata WHERE firstname = @firstname AND lastname = @lastname)
		BEGIN 
			INSERT INTO fldata VALUES (@firstname, @lastname)
			SET @i = @i + 1
		END
	END
END

EXEC Zad2 @n = 25;
