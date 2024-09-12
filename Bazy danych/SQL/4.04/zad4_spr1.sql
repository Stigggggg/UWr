SELECT c_custkey
FROM customer
LEFT JOIN orders ON o_custkey=c_custkey
WHERE o_orderkey IS NULL
ORDER BY 1;