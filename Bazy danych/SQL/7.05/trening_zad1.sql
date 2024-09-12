CREATE OR REPLACE FUNCTION pierwszy_zapis(int,int)
RETURNS wybor.data%TYPE AS $X$
	SELECT min(data)
	FROM wybor
	JOIN grupa USING(kod_grupy)
	JOIN przedmiot_semestr USING(kod_przed_sem)
	WHERE wybor.kod_uz=$1 AND semestr_id=$2;
$X$ LANGUAGE sql;

SELECT DISTINCT u.nazwisko, pierwszy_zapis(u.kod_uz,s.semestr_id)
FROM uzytkownik u
JOIN wybor w USING(kod_uz)
JOIN grupa g USING(kod_grupy)
JOIN przedmiot_semestr ps USING(kod_przed_sem)
JOIN semestr s USING (semestr_id)
WHERE s.nazwa='Semestr zimowy 2016/2017' AND u.nazwisko LIKE 'A%'
ORDER BY 2;
