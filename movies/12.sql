SELECT title FROM movies
Join people on people.id = stars.person_id
Join stars on movies.id = stars.movie_id
Where people.name = "Johnny Depp"
INTERSECT
SELECT title FROM movies
Join people on people.id = stars.person_id
Join stars on movies.id = stars.movie_id
Where people.name = "Helena Bonham Carter";
