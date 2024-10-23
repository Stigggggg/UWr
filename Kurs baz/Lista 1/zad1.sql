SELECT DISTINCT City FROM SalesLT.SalesOrderHeader AS SOH
JOIN SalesLT.Address AS A ON SOH.ShipToAddressID = A.AddressID
WHERE ShipDate <= '2024-10-12'
ORDER BY City;