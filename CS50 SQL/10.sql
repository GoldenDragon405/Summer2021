SELECT DISTINCT name FROM people
JOIN directors on directors.person_id = people.id
JOIN movies on movies.id = directors.movie_id
Join ratings on movies.id = ratings.movie_id
Where rating >= 9.0;
