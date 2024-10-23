DROP TYPE IF EXISTS Readers;

CREATE TYPE Readers AS TABLE (czytelnik_id INT);

DROP PROCEDURE IF EXISTS Zad4;

CREATE PROCEDURE Zad4 @r Readers READONLY AS
BEGIN
	SELECT czyt.czytelnik_id AS reader_id, SUM(Liczba_Dni) AS sum_days
	FROM @r AS czyt
	JOIN Wypozyczenie ON czyt.Czytelnik_ID = Wypozyczenie.Czytelnik_ID
	GROUP BY czyt.czytelnik_id 
END

DECLARE @id_czyt Readers
INSERT INTO @id_czyt VALUES (1),(2),(3)

EXEC Zad4 @id_czyt