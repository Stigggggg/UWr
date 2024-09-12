SELECT name, COUNT(DISTINCT offer.title) AS stanowiska, COUNT(offer.id) AS oferty, MIN(skill.value), MAX(skill.value), ROUND(AVG(skill.value)) as avg
FROM skill
JOIN offer ON skill.offer_id=offer.id
GROUP BY name
ORDER BY 2 DESC, 3 DESC;