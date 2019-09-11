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

  <title>Liste par réalisateur</title>
</head>

<body>
  <?php
  include('inc/Connection.inc.php');
  include('inc/Movie.inc.php');
  include('inc/Director.inc.php');
  include('inc/util_xhtml.inc.php');
  ?>

  <h1>Liste par réalisateur</h1>

  <p>Formulaire pour obtenir la liste des films d'un réalisateur donné</p>

  <fieldset>
    <form action="listMovieByDirector.php" method="get">
      <p><label for="id_director">Réalisateur:</label> <select id="id_director" name="num_director">
        <?php
          // try to retrieve previously selected director
          if (array_key_exists('num_director', $_GET)) {
            $director_id = $_GET['num_director'];
          } else {
            unset($director_id);  
          }

          $directors = Director::getDirectors($con);
          foreach ($directors as $director_row) {
            $director = $director_row[0];
            $director_name = htmlspecialchars($director->getName());;
            $tmp_director_id = $director->getId();
            $nb_movie = $director_row[1];
            echo("<option value=\"$tmp_director_id\"");
	    if ((isset($director_id)) && ($director_id == $tmp_director_id)) {
              echo(' selected="selected"');
            }
	    echo(">$director_name ($nb_movie)</option>");
          }
        ?>
      </select></p>

      <p><input type="submit" value="Ok" /> <input type="reset" value="Raz" /></p>
    </form>
  </fieldset>

<?php

    if (isset($director_id)) {
      $director = Director::getDirectorById($director_id);
      if ($director != NULL) {
        $movies = $director->getMoviesList();
        echo("<p>Films réalisés par: ");
	directorToLink($director);
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
