--
-- indexes.sql                      ENSICAEN                       2005
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
-- Crée les index qui vont permettre d'accélérer les requètes
--
-- Pour plus de détails concernant les indexes sous PostgreSQL, voir
-- la documentation (indexes.html).
--

--
-- Version :	1.0
--
-- Fait :	-
--
-- A faire :	-
--

-- Index pour les noms de genre
CREATE INDEX genre_nomg_idx
ON genre 
USING BTREE(nomg);

-- Index pour les noms de comédiens
CREATE INDEX com_identc_idx
ON com
USING BTREE(identc);

-- Index pour les titres de films
CREATE INDEX film_titre_idx
ON film
USING BTREE(titre);

-- Index pour les annees de sortie des films
CREATE INDEX film_annee_idx
ON film
USING BTREE(annee);

-- Index pour les noms de réalisateurs
CREATE INDEX realis_identr_idx
ON realis
USING BTREE(identr);


