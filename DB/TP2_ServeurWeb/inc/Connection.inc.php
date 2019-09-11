<?php
/** 
 * #(@)Connection.inc.php            ENSICAEN                       2005
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
 * Connection to the database.
 */


define("PG_USER", "limint");
define("PG_SCHEMA", PG_USER);
define("PG_PASSWD", "vilest");
define("PG_DATABASE", "cinema");

// Useful alias, permit : $GLOBALS[PG_CONNECTION]
define("PG_CONNECTION", "PG_CONNECTION");

error_reporting(E_ALL);

$con = pg_connect('dbname=' . PG_DATABASE . ' user=' . PG_USER . ' password=' . PG_PASSWD);
if ($con === FALSE) {
	die("Unable to connect to the database.");
}

$GLOBALS[PG_CONNECTION] = $con;

