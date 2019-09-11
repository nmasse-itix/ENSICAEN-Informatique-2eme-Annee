--
-- insert_data.sql                      ENSICAEN                       2005
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
-- Insere les donnees de la base de donnees dp
-- 
-- Pour obtenir la liste des champs d'une table, on utilise la commande
-- \d <table> du client psql
-- 
-- Par exemple, \dt films donne :
--
--               Table "public.films"
--    Column    |          Type          | Modifiers
-- -------------+------------------------+-----------
--  numerofilm  | integer                | not null
--  titre       | character varying(80)  |
--  genre       | integer                |
--  anneesortie | integer                |
--  realisateur | integer                |
--  resume      | character varying(255) |
-- Indexes:
--     "films_pkey" PRIMARY KEY, btree (numerofilm)
-- 
--

--
-- Version :	1.0
--
-- Fait :	-
--
-- A faire :	-
--


-- comediens 		=> com
--  numerocomedien 	->  numc
--  nomcomedien 	->  identc
INSERT INTO com (numc, identc)
SELECT numerocomedien, nomcomedien
FROM public.comediens;

-- genre		=> genre
--  numerogenre		->  numg
--  nomgenre		->  nomg
INSERT INTO genre (numg, nomg)
SELECT numerogenre, nomgenre
FROM public.genre;

-- Des enregistrements de la table film font reference a un genre 0 manquant.
INSERT INTO genre (numg, nomg)
VALUES (0, 'Inconnu');

-- realisateurs		=> realis
--  numerorealisateur	->  numr
--  nomrealisateur	->  identr
INSERT INTO realis (numr, identr)
SELECT numerorealisateur, nomrealisateur
FROM public.realisateurs;

-- films		=> film
--  numerofilm		->  numf
--  titre		->  titre
--  genre		->  numg
--  anneesortie		->  annee
--  realisateur		->  numr
--  resume		->  resume
INSERT INTO film (numf, titre, numg, annee, numr, resume)
SELECT numerofilm, titre, genre, anneesortie, realisateur, resume
FROM public.films;

-- com_film		=> role
--  numerofilm		->  numf
--  numerocomedien	->  numc
-- 
-- NOTE : Le film 337 n'existe pas dans la table role
INSERT INTO role (numf, numc)
SELECT numerofilm, numerocomedien
FROM public.com_film
WHERE numerofilm != 337;


