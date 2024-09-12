SELECT DISTINCT company.name
FROM company
JOIN offer ON offer.company_id=company.id
WHERE offer.id NOT IN(
	SELECT offer_id
	FROM skill
	WHERE name ILIKE '%SQL%' OR name ILIKE'%database%')
ORDER BY 1;

