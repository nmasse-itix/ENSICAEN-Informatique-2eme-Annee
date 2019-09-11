/*
 * #(@)ImageFileFilter.java                ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */


package mybeans;

import java.io.*;

/**
 * Filtre les fichiers d'un répertoire, afin de ne laisser passer que les
 * fichiers image (*.png, *.jpg, *.gif).
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class ImageFileFilter implements FilenameFilter {
    
    /** Constructeur implicite */
    public ImageFileFilter() {
    }
    
    /** @see FileNameFilter */
    public boolean accept(File dir, String name) {
        return name.endsWith(".png") || name.endsWith(".jpg") || name.endsWith(".gif");
    }
}
