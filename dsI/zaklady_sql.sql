--1
SELECT email
FROM customer
WHERE active = 0;

--2
SELECT title, description
FROM film
WHERE rating = 'G'
ORDER BY title DESC;

--3
SELECT *
FROM payment
WHERE payment_date >= '2006-01-01'
  AND amount < 2;

--4
SELECT description
FROM film
WHERE rating = 'G'
   OR rating = 'PG';

--5
SELECT description
FROM film
WHERE rating IN ('G', 'PG', 'PG-13');

--6
SELECT description
FROM film
WHERE rating NOT IN ('G', 'PG', 'PG-13');

--7
SELECT *
FROM film
WHERE length > 50
  AND rental_duration IN (3, 5);

--8
SELECT title
FROM film
WHERE (title LIKE '%RAINBOW%' OR title LIKE 'TEXAS%')
  AND length > 70;

--9
SELECT title
FROM film
WHERE description LIKE '%AND%'
  AND length BETWEEN 80 AND 90
  AND rental_duration % 2 = 1;

--10
SELECT DISTINCT special_features
FROM film
WHERE replacement_cost BETWEEN 14 AND 16
ORDER BY special_features;

--11
SELECT *
FROM film
WHERE rental_duration < 4 AND rating != 'PG'
   OR rental_duration >= 4 AND rating = 'PG';

--12
SELECT *
FROM address
WHERE postal_code IS NOT NULL;

--13
SELECT DISTINCT customer_id
FROM rental
WHERE return_date IS NULL;

--14
SELECT payment_id
     , YEAR(payment_date)  AS year
     , MONTH(payment_date) AS month
     , DAY(payment_date)   AS day
FROM payment

--15
SELECT title
FROM film
WHERE LEN(title) != 20;

--16
SELECT rental_id, DATEDIFF(MINUTE, rental_date, return_date) AS minutes
FROM rental
WHERE return_date IS NOT NULL

--17
SELECT customer_id
     , first_name + ' ' + last_name AS full_name
FROM customer
WHERE active = 1;

--18
SELECT address, COALESCE(postal_code, '(empty)') AS psc
FROM address

--19
SELECT rental_id,
       CAST(rental_date AS VARCHAR) + ' - ' + CAST(return_date
           AS VARCHAR) AS interval
FROM rental
WHERE return_date IS NOT NULL

--20
SELECT rental_id,
       CAST(rental_date AS VARCHAR) + COALESCE(' - ' + CAST(
               return_date AS VARCHAR), ' ') AS interval
FROM rental

--21
SELECT COUNT(*) AS pocet
FROM film;

--22
SELECT COUNT(DISTINCT rating) AS pocet_klas
FROM film;

--23
SELECT COUNT(*) AS pocet_vsech, COUNT(DISTINCT postal_code) AS ruzna_psc, COUNT(postal_code) AS pocet_s_psc
FROM address;

--24
SELECT MIN(length)    AS nejmensi,
       MAX(length)    AS nejvetsi,
       AVG(CAST(length
           AS FLOAT)) AS prumerna
FROM film

--25
SELECT COUNT(*) AS pocet, SUM(amount) AS soucet
FROM payment
WHERE YEAR(payment_date) = 2005

--26
SELECT SUM(LEN(title))
FROM film