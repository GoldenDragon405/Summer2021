SELECT title FROM movies
JOIN stars on movies.id = stars.movie_id
JOIN people on stars.person_id = people.id
Join ratings on movies.id = ratings.movie_id
WHERE people.name = "Chadwick Boseman"
ORDER BY ratings.rating DESC
LIMIT 5;