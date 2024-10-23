DROP TYPE IF EXISTS Products;

CREATE TYPE Products AS TABLE (product_id INT);

CREATE PROCEDURE Zad5 @p Products READONLY, @discontinued_date DATE AS
BEGIN
	UPDATE SalesLT.Product SET DiscontinuedDate = @discontinued_date
	FROM SalesLT.Product
	JOIN @p AS PID ON Product.ProductId = PID.product_id
	WHERE SalesLT.Product.DiscontinuedDate IS NULL;
	SELECT ProductID, Name, DiscontinuedDate
	FROM SalesLT.Product
	JOIN @p AS PID ON Product.ProductID = PID.product_id
	WHERE DiscontinuedDate IS NOT NULL;
END

DECLARE @p Products;
INSERT INTO @p VALUES (680), (706), (707)

EXEC Zad5 @p, '2024-10-19'