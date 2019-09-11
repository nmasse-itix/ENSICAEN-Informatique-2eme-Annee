/*
 * #(@)Main.java              ENSICAEN                       2006
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
import javax.sql.*;
import javax.swing.*;

/**
 * Entry point of the application.
 *
 * @author Thomas LIMIN
 */
public class Main {
    
    /**
     * Entry point of the application. Starts a GUI.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        GestionBase.initConnection(System.getProperty("cinema.db-url"));
        JFrame jf = new CineJavaFrame();
        jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jf.pack();
        jf.setVisible(true);
    }
    
}
