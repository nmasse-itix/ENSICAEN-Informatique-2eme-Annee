-- Auteurs : V.Hugo, Jean d'Ormesson, Balzac, Stendhal, Flaubert, Verlaine
INSERT INTO auteur (identaut) VALUES ('V. Hugo');
INSERT INTO auteur (identaut) VALUES ('Jean d''Ormesson');
INSERT INTO auteur (identaut) VALUES ('Balzac');
INSERT INTO auteur (identaut) VALUES ('Stendhal');
INSERT INTO auteur (identaut) VALUES ('Flaubert');
INSERT INTO auteur (identaut) VALUES ('Verlaine');

-- Catégories : théatre, poésie, roman
INSERT INTO categ (libcat) VALUES ('théatre');
INSERT INTO categ (libcat) VALUES ('poésie');
INSERT INTO categ (libcat) VALUES ('roman');

-- ----------------------------------------------------------------------------
--                                     Livres
-- ----------------------------------------------------------------------------

-- "Hernani" de V.Hugo, théatre, 1830
INSERT INTO livre (titre, codecat, annee)
SELECT 'Hernani', codecat, 1830
FROM categ
WHERE libcat = 'théatre';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Hernani'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'V. Hugo')
);


-- "Les contemplations" de V.Hugo, poésie, 1856
INSERT INTO livre (titre, codecat, annee)
SELECT 'Les contemplations', codecat, 1856
FROM categ
WHERE libcat = 'poésie';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Les contemplations'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'V. Hugo')
);

-- "Les misérables" de V.Hugo, roman, 1860
INSERT INTO livre (titre, codecat, annee)
SELECT 'Les misérables', codecat, 1860
FROM categ
WHERE libcat = 'roman';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Les misérables'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'V. Hugo')
);

-- "Eugènie grandet" de Balzac, roman, 1833
INSERT INTO livre (titre, codecat, annee)
SELECT 'Eugénie grandet', codecat, 1833
FROM categ
WHERE libcat = 'roman';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Eugénie grandet'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'Balzac')
);

-- "Le rouge et le noir" de Stendhal, roman, 1831
INSERT INTO livre (titre, codecat, annee)
SELECT 'Le rouge et le noir', codecat, 1831
FROM categ
WHERE libcat = 'roman';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Le rouge et le noir'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'Stendhal')
);

-- "Madame Bovary" de Flaubert, roman, 1857
INSERT INTO livre (titre, codecat, annee)
SELECT 'Madame Bovary', codecat, 1857
FROM categ
WHERE libcat = 'roman';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Madame Bovary'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'Flaubert')
);

-- "Poèmes saturniens" de Verlaine, poésie, 1866
INSERT INTO livre (titre, codecat, annee)
SELECT 'Poèmes saturniens', codecat, 1866
FROM categ
WHERE libcat = 'poésie';

INSERT INTO ecritpar (numliv, numaut) VALUES (
	(SELECT numliv
	 FROM livre
	 WHERE titre = 'Poèmes saturniens'),
	(SELECT numaut
	 FROM auteur
	 WHERE identaut = 'Verlaine')
);


