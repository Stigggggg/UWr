--INSERT INTO lineitem VALUES (500,15519,785,1298,17,24386.67,0.04,0.02,'N','O','1996-03-13','1996-02-12','1996-03-22','DELIVER IN PERSON','TRUCK','egular courts above the');
--SELECT * FROM lineitem WHERE l_orderkey=500;

--ALTER TABLE lineitem
--ADD CONSTRAINT fk_lineitem_orders
--FOREIGN KEY (l_orderkey) REFERENCES orders(o_orderkey)
--ON UPDATE CASCADE

--UPDATE lineitem
--SET l_orderkey=1 WHERE l_orderkey=500;
--SELECT * FROM lineitem WHERE l_orderkey=1;

--ALTER TABLE lineitem
--ADD CONSTRAINT fk_lineitem_orders
--FOREIGN KEY (l_orderkey) REFERENCES orders(o_orderkey)
--ON UPDATE CASCADE;

--UPDATE orders
--SET o_orderkey=500 WHERE o_orderkey=1;
--SELECT * FROM lineitem WHERE l_orderkey=500;
