--clustered index - determines the physical order of rows in a table
--a table can have only one clustered index, usually it is a primary key

--nonclustered index - doesnt change the table's physical order but maintains
--a separate structure pointing to the data

--covering index - can satisfy all requested columns in a query
--without performing a further lookup into the clustered index

DROP INDEX IDX_nonclustered ON Ksiazka;
DROP INDEX IDX_nonclustered2 ON Egzemplarz;
DROP INDEX IDX_covering ON Egzemplarz;

SELECT Autor
FROM Ksiazka
JOIN Egzemplarz ON Egzemplarz.Ksiazka_ID = Ksiazka.Ksiazka_ID
WHERE Autor = 'Helen Feddema'

CREATE NONCLUSTERED INDEX IDX_nonclustered ON Ksiazka(Autor);

SELECT Autor
FROM Ksiazka
JOIN Egzemplarz ON Egzemplarz.Ksiazka_ID = Ksiazka.Ksiazka_ID
WHERE Autor = 'Helen Feddema'

CREATE NONCLUSTERED INDEX IDX_nonclustered2 ON Egzemplarz(Ksiazka_ID);

SELECT Autor
FROM Ksiazka
JOIN Egzemplarz ON Egzemplarz.Ksiazka_ID = Ksiazka.Ksiazka_ID
WHERE Autor = 'Helen Feddema'

CREATE NONCLUSTERED INDEX IDX_covering ON Egzemplarz(Ksiazka_ID, Sygnatura)
INCLUDE (Egzemplarz_ID);

SELECT Autor, Sygnatura
FROM Ksiazka
JOIN Egzemplarz ON Egzemplarz.Ksiazka_ID = Ksiazka.Ksiazka_ID
WHERE Autor = 'Helen Feddema'


