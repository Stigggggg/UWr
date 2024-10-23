DROP PROCEDURE IF EXISTS Zad3;

CREATE PROCEDURE Zad3 @pesel CHAR(11), @miasto VARCHAR(30), @nazwisko VARCHAR(30), @data_ur DATE AS
BEGIN
	IF (@pesel NOT LIKE '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]')
	BEGIN
		THROW 50000, 'PESEL validation failed', 1
	END
	IF (@nazwisko COLLATE Polish_CI_AS NOT LIKE '[A-Z]%' OR LEN(@nazwisko) < 2)
	BEGIN
		THROW 50001, 'Lastname validation failed', 1
	END
	IF (TRY_CAST(@data_ur AS DATE) IS NULL)
	BEGIN
		THROW 50002, 'Birth date validation failed', 1
	END
	INSERT INTO Czytelnik (PESEL, Nazwisko, Miasto, Data_Urodzenia) VALUES (@pesel, @miasto, @nazwisko, @data_ur)
END
