SELECT DISTINCT company.name
FROM company
JOIN offer ON company.id=offer.company_id
JOIN skill ON offer.id=skill.offer_id
WHERE skill.name LIKE '%PostgreSQL%'
