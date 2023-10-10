--1

--3
select *
from payment
where payment_date >= '2006-01-01'
  and amount < 2;

--4
select description
from film
where rating = 'G'
   or rating = 'PG';

--5
select description
from film
where rating in ('G', 'PG', 'PG-13');

--6
select description
from film
where rating not in ('G', 'PG', 'PG-13');

--7
select *
from film
where length > 50
  and rental_duration in (3, 5);

--8
select title
from film
where (title like '%RAINBOW%' or title like 'TEXAS%')
  and length > 70;

--9
select title
from film
where description like '%AND%'
  and length between 80 and 90
  and rental_duration % 2 = 1;

--10
select distinct special_features
from film
where replacement_cost between 14 and 16
order by special_features;

--12
select *
from address
where postal_code is not null;

--13
select distinct customer_id
from rental
where return_date is null;

--21
select count(*) as pocet
from film;

--22
select count(distinct rating) as pocet_klas
from film;

--23
select count(*) as pocet_vsech, count(distinct postal_code) as ruzna_psc, count(postal_code) as pocet_s_psc
from address;