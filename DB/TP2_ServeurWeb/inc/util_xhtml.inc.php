<?php
  /** 
   * #(@)util_xhtml.inc.php                 ENSICAEN                       2005
   *
   * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
   * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
   *
   * ENSICAEN
   * 6 Boulevard Marechal Juin
   * F-14050 Caen Cedex
   *
   * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
   * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
   */

/**
 * Write a link pointing towards the actor details page
 *
 * @param actor		the actor
 * @param listElement	if true, write the link as a list element
 */
function actorToLink($actor, $listElement = FALSE) {
  $actor_name = $actor->getName();
  $actor_name_xhtml = htmlspecialchars($actor_name);
  $actor_id = $actor->getId();

  if ($listElement) {
    echo("<li><a href=\"actorDetails?actor_id=$actor_id\">$actor_name_xhtml</a></li>");
  } else {
    echo("<a href=\"actorDetails?actor_id=$actor_id\">$actor_name_xhtml</a>");
  }
}

/**
 * Write a link pointing towards the movie details page
 *
 * @param movie		the movie
 * @param listElement	if true, write the link as a list element
 */
function movieToLink($movie, $listElement = FALSE) {
  $movie_title = $movie->getTitle();
  $movie_title_xhtml = htmlspecialchars($movie_title);
  $movie_id = $movie->getId();

  if ($listElement) {
    echo("<li><a href=\"movieDetails?movie_id=$movie_id\">$movie_title_xhtml</a></li>");
  } else {
    echo("<a href=\"movieDetails?movie_id=$movie_id\">$movie_title_xhtml</a>");
  }
}

/**
 * Write a link pointing towards the director details page
 *
 * @param director		the director
 * @param listElement	        if true, write the link as a list element
 */
function directorToLink($director, $listElement = FALSE) {
  $director_name = $director->getName();
  $director_name_xhtml = htmlspecialchars($director_name);
  $director_id = $director->getId();

  if ($listElement) {
    echo("<li><a href=\"directorDetails?director_id=$director_id\">$director_name_xhtml</a></li>");
  } else {
    echo("<a href=\"directorDetails?director_id=$director_id\">$director_name_xhtml</a>");
  }
}

/**
 * Write a link pointing towards the kind details page
 *
 * @param kind		the kind
 * @param listElement   if true, write the link as a list element
 */
function kindToLink($kind, $listElement = FALSE) {
  $kind_name = $kind->getName();
  $kind_name_xhtml = htmlspecialchars($kind_name);
  $kind_id = $kind->getId();

  if ($listElement) {
    echo("<li><a href=\"kindDetails?kind_id=$kind_id\">$kind_name_xhtml</a></li>");
  } else {
    echo("<a href=\"kindDetails?kind_id=$kind_id\">$kind_name_xhtml</a>");
  }
}

/**
 * Write a link pointing towards the year details page
 *
 * @param year		the year
 * @param listElement	if true, write the link as a list element
 */
function yearToLink($year, $listElement = FALSE) {

  if ($listElement) {
    echo("<li><a href=\"yearDetails?year=$year\">$year</a></li>");
  } else {
    echo("<a href=\"yearDetails?year=$year\">$year</a>");
  }
}

?>
