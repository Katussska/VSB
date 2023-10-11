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
SELECT address
FROM address
         JOIN customer ON address.address_id = customer.address_id
WHERE customer.last_name = 'SIMPSON'

--5
SELECT first_name, last_name, address, postal_code, city
FROM customer
         JOIN address ON customer.address_id = address.address_id
         JOIN city ON address.city_id = city.city_id