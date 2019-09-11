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

  <title>Détails d'un réalisateur</title>
</head>

<body>
  <?php
    include('inc/Connection.inc.php');
    include('inc/Movie.inc.php');
    include('inc/Director.inc.php');
    include('inc/util_xhtml.inc.php');

    if (array_key_exists('director_id', $_GET)) {
        $director_id = $_GET['director_id'];
        $director = Director::getDirectorById($director_id);

        if ($director != NULL) {
            $name_xhtml = htmlspecialchars($director->getName());
        }
    }
  ?>

  <h1>
      <?php
          echo($name_xhtml);
      ?>
  </h1>
  
   <h2>Filmographie:</h2>

   <ul>
      <?php
          $movies = $director->getMoviesList();

        if (count($movies) > 0) {
	    foreach ($movies as $movie) {
	      movieToLink($movie, TRUE);
	    }
         } else {
             echo('<li>Aucun film trouvé</li>');
         }

      ?>
  </ul>


 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
