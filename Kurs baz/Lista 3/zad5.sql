--PRZEROBIC

CREATE TABLE SalesLT.Cost_Price (
	ProductID INT,
	StandardCost DECIMAL(18,4),
	ListPrice DECIMAL(18,4),
	ChangeDate DATETIME,
	PRIMARY KEY (ProductID, ChangeDate),
	FOREIGN KEY (ProductID) REFERENCES SalesLT.Product(ProductID)
);

CREATE TRIGGER change
ON SalesLT.Product
AFTER UPDATE AS
BEGIN
	INSERT INTO SalesLT.Cost_Price (ProductID, StandardCost, ListPrice, ChangeDate)
	SELECT i.ProductID, i.StandardCost, i.ListPrice, GETDATE()
	FROM inserted i
	JOIN deleted d ON i.ProductID = d.ProductID
	WHERE i.StandardCost <> d.StandardCost OR i.ListPrice <> d.ListPrice
END;

WITH PriceHistory AS (
    SELECT ProductID, StandardCost, ListPrice, ChangeDate, LEAD(ChangeDate) OVER (PARTITION BY ProductID ORDER BY ChangeDate) AS NextChangeDate
	FROM SalesLT.Cost_Price
)
SELECT ProductID, StandardCost, ListPrice, ChangeDate AS EffectiveFrom, ISNULL(NextChangeDate, GETDATE()) AS EffectiveTo
FROM PriceHistory
ORDER BY ProductID, EffectiveFrom;

UPDATE SalesLT.Product
SET StandardCost = 12.00
WHERE ProductID = 680;

SELECT * FROM SalesLT.Cost_Price

UPDATE SalesLT.Product
SET StandardCost = 14.00
WHERE ProductID = 680;

SELECT * FROM SalesLT.Cost_Price