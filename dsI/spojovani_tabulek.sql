--1
SELECT *
FROM city
         JOIN country ON city.country_id = country.country_id

--2
SELECT film.title, language.name
FROM film
         JOIN language ON film.language_id = language.language_id

--3
SELECT rental_id
FROM rental
         JOIN customer ON
    rental.customer_id = customer.customer_id
WHERE customer.last_name = 'SIMPSON'

--4