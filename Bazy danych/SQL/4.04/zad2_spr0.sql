SELECT * 
FROM customer
JOIN nation ON c_nationkey=n_nationkey
WHERE n_name='UNITED STATES' AND c_mktsegment='BUILDING' AND c_acctbal>9000
ORDER BY c_name;