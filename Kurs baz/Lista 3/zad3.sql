DROP TABLE IF EXISTS Products;
DROP TABLE IF EXISTS Rates;
DROP TABLE IF EXISTS Prices;

CREATE TABLE Products (
	ID INT PRIMARY KEY,
	ProductName NVARCHAR(50)
);

CREATE TABLE Rates (
	Currency NVARCHAR(3) PRIMARY KEY,
	PricePLN DECIMAL(18, 2)
);

CREATE TABLE Prices (
	ProductID INT REFERENCES Products(ID),
	Currency NVARCHAR(3), --REFERENCES Rates(Currency),
	Price DECIMAL(18, 2)
);

INSERT INTO Products (ID, ProductName) 
VALUES (1, 'a'), (2, 'b'), (3, 'c');

INSERT INTO Rates (Currency, PricePLN)
VALUES ('PLN', 1), ('USD', 4.02), ('EUR', 4.34),  ('GBP', 5.22);

INSERT INTO Prices (ProductID, Currency, Price)
VALUES (1, 'PLN', 10), (2, 'PLN', 20), (3, 'PLN', 30), (1, 'USD', 2), (2, 'EUR', 5), (3, 'CHF', 7);

DECLARE @ProductID INT, @Currency NVARCHAR(3), @Price DECIMAL(18,2), @PricePLN DECIMAL(18,2);
DECLARE price_cursor CURSOR FOR
	SELECT ProductID, Currency, Price
	FROM Prices
	WHERE Currency <> 'PLN';
	OPEN price_cursor;
	FETCH NEXT FROM price_cursor INTO @ProductID, @Currency, @Price;
	WHILE @@FETCH_STATUS = 0
	BEGIN
		IF NOT EXISTS (SELECT * FROM Rates WHERE Currency = @Currency)
		BEGIN
			DELETE FROM Prices WHERE ProductID = @ProductID AND Currency = @Currency;
		END;
		ELSE
		BEGIN
			SELECT @PricePLN = Price
			FROM Prices
			WHERE ProductID = @ProductID AND Currency = 'PLN';
			UPDATE Prices
			SET Price = @PricePLN * (SELECT PricePLN FROM Rates WHERE Currency = @Currency) 
			WHERE ProductID = @ProductID AND Currency = @Currency;
		END
		FETCH NEXT FROM price_cursor INTO @ProductID, @Currency, @Price;
	END
	CLOSE price_cursor;
DEALLOCATE price_cursor;



