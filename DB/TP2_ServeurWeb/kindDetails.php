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

  <title>Détail d'un genre</title>
</head>

<body>
  <?php
    include('inc/Connection.inc.php');
    include('inc/Movie.inc.php');
    include('inc/Kind.inc.php');
    include('inc/util_xhtml.inc.php');

    if (array_key_exists('kind_id', $_GET)) {
        $kind_id = $_GET['kind_id'];
        $kind = Kind::getKindById($kind_id);

        if ($kind != NULL) {
            $name_xhtml = htmlspecialchars($kind->getName());
        }
    }
  ?>

  <h1>
      <?php
          echo($name_xhtml);
      ?>
  </h1>
  
   <h2>Films de ce genre:</h2>

   <ul>
      <?php
          $movies = $kind->getMoviesList();

          foreach ($movies as $movie) {
	      movieToLink($movie, TRUE);
          }


      ?>
  </ul>


 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
