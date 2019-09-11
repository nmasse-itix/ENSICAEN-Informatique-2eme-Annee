<?xml version="1.0" encoding="utf-8" ?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1//EN"
  "http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="fr">
<head>
  <meta name="generator" content=
  "HTML Tidy for Linux/x86 (vers 1st August 2004), see www.w3.org" />
  <meta http-equiv="Content-Type" content=
  "application/xhtml+xml" />
  <meta http-equiv="Pragma" content="nocache" />

  <title>Liste par acteur</title>
</head>

<body>
  <?php
  include('inc/Connection.inc.php');
  include('inc/Movie.inc.php');
  include('inc/Actor.inc.php');
  include('inc/util_xhtml.inc.php');
  ?>

  <h1>Liste des films ou l'acteur précisé tient un role</h1>

  <p>Formulaire pour obtenir la liste des films dans lequel joue le comédien donné</p>

  <fieldset>
    <form action="listMovieWithActor.php" method="get">
      <p><label for="id_actor">Comédien:</label> <select id="id_actor" name="num_actor">
        <?php
          // try to retrieve previously selected actor
          if (array_key_exists('num_actor', $_GET)) {
            $actor_id = $_GET['num_actor'];
          } else {
            unset($actor_id);  
          }

          $actors = Actor::getActors($con);
          foreach ($actors as $actor_row) {
            $actor = $actor_row[0];
            $actor_name = htmlspecialchars($actor->getName());
            $tmp_actor_id = $actor->getId();
            $nb_movie = $actor_row[1];
            echo("<option value=\"$tmp_actor_id\"");
	    if ((isset($actor_id)) && ($actor_id == $tmp_actor_id)) {
              echo(' selected="selected"');
            }
	    echo(">$actor_name ($nb_movie)</option>");
          }
        ?>
      </select></p>

      <p><input type="submit" value="Ok" /> <input type="reset" value="Raz" /></p>
    </form>
  </fieldset>

<?php

    if (isset($actor_id)) {
      $actor = Actor::getActorById($actor_id);
      if ($actor != NULL) {
        $movies = $actor->getMoviesList();
        echo("<p>Films dans lesquels à joué : ");
	actorToLink($actor);
	echo("</p><ul>");

        if (count($movies) > 0) {
	    foreach ($movies as $movie) {
	      movieToLink($movie, TRUE);
	    }
         } else {
             echo('<li>Aucun film trouvé</li>');
k         }

        echo("</ul>");
      }
    }
?>

 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
