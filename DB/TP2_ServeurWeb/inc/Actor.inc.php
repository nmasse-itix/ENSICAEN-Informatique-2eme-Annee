<?php
/** 
 * #(@)Actor.inc.php            ENSICAEN                          2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Represents an actor. 
 *
 * @author 	MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author 	LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * @version	1.0
 * @access	public
 */
class Actor {
	/**
	 * The id of this actor in the database.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $id;

	/**
	 * The identity of this actor in the database.
	 *
	 * @var		string
	 * @access	private
	 */
	var $name;

	/**
	 * The list of movies in which this actor appears
	 */
	var $movies;
	
	/**
	 * Constructs an actor using his data.
	 *
	 * @param integer	$id	the id of the actor.
	 * @param string	$name	the name of the actor.
	 * @access private
	 */
	function Actor($id, $name) {
		$this->id = $id;
		$this->name = $name;
		$this->movies = NULL;
	}
	
	/**
	 * Constructs an actor using its id in the database, if it doesn't exist
	 * it is inserted and the given number is returned.
	 *
	 * @param string	$name	the name of the actor
	 * @access public
	 * @static
	 * @returns 			a new actor.
	 */
	function newActor($name) {
		$id = 0;
		
		// Doubles the quotes
		$name_esc = pg_escape_string($name);
		
		$query = "SELECT numc FROM com WHERE identc = '$name_esc'";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the director exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$id = $row[0];
		} else if ($num == 0) {
			// No, insert it
			$id = getNextKey('com');
			$insert = "INSERT INTO com (numc, identc) VALUES (" . $id . ", '$name_esc')";
	
			if (pg_query($GLOBALS[PG_CONNECTION], $insert) === FALSE) {
				die("Unable to insert new actor.");
			}

			trigger_error("New actor inserted", E_USER_NOTICE);
		} else {
			die("'$query' returned $num lines.");
		}
		
		// creates the object
		$act = new Actor($id, $name);
		
		return $act;
	}
	

	/**
	 * Constructs an actor using his id in the database, if it doesn't exist
	 * NULL is returned
	 *
	 * @param string	$id	the id of the actor
	 * @access public
	 * @static
	 * @returns 			a new actor or NULL.
	 */
	function getActorById($id) {
				
		$query = "SELECT identc FROM com WHERE numc = $id";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the actor exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$name = $row[0];
			// creates the object
			$actor = new Actor($id, $name);

		} else if ($num == 0) {
			// No, return NULL
			$actor = NULL;
		}
		
		return $actor;
	}

	/**
	 * Returns the list of movies in which this actor appears.
	 * This method is a lazy initialization of the movies field
	 *
	 * @return		movies list
	 */
	function getMoviesList() {
	  if ($this->movies == NULL) {
	    $this->movies = Movie::getMoviesWithActor($this->id);
	  }
		
	  return $this->movies;
	}


	/**
	 * Returns the list of all the actors in the database and the number
	 * of movies associated.
	 *
	 * @return array	an array of two columns, the actor and 
	 * 			the number of movies.
	 * @static
	 */
	function getActors() {
		$query = "SELECT numc, identc, count(numf) AS num 
			  FROM com NATURAL JOIN role
			  GROUP BY numc, identc
			  ORDER BY identc";
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Can't list actors.");
		}

		$arr = Array();
		
		while (($row = pg_fetch_row($res)) !== FALSE) {
			$arr[] = Array(new Actor($row[0], $row[1]), $row[2]);
		}

		return $arr;
	}
	

	/**
	 * Register the role of this actor in the film.
	 * 
	 * @param Movie		$movie 	the movie the actor played in.
	 * @access public
	 */
	function playIn($movie) {
		$query = "INSERT INTO role (numc, numf) VALUES (" . 
				$this->getId() . ", " . 
				$movie->getId() . ")";

		if (pg_query($GLOBALS[PG_CONNECTION], $query) === FALSE) {
			die("Unable to insert new role.");
		}
		
		trigger_error("New role inserted: " . $this->toString() . 
				" + " . $movie->toString(), E_USER_NOTICE);
	}

	/**
	 * Returns the ID of this actor.
	 *
	 * @return integer	the id of this actor.
	 * @access public
	 */
	function getId() {
		return $this->id;
	}

	/**
	 * Returns the identity of this actor.
	 *
	 * @return string	the identity of this actor.
	 * @access public
	 */
	function getName() {
		return $this->name;
	}

	/**
	 * Returns the string representation of this actor.
	 *
	 * @return string	the string representation of this actor.
	 * @access public
	 */
	function toString() {
		return "Actor(" . $this->getId() . ", " . $this->getName() . ")";
	}
}
?>
