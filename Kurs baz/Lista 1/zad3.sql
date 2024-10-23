SELECT A.City, COUNT(C.CustomerID) AS clients, COUNT(DISTINCT C.SalesPerson) AS sp
FROM SalesLT.Address AS A
JOIN SalesLT.CustomerAddress AS CA ON A.AddressID = CA.AddressID
LEFT JOIN SalesLT.Customer AS C ON C.CustomerID = CA.CustomerID
GROUP BY A.City