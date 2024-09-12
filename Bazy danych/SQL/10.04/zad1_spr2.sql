SELECT c_custkey, c_name, SUM(o_totalprice) 
    FROM customer
    JOIN orders ON o_custkey = c_custkey
    JOIN nation ON c_nationkey = n_nationkey
    JOIN region ON r_regionkey = n_regionkey
    WHERE EXTRACT(year FROM o_orderdate) = 1997
        AND r_name = 'EUROPE'
    GROUP BY c_custkey
    HAVING SUM(o_totalprice) > 500000
    ORDER BY 1 DESC;