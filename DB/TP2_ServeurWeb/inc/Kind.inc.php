<?php
/** 
 * #(@)Kind.inc.php            ENSICAEN                          2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Represents a kind of movie. 
 *
 * @author 	MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author 	LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * @version	1.0
 * @access	public
 */
class Kind {
	/**
	 * The id of this kind in the database.
	 *
	 * @var		integer
	 * @access	private
	 */
	var $id;

	/**
	 * The name of this kind in the database.
	 *
	 * @var		string
	 * @access	private
	 */
	var $name;
	
	/**
	 * The movies of this kind
	 */
	var $movies;

	/**
	 * Constructs a kind using its data.
	 *
	 * @param integer	$id	the id of the kind.
	 * @param string	$name	the name of the kind.
	 * @access private
	 */
	function Kind($id, $name) {
		$this->id = $id;
		$this->name = $name;
		$this->movies = NULL;
	}
	
	/**
	 * Constructs a kind using his name in the database, if it doesn't exist
	 * it is inserted and the given number is returned.
	 *
	 * @param string	$name	the name of the kind.
	 * @access public
	 * @static
	 * @returns 			a new kind.
	 */
	function newKind($name) {
		$id = 0;
		
		// Doubles the quotes
		$name_esc = pg_escape_string($name);
		
		$query = "SELECT numg FROM genre WHERE nomg = '$name_esc'";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the kind exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$id = $row[0];
		} else if ($num == 0) {
			// No, insert it
			$id = getNextKey('genre');
			$insert = "INSERT INTO genre (numg, nomg) VALUES (" . $id . ", '$name_esc')";
	
			if (pg_query($GLOBALS[PG_CONNECTION], $insert) === FALSE) {
				die("Unable to insert new kind.");
			}

			trigger_error("New kind inserted", E_USER_NOTICE);
		} else {
			die("'$query' returned $num lines.");
		}
		
		// creates the object
		$kind = new Kind($id, $name);
		
		return $kind;
	}
	

	/**
	 * Constructs a kind using his id in the database, if it doesn't exist
	 * NULL is returned
	 *
	 * @param string	$id	the id of the kind.
	 * @access public
	 * @static
	 * @returns 			a new kind or NULL.
	 */
	function getKindById($id) {
				
		$query = "SELECT nomg FROM genre WHERE numg = $id";
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
	
		// Does the kind exist in the database ?
		$num = pg_num_rows($res);
		if ($num == 1) {
			// Yes
			$row = pg_fetch_row($res);
			$name = $row[0];
			// creates the object
			$kind = new Kind($id, $name);

		} else if ($num == 0) {
			// No, return NULL
			$kind = NULL;
		}
		
		return $kind;
	}


	/**
	 * Returns the list of movies of this kind
	 * This method is a lazy initialization of the movies field
	 *
	 * @param sort_type	how to sort: 0 => ASC title, 1 => DSC year
	 *
	 * @return		movies list
	 */
	function getMoviesList($sort_type = 0) {
	  if ($this->movies == NULL) {
	    $this->movies = Movie::getMoviesOfKind($this->id, $sort_type);
	  }
		
	  return $this->movies;
	}


	/**
	 * Returns the list of all the kinds in the database and the number
	 * of movies associated.
	 *
	 * @return array	an array, each element is a two columns array containing 
	 * 			the kind and the number of movies.
	 * @static
	 */
	function getKinds() {
		$query = "SELECT numg, nomg, count(numf) AS num 
			  FROM genre NATURAL JOIN film
			  GROUP BY numg, nomg
			  ORDER BY nomg";
		
		$res = pg_query($GLOBALS[PG_CONNECTION], $query);
		if ($res === FALSE) {
			die("Can't list kinds.");
		}

		$arr = Array();
		
		while (($row = pg_fetch_row($res)) !== FALSE) {
			$arr[] = Array(new Kind($row[0], $row[1]), $row[2]);
		}

		return $arr;
	}
	
	/**
	 * Returns the ID of this kind.
	 *
	 * @return integer	the id of this kind.
	 * @access public
	 */
	function getId() {
		return $this->id;
	}

	/**
	 * Returns the identity of this kind.
	 *
	 * @return string	the identity of this kind.
	 * @access public
	 */
	function getName() {
		return $this->name;
	}

	/**
	 * Returns the string representation of this kind.
	 *
	 * @return string	the string representation of this kind.
	 * @access public
	 */
	function toString() {
		return "Kind(" . $this->getId() . ", " . $this->getName() . ")";
	}
}
?>