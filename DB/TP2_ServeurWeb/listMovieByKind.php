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

  <title>Liste par genre</title>
</head>

<body>
  <?php
  include('inc/Connection.inc.php');
  include('inc/Movie.inc.php');
  include('inc/Kind.inc.php');
  include('inc/util_xhtml.inc.php');
  ?>

  <h1>Liste par genre</h1>

  <p>Formulaire pour obtenir la liste des films d'un genre donné</p>

  <fieldset>
    <form action="listMovieByKind.php" method="get">
      <p><label for="id_genre">Genre:</label> <select id="id_genre" name="num_genre">
        <?php
          // try to retrieve previously selected kind
          if (array_key_exists('num_genre', $_GET)) {
            $kind_id = $_GET['num_genre'];
          } else {
            unset($kind_id);  
          }

          $kinds = Kind::getKinds($con);
          foreach ($kinds as $kind_row) {
            $kind = $kind_row[0];
            $kind_name = htmlspecialchars($kind->getName());;
            $tmp_kind_id = $kind->getId();
            $nb_movie = $kind_row[1];
            echo("<option value=\"$tmp_kind_id\"");
	    if ((isset($kind_id)) && ($kind_id == $tmp_kind_id)) {
              echo(' selected="selected"');
            }
	    echo(">$kind_name ($nb_movie)</option>");
          }
        ?>
      </select></p>

      <p><input type="submit" value="Send" /> <input type="reset" /></p>
    </form>
  </fieldset>

<?php

    if (isset($kind_id)) {
      $kind = Kind::getKindById($kind_id);
      if ($kind != NULL) {
        $movies = $kind->getMoviesList();
        echo("<p>Films trouvés pour le genre: ");
	kindToLink($kind);
        echo("</p><ul>");

        if (count($movies) > 0) {
	    foreach ($movies as $movie) {
	      movieToLink($movie, TRUE);
	    }
         } else {
             echo('<li>Aucun film trouvé</li>');
         }

        echo("</ul>");
      }
    }
?>

 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
