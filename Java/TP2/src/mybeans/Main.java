/*
 * #(@)Main.java                ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package mybeans;

import javax.swing.*;

/**
 * Point d'entrée du TP, permet de tester l'interface graphique.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public abstract class Main {
    public static void main(String[] args) {
        ImageDisplayer id = new ImageDisplayer();
        JFrame jf = new JFrame();
        jf.setContentPane(id);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jf.setSize(640, 480);
        jf.setVisible(true);
    }
    
}
