(
SELECT DISTINCT company.name
FROM company
JOIN offer ON company.id=offer.company_id
JOIN skill ON skill.offer_id=offer.id
)
EXCEPT
(
SELECT DISTINCT company.name
FROM company
JOIN offer ON company.id=offer.company_id
JOIN skill ON skill.offer_id=offer.id
WHERE skill.name ILIKE '%SQL%' OR skill.name ILIKE '%database%'
)
ORDER BY 1;