--1
SELECT film.film_id,
       film.title,
       (SELECT COUNT(*)
        FROM film_actor
        WHERE film_actor.film_id = film.film_id)    AS pocet_hercu,
       (SELECT COUNT(*)
        FROM film_category
        WHERE film_category.film_id = film.film_id) AS pocet_kategorii
FROM film

--6
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
