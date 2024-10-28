DROP PROCEDURE IF EXISTS Zad3;

CREATE PROCEDURE Zad3 @pesel CHAR(11), @miasto VARCHAR(30), @nazwisko VARCHAR(30), @data_ur VARCHAR(30) AS
BEGIN
	IF (@pesel NOT LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')
	BEGIN
		THROW 50000, 'PESEL validation failed', 1
	END
	IF (@nazwisko COLLATE Latin1_General_BIN NOT LIKE '[A-Z]%' OR LEN(@nazwisko) < 2)
	BEGIN
		THROW 50001, 'Lastname validation failed', 1
	END
	IF (TRY_CAST(@data_ur AS DATE) IS NULL)
	BEGIN
		THROW 50002, 'Birth date validation failed', 1
	END
	INSERT INTO Czytelnik (PESEL, Miasto, Nazwisko, Data_Urodzenia) VALUES (@pesel, @miasto, @nazwisko, @data_ur)
END

EXEC Zad3 @pesel = '00040012351', @miasto = 'Bygdoszcz', @nazwisko = 'B', @data_ur = '2024-10-23';