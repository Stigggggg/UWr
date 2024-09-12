--1 kropka
ALTER TABLE nation 
ADD CONSTRAINT fk_nation_region
FOREIGN KEY (n_regionkey) REFERENCES region(r_regionkey)
ON DELETE CASCADE

--2 kropka
INSERT INTO region VALUES (6996,'Australia','xdddddddd')
INSERT INTO nation VALUES (2137,'Australia',6996,'bing chilling')

--3 kropka
DELETE FROM region WHERE r_name='Australia'
SELECT DISTINCT n_regionkey FROM nation

