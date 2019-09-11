<?xml version="1.0" encoding="utf-8"?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
  "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr">
<head>
  <meta name="generator" content=
  "HTML Tidy for Linux/x86 (vers 1st August 2004), see www.w3.org" />
  <meta http-equiv="Content-Type" content=
  "application/xhtml+xml" />
  <meta http-equiv="Pragma" content="nocache" />

  <title>Catalogue des films</title>
</head>

<body>
  <?php
  include('inc/Connection.inc.php');
  include('inc/Movie.inc.php');
  include('inc/Kind.inc.php');
  include('inc/util_xhtml.inc.php');
  ?>

  <h1>Catalogue des films</h1>

  <p>Catalogue de l'ensemble des films présents dant la base de données Cinéma, classés par genre, et listés par année de sortie décroissante</p>

  <?php
          $kinds = Kind::getKinds($con);
          foreach ($kinds as $kind_row) {
            $kind = $kind_row[0];
            $kind_name = htmlspecialchars($kind->getName());
	    echo("<h2>$kind_name</h2><ul>");
            $kind_id = $kind->getId();
	    $movies = $kind->getMoviesList(1);
	    foreach ($movies as $movie) {
		movieToLink($movie, TRUE);
            }
	    echo("</ul>");
          }
  ?>

 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
