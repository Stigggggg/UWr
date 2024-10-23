DROP FUNCTION IF EXISTS Zad1;

CREATE FUNCTION Zad1 (@days INT)
RETURNS TABLE AS
RETURN
	SELECT PESEL, COUNT(Egzemplarz_ID) as specimens_number
	FROM Czytelnik
	JOIN Wypozyczenie ON Czytelnik.Czytelnik_ID = Wypozyczenie.Czytelnik_ID
	WHERE Liczba_Dni >= @days
	GROUP BY PESEL

SELECT * FROM Zad1(5);

