<?php
  /** 
   * #(@)util.inc.php                 ENSICAEN                       2005
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
   * Creates and fill the table "numero" with pairs of table name and
   * first identifier available.
   *
   */
function createTableNum() {
  if (!tableExists($GLOBALS[PG_CONNECTION], 'numero', PG_SCHEMA)) {
    $query = 'CREATE TABLE numero (
		 nom_table VARCHAR(255) PRIMARY KEY,
		 numero INTEGER NOT NULL DEFAULT 0);';
    
    $res = pg_query($GLOBALS[PG_CONNECTION], $query);
    if ($res === FALSE) {
      // filling of the table "numero"
      $liste_table = array("com" => "numc", "film" => "numf", "genre" => "numg", "realis" => "numr");
      foreach($liste_table as $key_lt => $value_lt) {
	$res2 = pg_query($con, "SELECT max($value_lt) + 1 FROM $key_lt;");
	$row = pg_fetch_row($res2);
	pg_query($GLOBALS[PG_CONNECTION], "INSERT INTO numero VALUES('$key_lt', $row[0]);");
      }
    } else {
      echo(pg_last_error($con));
    }
  }
}


/**
 * Tests if the given table name match an existant exists
 *
 * @param table		checked table
 * @param schema	the schema in wich is search the table
 * @return bool
 */
function tableExists($table, $schema) {	
  $query = "SELECT table_name 
	FROM information_schema.tables
        WHERE table_type = 'BASE TABLE'
        AND table_name = '$table'
        AND table_schema = '$schema';";

  $res = pg_query($GLOBALS[PG_CONNECTION], $query);
  $num = pg_num_rows($res);

  return $num > 0;
}


/**
 * Return the next availlable key for the given table then
 * increment the  numero table, so the next call will
 * return a different key (atomic transaction)
 *
 * @param table		the table you want a key for
 * @return
 */
function getNextKey($table) {

  // begin the transaction
  $query = "BEGIN;";
  pg_query($GLOBALS[PG_CONNECTION], $query);

  // retrieve the key and get a lock on the concerned row
  $query = "SELECT numero FROM " . PG_SCHEMA . ".numero WHERE nom_table = '$table' FOR UPDATE;";
  $res = pg_query($GLOBALS[PG_CONNECTION], $query);  
  if($row = pg_fetch_row($res)) {
    $key = $row[0];
  } else {
    echo(pg_last_error($GLOBALS[PG_CONNECTION]));
    // cancel the transaction
    $query = "ROLLBACK;";
    pg_query($GLOBALS[PG_CONNECTION], $query);
    return 0;
  }

  $new_key = $key + 1;

  // update the key
  $query = "UPDATE " . PG_SCHEMA . ".numero SET numero = $new_key WHERE nom_table = '$table';";
  pg_query($GLOBALS[PG_CONNECTION], $query);

  // end the transaction and released
  $query = "commit;";
  pg_query($GLOBALS[PG_CONNECTION], $query);

  return $key;
}


/**
 * This aim to import new movies entries from a text file (utf8)
 * The layout of the text file is as follow:
 * title | kind | date | director | text preview (| actors)*
 * 
 * @param fileName	the name of the file to import data from
 */
function importNewMovies($fileName) {
  // opening the file
  $filedes = fopen($fileName, 'r') 
  	or die("Unable to open file '$fileName'");
  
  // read each line of the file
  while (! feof($filedes)) {
    $buffer = fgets($filedes, 2048);

    // retrieve all tokens
    $data = explode('|', $buffer);
   
    // partial record ? skip !
    if (sizeof($data) < 5)
    	continue;
    
    // get actors
    $nb_actors = sizeof($data) - 5;
    $actors = array();

    for ($i = 0; $i < $nb_actors; $i++) {
      $actors[$i] = Actor::newActor($data[$i + 5]);
    }    

    $kind = Kind::newKind($data[1]);
    $director = Director::newDirector($data[3]);
    
    // Movie ($conection, $title, $kind, $annee, $director, $text_preview, actors_array)
    // Create a new Movie, object. If the movie doesn't exist in the database, it is inserted
    Movie::newMovie($data[0], $kind, $data[2], $director, $data[4], $actors);
    
  }

  // close the file
  fclose($filedes);
}

?>
