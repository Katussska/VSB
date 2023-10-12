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
SELECT first_name,
       last_name,
       address,
       postal_code,
       city
FROM customer
         JOIN address ON customer.address_id = address.address_id
         JOIN city ON address.city_id = city.city_id

--6
SELECT first_name,
       last_name,
       city
FROM customer
         JOIN address ON customer.address_id = address.address_id
         JOIN city ON address.city_id = city.city_id

--7
SELECT rental_id,
       staff.first_name + ' ' + staff.last_name       AS S_name,
       customer.first_name + ' ' + customer.last_name AS C_name,
       film.title
FROM rental
         JOIN staff ON rental.staff_id = staff.staff_id
         JOIN customer ON rental.customer_id = customer.customer_id
         JOIN inventory ON rental.inventory_id = inventory.inventory_id
         JOIN film ON inventory.film_id = film.film_id

--8
SELECT film.title,
       actor.first_name,
       actor.last_name
FROM film
         JOIN film_actor ON film.film_id = film_actor.film_id
         JOIN actor ON film_actor.actor_id = actor.actor_id
ORDER BY film.title

--9
SELECT actor.first_name,
       actor.last_name,
       film.title
FROM film
         JOIN film_actor ON film.film_id = film_actor.film_id
         JOIN actor ON film_actor.actor_id = actor.actor_id
ORDER BY actor.last_name, actor.first_name

--10
SELECT film.title
FROM category
         JOIN film_category ON
    category.category_id = film_category.category_id
         JOIN film ON film_category.film_id = film.film_id
WHERE category.name = 'Horror'

--11
SELECT store.store_id,
       store_address.address                    AS store_address,
       store_city.city                          AS store_city,
       store_country.country                    AS store_country,
       staff.first_name + ' ' + staff.last_name AS staff_name,
       staff_address.address                    AS staff_address,
       staff_city.city                          AS staff_city,
       staff_country.country                    AS staff_country
FROM store
         JOIN staff ON
    store.manager_staff_id = staff.staff_id
         JOIN address store_address ON
    store.address_id = store_address.address_id
         JOIN city store_city ON
    store_address.city_id = store_city.city_id
         JOIN country store_country ON
    store_city.country_id = store_country.country_id
         JOIN address staff_address ON
    staff.address_id = staff_address.address_id
         JOIN city staff_city ON
    staff_address.city_id = staff_city.city_id
         JOIN country staff_country ON
    staff_city.country_id = staff_country.country_id

--12


--24
SELECT *
FROM film
         LEFT JOIN language ON film.language_id = language.language_id AND language.name LIKE 'I%'