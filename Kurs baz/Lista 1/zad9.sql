ALTER TABLE SalesLT.Customer ADD CreditCardNumber NVARCHAR(50);

UPDATE SalesLT.SalesOrderHeader
SET CreditCardApprovalCode = 'YES'
WHERE SalesOrderID IN (SELECT TOP 3 SalesOrderID FROM SalesLT.SalesOrderHeader);

UPDATE SalesLT.Customer
SET CreditCardNumber = 'X'
WHERE CustomerID IN (SELECT CustomerID FROM SalesLT.SalesOrderHeader WHERE CreditCardApprovalCode = 'YES');