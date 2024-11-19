CREATE OR ALTER PROCEDURE zad2
AS
BEGIN
    BEGIN TRANSACTION;
    SAVE TRANSACTION StartPoint;
    BEGIN TRY
        UPDATE SalesLT.CustomerAddress SET AddressType = 'Shipping' WHERE CustomerID = 29485;
		SAVE TRANSACTION MidPoint;
		UPDATE SalesLT.Product SET Size = 1234567 WHERE ProductID = 680;
	END TRY
    BEGIN CATCH
		PRINT 'B³¹d wykryty, cofniêcie do StartPoint';
        ROLLBACK TRANSACTION StartPoint;
    END CATCH
	COMMIT TRANSACTION;
END;

EXEC zad2;