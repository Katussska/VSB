--1
SELECT film.film_id,
       film.title,
       COUNT(DISTINCT actor_id)    AS pocet_hercu,
       COUNT(DISTINCT category_id) AS pocet_kategorii
FROM film
         LEFT JOIN film_category ON film.film_id = film_category.film_id
         LEFT JOIN film_actor ON film.film_id = film_actor.film_id
GROUP BY film.film_id, film.title;

--1.1
SELECT film.film_id,
       film.title,
       (SELECT COUNT(*)
        FROM film_actor
        WHERE film_actor.film_id = film.film_id)    AS pocet_hercu,
       (SELECT COUNT(*)
        FROM film_category
        WHERE film_category.film_id = film.film_id) AS pocet_kategorii
FROM film

--1.2
SELECT pocty_hercu.film_id,
       pocty_hercu.title,
       pocet_hercu,
       pocet_kategorii
FROM (SELECT film.film_id,
             film.title,
             COUNT(film_actor.film_id) AS pocet_hercu
      FROM film
               LEFT JOIN film_actor ON film.film_id = film_actor.film_id
      GROUP BY film.film_id, film.title) pocty_hercu
         JOIN
     (SELECT film.film_id,
             COUNT(film_category.film_id) AS pocet_kategorii
      FROM film
               LEFT JOIN film_category ON film.film_id = film_category.
          film_id
      GROUP BY film.film_id, film.title) pocty_kategorii ON pocty_hercu.film_id = pocty_kategorii.film_id

--1.3
WITH pocty_hercu AS (SELECT film.film_id,
                            film.title,
                            COUNT(film_actor.film_id) AS pocet_hercu
                     FROM film
                              LEFT JOIN film_actor ON film.film_id = film_actor.film_id
                     GROUP BY film.film_id, film.title),
     pocty_kategorii AS (SELECT film.film_id,
                                COUNT(film_category.film_id) AS pocet_kategorii
                         FROM film
                                  LEFT JOIN film_category ON film.film_id = film_category.film_id
                         GROUP BY film.film_id)
SELECT pocty_hercu.film_id,
       pocty_hercu.title,
       pocet_hercu,
       pocet_kategorii
FROM pocty_hercu
         JOIN pocty_kategorii ON pocty_hercu.film_id = pocty_kategorii.film_id

--2
SELECT first_name,
       last_name,
       (SELECT COUNT(*)
        FROM rental
        WHERE rental.customer_id = customer.customer_id
          AND DATEDIFF(DAY, return_date, return_date) < 5) AS kratsi_5,
       (SELECT COUNT(*)
        FROM rental
        WHERE rental.customer_id = customer.customer_id
          AND DATEDIFF(DAY, return_date, return_date) < 7) AS kratsi_7
FROM customer

--2.1
SELECT k5.first_name,
       k5.last_name,
       kratsi_5,
       kratsi_7
FROM (SELECT customer.customer_id,
             customer.first_name,
             customer.last_name,
             COUNT(rental.rental_id) AS kratsi_5
      FROM customer
               LEFT JOIN rental ON customer.customer_id = rental.customer_id
          AND DATEDIFF(DAY, rental_date, return_date) < 5
      GROUP BY customer.customer_id, customer.first_name, customer.last_name) k5
         JOIN (SELECT customer.customer_id,
                      customer.first_name,
                      customer.last_name,
                      COUNT(rental.rental_id) AS kratsi_7
               FROM customer
                        LEFT JOIN rental ON customer.customer_id = rental.customer_id
                   AND DATEDIFF(DAY, rental_date, return_date) < 7
               GROUP BY customer.customer_id, customer.first_name, customer.last_name) k7
              ON k5.customer_id = k7.customer_id

--2.2
WITH k5 AS (SELECT customer.customer_id,
                   customer.first_name,
                   customer.last_name,
                   COUNT(rental.rental_id) AS kratsi_5
            FROM customer
                     LEFT JOIN rental ON customer.customer_id = rental.customer_id
                AND DATEDIFF(DAY, rental_date, return_date) < 5
            GROUP BY customer.customer_id, customer.first_name, customer.last_name),
     k7 AS (SELECT customer.customer_id,
                   customer.first_name,
                   customer.last_name,
                   COUNT(rental.rental_id) AS kratsi_7
            FROM customer
                     LEFT JOIN rental ON customer.customer_id = rental.customer_id
                AND DATEDIFF(DAY, rental_date, return_date) < 7
            GROUP BY customer.customer_id, customer.first_name, customer.last_name)
