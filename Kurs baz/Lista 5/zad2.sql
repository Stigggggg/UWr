--first query
SET STATISTICS TIME ON;
--SET SHOWPLAN_ALL ON;

DECLARE @t1 DATETIME = GETDATE();
SELECT DISTINCT c.PESEL, c.Nazwisko
FROM Egzemplarz e
JOIN Ksiazka k ON e.Ksiazka_ID=k.Ksiazka_ID
JOIN Wypozyczenie w ON e.Egzemplarz_ID=w.Egzemplarz_ID
JOIN Czytelnik c ON c.Czytelnik_ID = w.Czytelnik_ID;
DECLARE @t2 DATETIME = GETDATE();
SELECT DATEDIFF(MILLISECOND, @t1, @t2);

--second query
DECLARE @t3 DATETIME = GETDATE();
SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c WHERE c.Czytelnik_ID IN
(SELECT w.Czytelnik_ID FROM Wypozyczenie w
JOIN Egzemplarz e ON e.Egzemplarz_ID=w.Egzemplarz_ID
JOIN Ksiazka k ON e.Ksiazka_ID=k.Ksiazka_ID)
DECLARE @t4 DATETIME = GETDATE();
SELECT DATEDIFF(MILLISECOND, @t3, @t4);

--my query
DECLARE @t5 DATETIME = GETDATE();
SELECT DISTINCT PESEL, Nazwisko
FROM Czytelnik
WHERE Czytelnik_ID IN (
	SELECT DISTINCT Czytelnik_ID
    FROM Wypozyczenie
    WHERE Egzemplarz_ID IN (
		SELECT Egzemplarz_ID
        FROM Egzemplarz 
        JOIN Ksiazka ON Egzemplarz.Ksiazka_ID = Ksiazka.Ksiazka_ID
        )
    );
DECLARE @t6 DATETIME = GETDATE();
SELECT DATEDIFF(MILLISECOND, @t5, @t6);

--SET SHOWPLAN_ALL OFF;
SET STATISTICS TIME OFF;

