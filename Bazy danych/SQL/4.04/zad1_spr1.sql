SELECT DISTINCT o_orderkey, o_orderdate, o_orderpriority
FROM orders
JOIN lineitem ON o_orderkey=l_orderkey
WHERE l_shipdate>o_orderdate+120
AND EXTRACT(month FROM o_orderdate)=8
AND (o_orderpriority='2-HIGH' OR o_orderpriority='1-URGENT')
ORDER BY o_orderpriority ASC, o_orderdate DESC, o_orderkey ASC
