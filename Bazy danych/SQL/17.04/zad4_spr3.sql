SELECT company.name, title, experience_level, salary_from_b2b::decimal, salary_to_b2b::decimal, round(salary_to_b2b::decimal-salary_from_b2b::decimal) AS diff, round(100*(salary_to_b2b::decimal-salary_from_b2b::decimal)/salary_from_b2b::decimal) AS "%" 
FROM offer
JOIN company ON offer.company_id=company.id
WHERE salary_from_b2b::decimal>0 AND salary_currency_b2b='pln' AND published_at::date>='22.04.2023'
ORDER BY 7,1;