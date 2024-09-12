--CREATE TYPE plan_zajec_typ AS (nazwa text,
--							  rodzaj_zajec char,
--							  termin text,
--							  sala text,
--							  liczba_osob int);
							  
CREATE OR REPLACE FUNCTION plan_zajec(int,int)
RETURNS SETOF plan_zajec_typ AS $X$
	SELECT p.nazwa::text, g.rodzaj_zajec::char, g.termin::text, g.sala::text, COUNT(*)::int
	FROM przedmiot p 
	JOIN przedmiot_semestr ps USING(kod_przed)
	JOIN grupa g USING(kod_przed_sem)
	JOIN wybor w USING(kod_grupy)
	WHERE g.kod_uz=$1 AND ps.semestr_id=$2
	GROUP BY p.nazwa, g.rodzaj_zajec, g.termin, g.sala;
$X$ LANGUAGE sql;

SELECT plan_zajec(187,39);