INSERT INTO salary
SELECT salary_from_b2b::decimal, salary_to_b2b::decimal, id, 'b2b', salary_currency_b2b
FROM offer
WHERE salary_currency_b2b<>'unknown' AND salary_from_b2b::decimal>0;