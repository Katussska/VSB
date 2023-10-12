--1
SELECT rating,
       COUNT(*) AS pocet
FROM film
GROUP BY rating

--5
SELECT YEAR(payment_date)  AS rok,
       MONTH(payment_date) AS mesic,
       SUM(amount)         AS soucet
FROM payment
GROUP BY YEAR(payment_date), MONTH(payment_date)
ORDER BY rok, mesic

--6
SELECT store_id,
       COUNT(*) AS pocet
FROM inventory
GROUP BY store_id
HAVING COUNT(*) > 2300
--HAVING vzdy, kdyz porovnavame agregacni funkce, bcs se vyhodnocuje po GROUP BY a SELECT pred

--10
SELECT language_id,
       COUNT(*) AS pocet
FROM film
GROUP BY language_id

--11
SELECT language.language_id,
       language.name,
       COUNT(*) AS pocet
FROM film
         JOIN language ON film.language_id = language.language_id
GROUP BY language.language_id, language.name

--12
SELECT language.language_id,
       language.name,
       COUNT(film.film_id) AS pocet
FROM language
         LEFT JOIN film ON film.language_id = language.language_id
GROUP BY language.language_id, language.name


--13
SELECT customer.customer_id,
       customer.first_name,
       customer.last_name,
       COUNT(rental.rental_id) AS vypujcek
FROM customer
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
GROUP BY customer.customer_id, customer.first_name, customer.last_name
--POUZE PROCVICENI: HAVING COUNT(rental.rental_id) > 40

--16
SELECT customer.first_name,
       customer.last_name,
       SUM(payment.amount) AS castka,
       MIN(payment.amount) AS minimum,
       MAX(payment.amount) AS maximum,
       AVG(payment.amount) AS prumer

FROM customer
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
         LEFT JOIN payment ON rental.rental_id = payment.rental_id
GROUP BY customer.customer_id, customer.first_name, customer.last_name

--23
SELECT language.name,
       COUNT(film.film_id) AS pocet
FROM language
         LEFT JOIN film ON language.language_id = film.language_id
    AND film.length > 350
GROUP BY language.name

--24
SELECT customer.customer_id,
       customer.first_name,
       customer.last_name,
       COALESCE(SUM(payment.amount), 0) AS celkem
FROM customer
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
    AND MONTH(rental.rental_date) = 6
         LEFT JOIN payment ON rental.rental_id = payment.rental_id
GROUP BY customer.customer_id, first_name, last_name