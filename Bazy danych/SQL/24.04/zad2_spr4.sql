SELECT offer.title, COUNT(DISTINCT skill.name) AS count, (array_agg(DISTINCT skill.name))[1:4] AS example_skill
FROM offer
JOIN skill ON skill.offer_id=offer.id
GROUP BY offer.title
HAVING COUNT(DISTINCT skill.name)>20
ORDER BY 2 DESC, 1 ASC