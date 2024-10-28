DROP TYPE IF EXISTS Products;

CREATE TYPE Products AS TABLE (product_id INT);

DROP PROCEDURE IF EXISTS Zad5;

CREATE PROCEDURE Zad5 @p Products READONLY, @discontinued_date DATE AS
BEGIN
	IF EXISTS (SELECT ProductID, Name, DiscontinuedDate
	FROM SalesLT.Product
	JOIN @p AS PID ON Product.ProductID = PID.product_id
	WHERE DiscontinuedDate IS NOT NULL)
	BEGIN
		THROW 50001, 'Already exists', 1;
	END
	UPDATE SalesLT.Product SET DiscontinuedDate = @discontinued_date
	FROM SalesLT.Product
	JOIN @p AS PID ON Product.ProductId = PID.product_id
	WHERE SalesLT.Product.DiscontinuedDate IS NULL;
END

DECLARE @p Products;
INSERT INTO @p VALUES (710)

EXEC Zad5 @p, '2024-10-23'