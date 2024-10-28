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
INSERT INTO Egzemplarz (Egzemplarz_ID, Sygnatura, Ksiazka_ID) VALUES (42, 'E1', 6), (43, 'E2', 6), (44, 'E3', 6), (45, 'E4', 6);
