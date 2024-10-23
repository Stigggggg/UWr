/*UPDATE SalesLT.SalesOrderHeader
SET ShipDate = OrderDate - 1;*/

/*ALTER TABLE SalesLT.SalesOrderHeader NOCHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;*/

ALTER TABLE SalesLT.SalesOrderHeader CHECK CONSTRAINT CK_SalesOrderHeader_ShipDate;