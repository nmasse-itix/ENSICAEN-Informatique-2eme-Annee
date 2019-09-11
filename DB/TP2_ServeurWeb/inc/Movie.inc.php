<?php
/** 
 * #(@)Movie.inc.php            ENSICAEN                          2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Represents a movie.
 *
 * @author 	MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author 	LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * @version	1.0
 * @access	public
 */
class Movie {
	/**
	 * The id of this movie in the database.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $id;

	/**
	 * The title of this movie in the database.
	 *
	 * @var		string
	 * @access	private
	 */
	var $title;
	
	/**
	 * The id of the kind related to this movie.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $kind_id;

	/**
	 * On screen date.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $year;

	/**
	 * The id of the director related to this movie.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $dir_id;

	/**
	 * The text preview.
	 *
	 * @var		string
	 * @access	private
	 */
	var $text_preview;

	/**
	 * The list of actors who appears in this movie
	 */
	var $actors;
	
	/**
	 * Insert a new movie in the database.
	 *
	 * @param string	$title	the title of the movie.
	 * @param Kind		$kind	the kind of the movie.
	 * @param integer	$year	the year of the movie.
	 * @param Director	$dir	the director of the movie.
	 * @param string	$tp	the text preview of the movie.
	 * @param Array		$actors	the list of the actors of the movie.
	 * @return Movie	the new movie.
	 * @access public
	 * @static
	 */
	function newMovie($title, $kind, $year, $dir, $tp, $actors) {
		// Doubles the quotes
		$title_esc = pg_escape_string($title);
		$tp_esc = pg_escape_string($tp);
		
		// Insertion of the movie in the database
		$id = getNextKey('film');
		$insert = "INSERT INTO film 
				(numf, titre, numg, annee, numr, resume) 
				VALUES (" . 
					$id . ", " .
					"'$title_esc', " .
					$kind->getId() . ', ' .
					"$year, " .
					$dir->getId() . ", " .
					"'$tp_esc')";
	
		if (pg_query($GLOBALS[PG_CONNECTION], $insert) === FALSE) {
			die("Unable to insert new movie.");
		}

		// Constructs the newly added movie.
		$newMovie = new Movie($id, $title, $kind->getId(), $year, $dir->getId(), $tp);
		
		// Quick notice for debug
		trigger_error("New movie inserted: " . $newMovie->toString(), E_USER_NOTICE);
		
		// Inserts the roles
		foreach($actors as $actor) {
			$actor->playIn($newMovie);
		}
		
		return $newMovie;
	}

	/**
	 * Constructs a movie from its data.
	 *
	 * @param integer	$id		the identifier of the movie.
	 * @param string	$title		the title of the movie.
	 * @param integer	$kind_id	the kind identifier of the movie.
	 * @param integer	$year		the year of the movie.
	 * @param integer	$dir_id		the director of the movie.
	 * @param string	$tp		the text preview of the movie.
	 * @access private
	 */
	function Movie($id, $title, $kind_id, $year, $dir_id, $tp) {
		$this->id = $id;
		$this->title = $title;
		$this->kind_id = $kind_id;
		$this->year = $year;
		$this->dir_id = $dir_id;
		$this->text_preview = $tp;
		$this->actors = NULL;
	}


	/**
	 * Returns the movie having the wanted identifier.
	 * 
	 * @param Director	$dir	the wanted identifier.
	 * @return 		the wanted movie
	 * @access public
	 * @static
	 */
	function getMovieById($movie_id) {
		$query = "SELECT numf, titre, numg, annee, numr, resume 
			  FROM film WHERE numf = " . $movie_id;
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}

		// Does the movie exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$name = $row[0];
			// creates the object
			$movie = new Movie($row[0], $row[1], $row[2], $row[3], $row[4], $row[5]);
		} else if ($num == 0) {
			// No, return NULL
			$movie = NULL;
		}
		
