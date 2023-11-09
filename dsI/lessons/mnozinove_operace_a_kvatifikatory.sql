--1.1


--1.2


--2
SELECT film_id
FROM film_actor
WHERE actor_id = 1

--3
SELECT film_id,
       title
FROM film
WHERE film_id IN (SELECT film_id FROM film_actor WHERE actor_id = 1)
  AND film_id IN (SELECT film_id FROM film_actor WHERE actor_id = 10)

--4
SELECT film_id,
       title
FROM film
WHERE film_id IN (SELECT film_id FROM film_actor WHERE actor_id = 1 OR actor_id = 10)

--5
SELECT film_id,
       title
FROM film
WHERE film_id NOT IN (SELECT film_id FROM film_actor WHERE actor_id = 1)

--7
SELECT film_id,
       title
FROM film
WHERE film_id IN (SELECT film_id
                  FROM actor
                           JOIN film_actor ON
                      actor.actor_id = film_actor.actor_id
                  WHERE actor.first_name = 'PENELOPE'
                    AND actor.last_name = 'GUINESS')
  AND film_id IN (SELECT film_id
                  FROM actor
                           JOIN film_actor
                                ON actor.actor_id = film_actor.actor_id
                  WHERE actor.first_name = 'CHRISTIAN'
                    AND actor.last_name = 'GABLE')

SELECT *
FROM organ;
