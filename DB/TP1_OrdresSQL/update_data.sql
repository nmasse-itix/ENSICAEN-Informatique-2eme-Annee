--
-- update_data.sql                      ENSICAEN                       2005
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
-- Corrige les enregistrements relatifs au réalisateur James CAMERON :
-- suppression de 'CAMERON James'
--

--
-- Version :	1.0
--
-- Fait :	-
--
-- A faire :	-
--

-- Les films de 'CAMERON James' sont désormais réalisés par 'CAMERON James F.'
UPDATE film
SET numr = 41
WHERE numr = 289;

-- 'CAMERON James' n'a plus lieu d'exister, on le supprime
DELETE FROM realis
WHERE numr = 289;

-- Liste des films réalisés par 'CAMERON James F.'
SELECT numf, titre, annee, identr
FROM film INNER JOIN realis USING (numr)
WHERE numr = 41;

