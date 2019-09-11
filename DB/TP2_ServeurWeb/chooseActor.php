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

  <title>Choix d'un comédien</title>
</head>

<body>
  <?php
  include('inc/Connection.inc.php');
  include('inc/Movie.inc.php');
  include('inc/Actor.inc.php');
  include('inc/util_xhtml.inc.php');
  ?>

  <h1>Choix d'un comédien</h1>

  <fieldset>
    <form action="actorDetails.php" method="get">
      <p>
        <label for="actor_id">Comédien:</label>
        <select id="actor_id" name="actor_id">
        <?php
          $actors = Actor::getActors($con);
          foreach ($actors as $actor_row) {
            $actor = $actor_row[0];
            $actor_name = htmlspecialchars($actor->getName());;
            $tmp_actor_id = $actor->getId();
            $nb_movie = $actor_row[1];
            echo("<option value=\"$tmp_actor_id\"");
	    echo(">$actor_name ($nb_movie)</option>");
          }
        ?>
      </select></p>

      <p><input type="submit" value="Ok" /><input type="reset" value="Raz" /></p>
    </form>
  </fieldset>

 <?php
    include('inc/footer.inc.xhtml');
 ?>

</body>
</html>
