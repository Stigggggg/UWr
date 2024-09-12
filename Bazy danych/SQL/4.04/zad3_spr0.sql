SELECT DISTINCT s_name,r_name,p_type,p_size
FROM supplier
JOIN nation ON s_nationkey=n_nationkey
JOIN region ON n_regionkey=r_regionkey
JOIN partsupp ON s_suppkey=ps_suppkey
JOIN part ON ps_partkey=p_partkey
WHERE r_name='ASIA' AND p_type LIKE '%BRUSHED BRASS' AND p_size=50;