SELECT k5.first_name, k5.last_name, kratsi_5, kratsi_7
FROM k5
         JOIN k7 ON k5.customer_id = k7.customer_id

--3.1
WITH t AS (SELECT inventory.store_id,
                  language.name
           FROM inventory
                    JOIN film ON inventory.film_id = film.film_id
                    JOIN language ON film.language_id = language.language_id)
SELECT store_id,
       (SELECT COUNT(*)
        FROM t
        WHERE t.name = 'English'
          AND t.store_id = store.store_id) AS english,
       (SELECT COUNT(*)
        FROM t
        WHERE t.name = 'French'
          AND t.store_id = store.store_id) AS french
FROM store

--4
SELECT film.film_id,
       film.title,
       (SELECT COUNT(*)
        FROM film_actor
        WHERE film_actor.film_id = film.film_id) AS pocet_hercu,
       (SELECT COUNT(DISTINCT customer_id)
        FROM inventory
                 JOIN rental ON inventory.inventory_id = rental.inventory_id
        WHERE inventory.film_id = film.film_id
          AND MONTH(rental.rental_date) = 8)     AS zak_srp,
       (SELECT AVG(amount)
        FROM payment
                 JOIN rental ON payment.rental_id = rental.rental_id
                 JOIN inventory ON rental.inventory_id = inventory.inventory_id
        WHERE inventory.film_id = film.film_id)  AS prum_platba
FROM film

--5
SELECT first_name,
       last_name
FROM customer
WHERE (SELECT COUNT(*)
       FROM payment
       WHERE payment.customer_id = customer.customer_id
         AND MONTH(payment_date) = 6) > 5
  AND (SELECT MAX(length)
       FROM film
                JOIN inventory ON film.film_id = inventory.film_id
                JOIN rental ON inventory.inventory_id = rental.inventory_id
       WHERE rental.customer_id = customer.customer_id) > 185

--5.1
SELECT first_name,
       last_name
FROM (SELECT first_name,
             last_name,
             (SELECT COUNT(*)
              FROM payment
              WHERE payment.customer_id = customer.customer_id
                AND MONTH(
                            payment_date) = 6)                 AS pocet,
             (SELECT MAX(length)
              FROM film
                       JOIN inventory ON film.film_id = inventory.film_id
                       JOIN rental ON inventory.inventory_id = rental.inventory_id
              WHERE rental.customer_id = customer.customer_id) AS max_delka
      FROM customer) t
WHERE pocet > 5
  AND max_delka >= 185

--6
SELECT first_name, last_name
FROM customer
WHERE (SELECT COUNT(*)
       FROM payment
       WHERE payment.customer_id = customer.customer_id
         AND amount > 4) >
      (SELECT COUNT(*)
       FROM payment
       WHERE payment.customer_id = customer.customer_id
         AND amount <= 4)

--6.1
SELECT first_name,
       last_name
FROM (SELECT first_name,
             last_name,
             (SELECT COUNT(*)
              FROM payment
              WHERE payment.customer_id = customer.customer_id
                AND amount > 4)  AS nad_4,
             (SELECT COUNT(*)
              FROM payment
              WHERE payment.customer_id = customer.customer_id
                AND amount <= 4) AS do_4
      FROM customer) pocty
WHERE nad_4 > do_4

--7
SELECT first_name,
       last_name
FROM actor
WHERE (SELECT COUNT(*)
       FROM film_actor
       WHERE film_actor.actor_id = actor.actor_id
         AND film_id IN (SELECT film_id
                         FROM film_category
                                  JOIN category ON film_category.category_id = category.category_id
                         WHERE category.name = 'comedy'))
          >
      (SELECT COUNT(*)
       FROM film_actor
       WHERE film_actor.actor_id = actor.actor_id
         AND film_id IN (SELECT film_id
                         FROM film_category
                                  JOIN category ON film_category.category_id = category.category_id
                         WHERE category.name = 'horror')) * 2
