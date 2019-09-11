--
-- queries.sql                      ENSICAEN                       2005
--
-- MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
-- LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
--
-- ENSICAEN
-- 6 Boulevard Marechal Juin
-- F-14050 Caen Cedex
--
-- Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
-- reproduit, utilise ou modifie sans l'avis express de ses auteurs.
--

--
-- Exécute les requetes demandées dans l'énoncé
--

--
-- Version :	0.0.1
--
-- Fait :	Detail de ce qui a ete fait.
--
-- A faire :	Detail de ce qui n'a pas ete fait.
--

-- On ecrit dans le fichier queries.html
\o queries.html

-- On active le mode HTML
\pset format html
\T 'width="100%"'

-- En-tête
\qecho '<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/TR/html4/strict.dtd">'
\qecho '<html>'
\qecho '<head>'
\qecho '<title>Résultat des requètes</title>'
\qecho '<meta http-equiv="Content-Type" content="text/html; charset=utf-8">'
\qecho '</head>'
\qecho '<body>'

\C '4.a - Titres des films réalisés par Woody ALLEN'
SELECT numf AS "Numéro", titre AS "Titre", annee AS "Année", nomg AS "Genre", identr AS "Réalisateur"
FROM film NATURAL JOIN genre NATURAL JOIN realis
WHERE identr = 'ALLEN Woody';

\C '4.b - Titres et années de sortie des films réalisés par Charlie CHAPLIN entre 1930 et 1940'
SELECT numf AS "Numéro", titre AS "Titre", annee AS "Année", nomg AS "Genre", identr AS "Réalisateur"
FROM film NATURAL JOIN genre NATURAL JOIN realis
WHERE identr = 'CHAPLIN Charlie'
AND annee BETWEEN 1930 AND 1940;

\C '4.c - Noms des acteurs, triés par ordre alphabétique, du film "Les lumières de la ville"'
SELECT identc AS "Comédien", titre AS "Film"
FROM film NATURAL JOIN role NATURAL JOIN com
WHERE titre = 'Les lumieres de la ville'
ORDER BY identc ASC;

\C '4.d - Titre des films d\'espionnage sortis en 1987'
SELECT numf AS "Numéro", titre AS "Titre", annee AS "Année", nomg AS "Genre", identr AS "Réalisateur"
FROM film NATURAL JOIN genre NATURAL JOIN realis
WHERE nomg = 'Espionnage'
AND annee = 1987;

\C '4.e - Nombre de films joués par Gérard DEPARDIEU'
SELECT count(*) AS "Nombre"
FROM role
WHERE numc = (SELECT numc FROM com WHERE identc = 'DEPARDIEU Gerard');

\C '4.f - Noms des réalisateurs, triés par ordre alphabétique, qui sont également comédiens'
SELECT identr AS "Réalisateur"
FROM realis, com
WHERE identc = identr
ORDER BY identr ASC;

\C '4.g - Titres des films et nom des réalisateurs des films de la série Star Trek'
SELECT numf AS "Numéro", titre AS "Titre", annee AS "Année", nomg AS "Genre", identr AS "Réalisateur"
FROM film NATURAL JOIN genre NATURAL JOIN realis
WHERE titre LIKE 'Star Trek%';

\C '4.h - Nom des comédiens ayant joué dans au moins 5 films'
SELECT identc AS "Nom du comédien", count(*) AS "Nombre de films"
FROM role NATURAL JOIN com
GROUP BY identc
HAVING count(*) >= 5
ORDER BY count(*) DESC;

\qecho '</body>'
\qecho '</html>'
