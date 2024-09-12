CREATE TABLE salary(salary_from decimal NOT NULL,
				   salary_to decimal NOT NULL,
				   offer_id int REFERENCES offer(id) NOT NULL,
				   type text,
				   currency text);