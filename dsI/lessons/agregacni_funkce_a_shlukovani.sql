--1
SELECT rating,
       COUNT(*) AS pocet
FROM film
GROUP BY rating

--2
SELECT customer_id,
       COUNT(last_name) AS pocet
FROM customer
GROUP BY customer_id

--3
SELECT customer_id
FROM payment
GROUP BY customer_id
ORDER BY SUM(amount)

--4
SELECT first_name,
       last_name,
       COUNT(*) AS pocet
FROM actor
GROUP BY first_name, last_name
ORDER BY pocet DESC

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

--7
SELECT language_id
FROM film
GROUP BY language_id
HAVING MIN(length) > 46

--8
SELECT YEAR(payment_date)  AS rok,
       MONTH(payment_date) AS mesic,
       SUM(amount)         AS soucet
FROM payment
GROUP BY YEAR(payment_date),
         MONTH(payment_date)
HAVING SUM(amount) > 20000

--9
SELECT rating
FROM film
WHERE length < 50
GROUP BY rating
HAVING SUM(length) > 250
ORDER BY rating DESC

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

--14
SELECT customer.customer_id,
       customer.first_name + ' ' + customer.last_name AS name,
       COUNT(DISTINCT inventory.film_id)              AS pocet_filmu
FROM customer
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
         LEFT JOIN inventory ON rental.inventory_id = inventory.inventory_id
GROUP BY customer.customer_id, first_name, last_name

--15
SELECT actor.first_name,
       actor.last_name
FROM actor
         JOIN film_actor ON actor.actor_id = film_actor.actor_id
GROUP BY actor.actor_id, actor.first_name, actor.last_name
HAVING COUNT(film_actor.film_id) > 20

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

--17
SELECT category.category_id,
       category.name,
       AVG(CAST(film.length AS FLOAT)) AS prumer
FROM category
         LEFT JOIN film_category ON category.category_id = film_category.category_id
         LEFT JOIN film ON film_category.film_id = film.film_id
GROUP BY category.category_id, category.name

--18
SELECT film.film_id,
       film.title,
       SUM(payment.amount) AS celkem
FROM film
         LEFT JOIN inventory ON film.film_id = inventory.film_id
         LEFT JOIN rental ON inventory.inventory_id = rental.inventory_id
         LEFT JOIN payment ON rental.rental_id = payment.rental_id
GROUP BY film.film_id, film.title
HAVING SUM(payment.amount) > 100

--19
SELECT actor.actor_id,
       actor.first_name,
       actor.last_name,
       COUNT(DISTINCT film_category.category_id) AS pocet_kategorii
FROM actor
         LEFT JOIN film_actor ON actor.actor_id = film_actor.actor_id
         LEFT JOIN film_category ON film_actor.film_id = film_category.film_id
GROUP BY actor.actor_id, actor.first_name, actor.last_name

--20
SELECT address.address,
       city.city,
       country.country
FROM customer
         JOIN address ON customer.address_id = address.address_id
         JOIN city ON address.city_id = city.city_id
         JOIN country ON city.country_id = country.country_id
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
         LEFT JOIN inventory ON rental.inventory_id = inventory.inventory_id
         LEFT JOIN film_actor ON inventory.film_id = film_actor.film_id
GROUP BY address.address, city.city, country.country
HAVING COUNT(DISTINCT film_actor.actor_id) >= 40

--21
SELECT film.film_id,
       film.title,
       COUNT(DISTINCT address.city_id) AS pocet_mest
FROM film
         JOIN film_category ON film.film_id = film_category.film_id
         JOIN category ON film_category.category_id = category.category_id
         LEFT JOIN inventory ON film.film_id = inventory.film_id
         LEFT JOIN rental ON inventory.inventory_id = rental.inventory_id
         LEFT JOIN customer ON rental.customer_id = customer.customer_id
         LEFT JOIN address ON customer.address_id = address.address_id
WHERE category.name = 'Horror'
GROUP BY film.film_id, film.title

--22
SELECT customer.customer_id,
       customer.first_name,
       customer.last_name,
       COUNT(DISTINCT film_category.category_id) AS pocet_kategorii
FROM country
         JOIN city ON country.country_id = city.country_id
         JOIN address ON city.city_id = address.city_id
         JOIN customer ON address.address_id = customer.address_id
         LEFT JOIN rental ON customer.customer_id = rental.customer_id
         LEFT JOIN inventory ON rental.inventory_id = inventory.inventory_id
         LEFT JOIN film ON inventory.film_id = film.film_id
         LEFT JOIN film_category ON film.film_id = film_category.film_id
WHERE country.country = 'Poland'
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

--25
SELECT category.name
FROM category
         LEFT JOIN film_category ON category.category_id = film_category.category_id
         LEFT JOIN film ON film_category.film_id = film.film_id
         LEFT JOIN language ON film.language_id = language.language_id AND
                               language.name LIKE 'E%'
GROUP BY category.name
ORDER BY COUNT(language.language_id)

--26
SELECT film.film_id,
       film.title,
       customer.last_name,
       COUNT(customer.
           customer_id)
FROM film
         LEFT JOIN inventory ON film.film_id = inventory.film_id
         LEFT JOIN rental ON inventory.inventory_id = rental.inventory_id
         LEFT JOIN customer ON rental.customer_id = customer.customer_id AND
                               customer.last_name = 'BELL'
WHERE film.length < 50
GROUP BY film.film_id, film.title, customer.last_name
HAVING COUNT(customer.customer_id) = 1
--or
SELECT film.film_id,
       film.title,
       customer.last_name,
       COUNT(customer.
           customer_id)
FROM film
         JOIN inventory ON film.film_id = inventory.film_id
         JOIN rental ON inventory.inventory_id = rental.inventory_id
         JOIN customer ON rental.customer_id = customer.customer_id
WHERE film.length < 50
  AND customer.last_name = 'BELL'
GROUP BY film.film_id, film.title, customer.last_name
HAVING COUNT(customer.customer_id) = 1