ALTER TABLE offer
ALTER COLUMN salary_from_b2b
SET DATA TYPE decimal
USING salary_from_b2b::decimal;
