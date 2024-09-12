UPDATE customer
SET c_acctbal=1.1*c_acctbal
FROM nation
JOIN region ON n_regionkey=r_regionkey
WHERE c_nationkey=n_nationkey AND r_name='EUROPE';
