<?php
/** 
 * #(@)Director.inc.php            ENSICAEN                          2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Represents a director.
 *
 * @author 	MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author 	LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * @version	1.0
 * @access	public
 */
class Director {
	/**
	 * The id of this director in the database.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $id;

	/**
	 * The identity of this director in the database.
	 *
	 * @var		string
	 * @access	private
	 */
	var $name;

	/**
	 * The movies the director shot
	 */
	var $movies;
	
	/**
	 * Constructs a director using his data.
	 *
	 * @param integer	$id	the id of the director.
	 * @param string	$name	the name of the director.
	 * @access private
	 */
	function Director($id, $name) {
		$this->id = $id;
		$this->name = $name;
		$this->movies = NULL;
	}
	
	/**
	 * Constructs a director using its id in the database, if it doesn't exist
	 * it is inserted and the given number is returned.
	 *
	 * @param string	$name	the name of the director
	 * @access public
	 * @static
	 * @returns 			a new director.
	 */
	function newDirector($name) {
		$id = 0;
		
		// Doubles the quotes
		$name_esc = pg_escape_string($name);
		
		$query = "SELECT numr FROM realis WHERE identr = '$name_esc'";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the director exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$id = $row[0];
		} else if ($num == 0) {
			// No, insert it
			$id = getNextKey('realis');
			$insert = "INSERT INTO realis (numr, identr) VALUES (" . $id . ", '$name_esc')";
	
			if (pg_query($GLOBALS[PG_CONNECTION], $insert) === FALSE) {
				die("Unable to insert new director.");
			}

			trigger_error("New director inserted", E_USER_NOTICE);
		} else {
			die("'$query' returned $num lines.");
		}
		
		// creates the object
		$dir = new Director($id, $name);
		
		return $dir;
	}

	/**
	 * Constructs a director using his id in the database, if it doesn't exist
	 * NULL is returned
	 *
	 * @param string	$id	the id of the director.
	 * @access public
	 * @static
	 * @returns 			a new director or NULL.
	 */
	function getDirectorById($id) {
				
		$query = "SELECT identr FROM realis WHERE numr = $id";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the director exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$name = $row[0];
			// creates the object
			$director = new Director($id, $name);

		} else if ($num == 0) {
			// No, return NULL
			$director = NULL;
		}
		
		return $director;
	}

	
	/**
	 * Returns the list of all the directors in the database and the number
	 * of movies associated.
	 *
	 * @return array	an array of two columns, the director and 
	 * 			the number of movies.
	 * @static
	 */
	function getDirectors() {
		$query = "SELECT numr, identr, count(numf) AS num 
			  FROM realis NATURAL JOIN film
			  GROUP BY numr, identr
			  ORDER BY identr";
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Can't list directors.");
		}

		$arr = Array();
		
		while (($row = pg_fetch_row($res)) !== FALSE) {
			$arr[] = Array(new Director($row[0], $row[1]), $row[2]);
		}

		return $arr;
	}
	
	/**
	 * Returns the ID of this director.
	 *
	 * @return integer	the id of this director.
	 * @access public
	 */
	function getId() {
		return $this->id;
	}

	/**
	 * Returns the identity of this director.
	 *
	 * @return string	the identity of this director.
	 * @access public
	 */
	function getName() {
		return $this->name;
	}

	/**
	 * Returns the string representation of this director.
	 *
	 * @return string	the string representation of this director.
	 * @access public
	 */
	function toString() {
		return "Director(" . $this->getId() . ", " . $this->getName() . ")";
	}

	/**
	 * Returns the list of movies shot by this director
	 * This method is a lazy initialization of the movies field
	 *
	 * @return		movies list
	 */
	function getMoviesList() {
	  if ($this->movies == NULL) {
	    $this->movies = Movie::getMoviesOfDirector($this->id);
	  }
		
	  return $this->movies;
	}

}
?>
