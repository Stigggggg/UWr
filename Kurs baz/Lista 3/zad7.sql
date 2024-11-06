CREATE OR ALTER TRIGGER specimens_count 
ON Egzemplarz
AFTER INSERT AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @book_id INT;
	SELECT @book_id = inserted.Ksiazka_ID
	FROM inserted;
	IF (SELECT COUNT(*) FROM Egzemplarz WHERE Ksiazka_ID = @book_id) > 5
	BEGIN
		RAISERROR('Maximum limit of specimens exceeded', 16, 1);
		ROLLBACK TRANSACTION;
	END;
END;

SET IDENTITY_INSERT Egzemplarz ON;
INSERT INTO Egzemplarz (Egzemplarz_ID, Sygnatura, Ksiazka_ID) VALUES (47, 'E7', 6);

DELETE FROM Egzemplarz WHERE Ksiazka_ID = 6;
