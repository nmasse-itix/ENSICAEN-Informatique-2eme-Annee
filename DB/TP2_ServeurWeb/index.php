<?xml version="1.0" encoding="UTF-8" ?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr">
<head>
  <meta http-equiv="Content-Type" content="application/xhtml+xml" />
  <meta http-equiv="Pragma" content="nocache" />
  <title>TP2 de Base de données: base de données cinéma</title>
  <link type="text/css" href="index.css" rel="stylesheet" media="all" />
</head>

<body>
<h1>
TP2: Serveur Web
</h1>

<h2>
Introduction
</h2>

<p>
Ces quelques pages sont écrites en PHP 4, version qui bénéficie d'une approche que l'on peut qualifier "d'orientée objet", dans notre cas largement utilisée. Elle permettent la consultation de la base de données cinéma qui elle est prise en charge par un serveur PostgreSQL. Veuillez s'il vous plait excuser la présentation particulièrement spartiate de l'ensemble, les auteurs désirant respecter la norme XHTML 1.1 dans un but purement pédagogique, choix qui implique de faire la mise en forme à l'aide de feuille de style externes répondant au doux nom de CSS, ce qui ne fait pas partie (pour l'instant) de leurs compétences.
</p>

<h2>
Importation de données
</h2>

<p>
TODO
</p>

<h2>
Consultation de données
</h2>

<ul>

<li>
<a href="listMovieByKind.php">
La liste des films d'un genre donné
</a>
</li>

<li>
<a href="listMovieByDirector.php">
Liste des films d'un réalisateur donné
</a>
</li>

<li>
<a href="listMovieWithActor.php">
Liste des films dans lesquels un acteur donné a joué un role
</a>
</li>

<li>
<a href="findMovieFromTitle.php">
L'ensemble des données sur un film (titre, genre, année de sortie, réalisateur, résumé, principaux comédiens)
</a>
</li>

<li>
<a href="chooseActor.php">
L'ensemble des données sur un comédien (identité, filmographie, nombre de films référençés par genre)
</a>
</li>

<li>
<a href="chooseDirector.php">
L'ensemble des données sur un réalisateur (identité, filmographie, nombre de films référencés par genre)
</a>
</li>

</ul>

<h2>
Catalogue des films
</h2>

<ul>
<li>
<a href="movie_catalog.php">
Liste des films, classés par genre
</a>
</li>
</ul>


<?php
    include('inc/footer.inc.xhtml');
?>

</body>
</html>
