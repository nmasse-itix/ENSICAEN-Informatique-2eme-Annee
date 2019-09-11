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

  <title>Détails d'un film</title>
</head>

<body>
  <?php
    include('inc/Connection.inc.php');
    include('inc/Movie.inc.php');
    include('inc/Actor.inc.php');
    include('inc/Director.inc.php');
    include('inc/Kind.inc.php');
    include('inc/util_xhtml.inc.php');


    if (array_key_exists('movie_id', $_GET)) {
        $movie_id = $_GET['movie_id'];
        $movie = Movie::getMovieById($movie_id);

        if ($movie != NULL) {
            $title_xhtml = htmlspecialchars($movie->getTitle());
        }
    }
  ?>

  <h1>
      <?php
          echo($title_xhtml);
      ?>
  </h1>

  <h2>Année de sortie:</h2>
  <p>
    <?php
	$year = $movie->getYear();
        yearToLink($year);
    ?>
  </p>

  <h2>Genre:</h2>
  <p>
    <?php
	$kindId = $movie->getKindId();
	$kind = Kind::getKindById($kindId);
	kindToLink($kind);
    ?>
  </p>
  
  <h2>Réalisateur:</h2>
  <p>
      <?php
          $dir_id = $movie->getDirId();
	  $director = Director::getDirectorById($dir_id);
	  if ($director == NULL) {
	      echo(" Réalisateur non trouvé!!");
          } else {
	      directorToLink($director);
          }
      ?>
  </p>
  
   <h2>Résumé:</h2>
   <p>
      <?php
          $resume = $movie->getTextPreview();

	  if ($resume <> NULL) {
 	      $resume_xhtml = htmlspecialchars($resume);
              echo($resume_xhtml);
          } else {
              echo('résumé non disponible');
          }
 
      ?>
  </p>
  
   <h2>Liste des acteurs:</h2>

   <ul>
      <?php
          $actors = $movie->getActorsList();

        if (count($actors) > 0) {
	    foreach ($actors as $actor) {
	      actorToLink($actor, TRUE);
	    }
         } else {
             echo('<li>Aucun acteur trouvé</li>');
         }


      ?>
  </ul>


 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
