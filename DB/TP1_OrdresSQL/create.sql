--
-- create.sql                    ENSICAEN                       2005
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
-- Creation des tables
--

--
-- Version :	0.0.1
--
-- Fait :	-
--
-- A faire :	-
--


-- genre(_numg_, nomg)
--   numg 	: identifiant de genre
--   nomg 	: nom du genre
CREATE TABLE genre (
	numg		INTEGER PRIMARY KEY,
	nomg		VARCHAR(80) NOT NULL
);

-- com(_numc_, identc)
--   numc 	: identifiant de comedien
--   identc 	: nom et prenom du comedien
CREATE TABLE com (
	numc		INTEGER PRIMARY KEY,
	identc		VARCHAR(30) NOT NULL
);

-- realis(_numr_, identr)
--   numr	: identifiant du realisateur
--   identr	: nom et prenom du realisateur
CREATE TABLE realis (
	numr		INTEGER PRIMARY KEY,
	identr		VARCHAR(30) NOT NULL
);

-- film(_numf_, titre, numg*, annee, numr*, resume)
--   numf 	: identifiant du film
--   titre	: titre du film
--   numg 	: identifiant du genre, reference la table genre
--   annee	: annee de sortie du film
--   numr	: identifiant du realisateur du film, reference la table realis
--   resume	: resume du film
CREATE TABLE film (
	numf		INTEGER PRIMARY KEY,
	titre		VARCHAR(80) NOT NULL,
	numg		INTEGER NOT NULL REFERENCES genre,
	annee 		INTEGER NOT NULL DEFAULT date_part('year', now()) 
				CHECK (annee > 1850 
					AND annee <= date_part('year', now())
				),
	numr		INTEGER NOT NULL REFERENCES realis,
	resume		TEXT
);

-- role(_numc*, numf*_)
--   numc	: identifiant du comedien, reference la table com
--   numf	: identifiant du film, reference la table film
CREATE TABLE role (
	numc		INTEGER NOT NULL REFERENCES com,
	numf		INTEGER NOT NULL REFERENCES film,
			PRIMARY KEY (numc, numf)
);


