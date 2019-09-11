-- categ(_codecat_, libcat)
CREATE TABLE categ (
	codecat		SERIAL PRIMARY KEY,
	libcat		VARCHAR(50) NOT NULL
);

-- auteur(_numaut_, identaut)
CREATE TABLE auteur (
	numaut		SERIAL PRIMARY KEY,
	identaut	VARCHAR(50)
);

-- livre(_numliv_, titre, codecat*, annee, nbexe)
CREATE TABLE livre (
	numliv		SERIAL PRIMARY KEY,
	titre		VARCHAR(100) NOT NULL,
	codecat		INTEGER REFERENCES categ,
	annee		INTEGER NOT NULL,
	nbexe		INTEGER NOT NULL DEFAULT 1
);

-- ecritpar(_numliv*, numaut*_)
CREATE TABLE ecritpar (
	numliv		INTEGER NOT NULL REFERENCES livre,
	numaut		INTEGER NOT NULL REFERENCES auteur,
			PRIMARY KEY (numliv, numaut)
);