		return $movie;
	}

	/**
	 * Returns the movies having the wanted relase date.
	 * 
	 * @param year.		th ewanted year
	 * @return array	an array of movies.
	 * @access public
	 * @static
	 */
	function getMoviesOfYear($year) {
		$arr = array();

		$query = "SELECT numf, titre, numg, annee, numr, resume 
			  FROM film WHERE annee = $year  ORDER BY titre ASC";
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
			$arr[] = new Movie($row[0], $row[1], $row[2], $row[3],
					   $row[4], $row[5]);
		}
		
		return $arr;
	}

	/**
	 * Returns the movies having the wanted kind identifier.
	 * 
	 * @param kind_id	the wanted kind identifier
	 * @param sort_type	how to sort: 0 => ASC title, 1 => DSC year
	 * @return array	an array of movies.
	 * @access public
	 * @static
	 */
	function getMoviesOfKind($kind_id, $sort_type = 0) {
		$arr = array();

		$query = "SELECT numf, titre, numg, annee, numr, resume 
			  FROM film WHERE numg = $kind_id ORDER BY ";

		
		switch ($sort_type) {
		    case 1:
		      $query = $query . "annee DESC;";
		      break;
		    default:
		      $query = $query . "titre ASC;";
		      break;
		}
		
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
			$arr[] = new Movie($row[0], $row[1], $row[2], $row[3],
					   $row[4], $row[5]);
		}
		
		return $arr;
	}

	/**
	 * Returns the movies having the wanted director.
	 * 
         * @param director_id		the director identifier
	 * @return array		an array of movies.
	 * @access public
	 * @static
	 */
	function getMoviesOfDirector($director_id) {
		$arr = array();

		$query = "SELECT numf, titre, numg, annee, numr, resume 
			  FROM film WHERE numr = $director_id ORDER BY titre ASC";
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
			$arr[] = new Movie($row[0], $row[1], $row[2], $row[3],
					   $row[4], $row[5]);
		}
		
		return $arr;
	}

	/**
	 * Returns the movies in which the wanted actor play.
	 * 
	 * @param  actor_id		the wanted actor identifier
	 * @return array		an array of movies.
	 * @access public
	 * @static
	 */
	function getMoviesWithActor($actor_id) {
		$arr = array();

		$query = "SELECT f.numf, f.titre, f.numg, f.annee, f.numr, f.resume 
			  FROM film f INNER JOIN role r ON f.numf = r.numf WHERE numc = $actor_id ORDER BY titre ASC"; 
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
			$arr[] = new Movie($row[0], $row[1], $row[2], $row[3],
					   $row[4], $row[5]);
		}
		
		return $arr;
	}

	/**
	 * Returns the movies with title matching the given parameter
	 * 
	 * @param  title_part		a search criteria based on a part of the title
	 * @return array		an array of movies.
	 * @access public
	 * @static
	 */
	function getMoviesWithTitleMatching($title_part) {
		$arr = array();

		$query = "SELECT numf, titre, numg, annee, numr, resume 
			  FROM film WHERE upper(titre) LIKE upper('%" . pg_escape_string($title_part) . "%') ORDER BY titre ASC"; 
		

		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list movies.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
			$arr[] = new Movie($row[0], $row[1], $row[2], $row[3],
					   $row[4], $row[5]);
		}
		
		return $arr;
	}


	/**
	 * Returns the list of actors who appears in this movie
	 * This method is a lazy initialization of the actors field
	 *
	 * @return		actors list
	 */
	function getActorsList() {
	  if ($this->actors == NULL) {
		$this->actors = array();

		$query = "SELECT c.numc, c.identc 
			  FROM com c INNER JOIN  role r ON  c.numc = r.numc WHERE r.numf = $this->id ORDER BY c.identc ASC"; 
		

		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Unable to list actors.");
		}
		
		// fetch rows
		while (($row = pg_fetch_row($res)) !== FALSE) {
			// populate array
		  $this->actors[] = new Actor($row[0], $row[1]);
		}
	  }
		
	  return $this->actors;
	}

	/**
	 * Returns the ID of this movie.
	 *
	 * @return integer	the id of this movie.
	 * @access public
	 */
	function getId() {
		return $this->id;
	}

	/**
	 * Returns the title of the movie.
	 *
	 * @return string	the title of the movie.
	 * @access public
	 */
	function getTitle() {
		return $this->title;
	}

	/**
	 * Returns the identifier of the kind related to this movie.
	 *
	 * @return integer	the identifier of kind related to this movie.
	 * @access public
	 */
	function getKindId() {
		return $this->kind_id;
	}

	/**
	 * Returns the year of the movie.
	 *
	 * @return integer	the year of the movie.
	 * @access public
	 */
	function getYear() {
		return $this->year;
	}

	/**
	 * Returns the identifier of the director related to this movie.
	 * 
	 * @return integer	the id of the director related to this movie.
	 * @access public
	 */
	function getDirId() {
		return $this->dir_id;
	}

	/**
	 * Returns the text preview of this movie.
	 *
	 * @return integer	the text preview of this movie.
	 * @access public
	 */
	function getTextPreview() {
		return $this->text_preview;
	}
	
	/**
	 * Returns the string representation of this movie.
	 *
	 * @return string	the string representation of this movie.
	 * @access public
	 */
	function toString() {
		return "Movie(" . $this->getId() . ", " . 
		$this->getTitle() . ', ' .
		$this->getKindId() . ', ' .
		$this->getYear() . ', ' .
		$this->getDirId() . ')';
	}
}
?>
