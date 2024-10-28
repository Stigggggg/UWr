CREATE TABLE production.brand_approvals(
    brand_id INT IDENTITY PRIMARY KEY,
    brand_name VARCHAR(255) NOT NULL
);

CREATE VIEW production.vw_brands 
AS
SELECT
    brand_name,
    'Approved' approval_status
FROM
    production.brands
UNION
SELECT
    brand_name,
    'Pending Approval' approval_status
FROM
    production.brand_approvals;

CREATE TRIGGER production.trg_vw_brands 
ON production.vw_brands
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;
    INSERT INTO production.brand_approvals ( 
        brand_name
    )
    SELECT
        i.brand_name
    FROM
        inserted i
    WHERE
        i.brand_name NOT IN (
            SELECT 
                brand_name
            FROM
                production.brands
        );
END

INSERT INTO production.vw_brands(brand_name)
VALUES('Eddy Merckx');

SELECT
	brand_name,
	approval_status
FROM
	production.vw_brands;