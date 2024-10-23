SELECT PM.Name, COUNT(P.ProductID) AS ile 
FROM SalesLT.Product AS P
JOIN SalesLT.ProductModel AS PM ON P.ProductModelID = PM.ProductModelID
GROUP BY PM.Name
HAVING COUNT(P.ProductID) > 1;
