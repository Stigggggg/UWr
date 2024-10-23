SELECT C.LastName, C.FirstName, SUM(UnitPrice * OrderQty - LineTotal) AS savings
FROM SalesLT.Customer AS C
JOIN SalesLT.SalesOrderHeader AS SOH ON SOH.CustomerID = C.CustomerID
JOIN SalesLT.SalesOrderDetail AS SOD ON SOH.SalesOrderID = SOD.SalesOrderID
GROUP BY C.LastName, C.FirstName;