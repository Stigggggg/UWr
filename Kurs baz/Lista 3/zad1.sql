SELECT * INTO SalesLT.Product_Backup
FROM SalesLT.Product;

SET IDENTITY_INSERT SalesLT.Product_Backup ON;

--standard SQL query
TRUNCATE TABLE SalesLT.Product_Backup;
DECLARE @t1 DATETIME;
DECLARE @t2 DATETIME;
SET @t1 = GETDATE();
INSERT INTO SalesLT.Product_Backup (ProductID, Name, ProductNumber, Color, StandardCost, ListPrice, Size, Weight, ProductCategoryID, ProductModelID, SellStartDate, SellEndDate, DiscontinuedDate, ThumbNailPhoto, ThumbnailPhotoFileName, rowguid, ModifiedDate)
SELECT ProductID, Name, ProductNumber, Color, StandardCost, ListPrice, Size, Weight, ProductCategoryID, ProductModelID, SellStartDate, SellEndDate, DiscontinuedDate, ThumbNailPhoto, ThumbnailPhotoFileName, rowguid, ModifiedDate 
FROM SalesLT.Product;
SET @t2 = GETDATE();
SELECT DATEDIFF(MILLISECOND, @t1, @t2) AS time_1;

--using cursors
TRUNCATE TABLE SalesLT.Product_Backup;
SET IDENTITY_INSERT SalesLT.Product_Backup ON;
DECLARE @t3 DATETIME;
DECLARE @t4 DATETIME;
DECLARE @ProductID INT, @Name NVARCHAR(50), @ProductNumber NVARCHAR(25), @Color NVARCHAR(15), @StandardCost DECIMAL(19, 4), @ListPrice DECIMAL(19, 4), @Size NVARCHAR(5), @Weight DECIMAL(8, 2), @ProductCategoryID INT, @ProductModelID INT, @SellStartDate DATETIME, @SellEndDate DATETIME, @DiscontinuedDate DATETIME, @ThumbNailPhoto VARBINARY(max), @ThumbnailPhotoFileName NVARCHAR(50), @rowguid UNIQUEIDENTIFIER, @ModifiedDate DATETIME;
SET @t3 = GETDATE();
DECLARE c CURSOR FOR
	SELECT ProductID, Name, ProductNumber, Color, StandardCost, ListPrice, Size, Weight, ProductCategoryID, ProductModelID, SellStartDate, SellEndDate, DiscontinuedDate, ThumbNailPhoto, ThumbnailPhotoFileName, rowguid, ModifiedDate 
	FROM SalesLT.Product;
	OPEN c;
	FETCH NEXT FROM c into @ProductID, @Name, @ProductNumber, @Color, @StandardCost, @ListPrice, @Size, @Weight, @ProductCategoryID, @ProductModelID, @SellStartDate, @SellEndDate, @DiscontinuedDate, @ThumbNailPhoto, @ThumbnailPhotoFileName, @rowguid, @ModifiedDate;
	WHILE @@FETCH_STATUS = 0
	BEGIN
		INSERT INTO SalesLT.Product_Backup(ProductID, Name, ProductNumber, Color, StandardCost, ListPrice, Size, Weight, ProductCategoryID, ProductModelID, SellStartDate, SellEndDate, DiscontinuedDate, ThumbNailPhoto, ThumbnailPhotoFileName, rowguid, ModifiedDate)
		VALUES (@ProductCategoryID, @Name, @ProductNumber, @Color, @StandardCost, @ListPrice, @Size, @Weight, @ProductCategoryID, @ProductModelID, @SellStartDate, @SellEndDate, @DiscontinuedDate, @ThumbNailPhoto, @ThumbnailPhotoFileName, @rowguid, @ModifiedDate);
		FETCH NEXT FROM c into @ProductID, @Name, @ProductNumber, @Color, @StandardCost, @ListPrice, @Size, @Weight, @ProductCategoryID, @ProductModelID, @SellStartDate, @SellEndDate, @DiscontinuedDate, @ThumbNailPhoto, @ThumbnailPhotoFileName, @rowguid, @ModifiedDate;
	END;
	CLOSE c;
DEALLOCATE c;
SET @t4 = GETDATE();
SELECT DATEDIFF(MILLISECOND, @t3, @t4) AS time_2;

--time_1 = 3
--time_2 = 40
