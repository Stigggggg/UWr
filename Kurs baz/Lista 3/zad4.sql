CREATE OR ALTER TRIGGER update_date
ON SalesLT.Customer
AFTER UPDATE AS
BEGIN
	SET NOCOUNT ON; --doesn't say how many rows were affected
	DECLARE @CustomerID INT;
	SELECT @CustomerID = inserted.CustomerID
	FROM inserted;
	UPDATE SalesLT.Customer
	SET ModifiedDate = GETDATE()
	WHERE SalesLT.Customer.CustomerID = @CustomerID
END;

UPDATE SalesLT.Customer
SET FirstName = 'Robert', LastName = 'Kubica'
WHERE CustomerID = 1;