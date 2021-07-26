SELECT DISTINCT name from people
Join stars on people.id = stars.person_id
Join movies on movies.id = stars.movie_id
Where movies.year = "2004"
ORDER BY people.birth;