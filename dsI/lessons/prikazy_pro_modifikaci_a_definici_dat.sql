--1.1
INSERT INTO actor (first_name, last_name)
VALUES ('Arnold', 'Schwarzenegger');

--1.2
INSERT INTO film (title, description, language_id, rental_duration,
                  rental_rate, length)
VALUES (N'Terminátor', N'Z roku 2029 je do Los Angeles roku 1984
vyslán zabijácký stroj podobný člověku...', 1, 3, 1.99, 107);

--1.3
SELECT film_id
FROM film
WHERE title = N'Terminátor'

SELECT actor_id
FROM actor
WHERE last_name = 'Schwarzenegger'

INSERT INTO film_actor (film_id, actor_id)
VALUES (1001, 201)

--1.4
SELECT film_id
FROM film
WHERE title = N'Terminátor'

SELECT *
FROM category

INSERT INTO film_category (film_id, category_id)
VALUES (1001, 1);
INSERT INTO film_category (film_id, category_id)
VALUES (1001, 14)

--1.5
INSERT INTO film_category (film_id, category_id)
VALUES ((SELECT film_id FROM film WHERE title = N'Terminátor'),
        (SELECT category_id FROM category WHERE name = 'Comedy'))

--1.6
UPDATE film
SET rental_rate = 2.99,
    last_update = CURRENT_TIMESTAMP
WHERE title = N'Terminátor'

--2.1 zjisteni id naseho statu
SELECT *
FROM country
ORDER BY country

--2.2 zjisteni id naseho mesta
SELECT *
FROM city
WHERE country_id = 26
ORDER BY city

--2.3