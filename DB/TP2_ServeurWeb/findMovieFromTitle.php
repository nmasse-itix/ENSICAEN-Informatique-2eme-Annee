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

  <title>Rechercher d'un film à partir de son titre</title>
</head>

<body>
  <?php
    include('inc/Connection.inc.php');
    include('inc/Movie.inc.php');
    include('inc/util_xhtml.inc.php');
    ?>

  <h1>Recherche d'un film à partir de son titre</h1>

  <fieldset>
    <form action="findMovieFromTitle.php" method="get">
      <p><label for="title_part">Titre ou partie du
      titre:</label><br />
      <input id="title_part" name="title_part" <?php
                // try to retrieve previously selected movie
                if (array_key_exists('title_part', $_GET)) {
                  $title_part = $_GET['title_part'];
                  $title_part_xhtml = htmlspecialchars($title_part);
                  echo("value=\"$title_part_xhtml\"");
                } else {
                  unset($title_part);
                }
              ?> /><br />
      <input type="submit" value="Send" /> <input type=
      "reset" /></p>
    </form>
  </fieldset><?php

      if (isset($title_part)) {
        $movies = Movie::getMoviesWithTitleMatching($title_part);
          echo("<p>Films dont le titre contient \"$title_part_xhtml\":</p><ul>");

        if (count($movies) > 0) {
	    foreach ($movies as $movie) {
	      movieToLink($movie, TRUE);
	    }
         } else {
             echo('<li>Aucun film ne correspond au critère de recherche</li>');
         }

         echo("</ul>");
  }
  ?>

  <?php
    include('inc/footer.inc.xhtml');
  ?>

</body>
</html>
