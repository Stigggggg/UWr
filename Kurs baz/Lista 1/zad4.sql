SELECT PC.Name AS category, P.Name as product
FROM SalesLT.ProductCategory AS PC
JOIN SalesLT.Product AS P ON P.ProductCategoryID = PC.ProductCategoryID
WHERE PC.ParentProductCategoryID IN (
	SELECT ParentProductCategoryID
	FROM SalesLT.ProductCategory
	WHERE ParentProductCategoryID IS NOT NULL
);