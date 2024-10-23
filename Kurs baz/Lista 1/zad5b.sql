SELECT SOD.SalesOrderID, SalesOrderNumber, PurchaseOrderNumber, SUM(LineTotal) AS with_discount, SUM(UnitPrice * OrderQty) as without_discount, SUM(OrderQty) AS total_order
FROM SalesLT.SalesOrderHeader AS SOH
JOIN SalesLT.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
GROUP BY SOD.SalesOrderID, SalesOrderNumber, PurchaseOrderNumber
HAVING SUM(UnitPrice * OrderQty) - SUM(LineTotal) > 1000;