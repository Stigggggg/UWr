SET STATISTICS TIME ON;
SET SHOWPLAN_ALL ON;

--there is a clustered index - its primary key, so it doesn't work
DROP INDEX IDX_clustered ON Ksiazka;
CREATE CLUSTERED INDEX IDX_clustered ON Ksiazka (Ksiazka_ID, Rok_Wydania DESC, Tytul ASC);

DROP INDEX IDX_nonclustered ON Egzemplarz;
CREATE NONCLUSTERED INDEX IDX_nonclustered ON Egzemplarz (Ksiazka_ID);

DROP INDEX IDX_covering ON Ksiazka;
CREATE NONCLUSTERED INDEX IDX_covering ON Ksiazka (Autor) INCLUDE (Tytul);

SELECT k.Tytul, e.Egzemplarz_ID, e.Sygnatura
FROM Ksiazka k
JOIN Egzemplarz e ON k.Ksiazka_ID = e.Ksiazka_ID
WHERE k.Autor = 'Helen Feddema'

SET STATISTICS TIME OFF;
SET SHOWPLAN_ALL OFF;