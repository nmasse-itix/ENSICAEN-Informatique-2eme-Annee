/*
 * #(@)GestionBase.java              ENSICAEN                       2006
 *
 * @author MASSE Nicolas (2005-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe4-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */
package cinejava;


import java.sql.*;


/**
 * This class allows to connect to the database.
 *
 * @author Thomas LIMIN
 * @author Nicolas MASSE
 */
public class GestionBase {
    
    /**
     * Provide a login and password to the datase
     *
     * @param dbUrl     data to reach the database, url formed
     */
    public static void initConnection(String dbUrl) {
        if (GestionBase.con == null) {
            try {
                GestionBase.con = DriverManager.getConnection(dbUrl);
            } catch (SQLException e) {
                e.printStackTrace(System.err);
                throw new IllegalArgumentException(e);
            }
        }
    }
    
    /**
     * To retrieve the current connection
     *
     * @return  the current connection
     */
    public static Connection getConnection() {
        Connection ret;
        
        if (GestionBase.con == null) {
            throw new IllegalStateException("The database connection has been closed");
        } else {
            ret = GestionBase.con;
        }
        
        return ret;
    }
    
    /**
     * Close the current connection.
     */
    public static void closeConnection() {
        try {
            GestionBase.getConnection().close();
        } catch (SQLException e) {
            e.printStackTrace(System.err);
        }
        
        GestionBase.con = null;
    }
    
    
    /**
     * the link with the database
     */
    private static Connection con = null;
    
}
