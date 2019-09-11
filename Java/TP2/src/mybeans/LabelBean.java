/*
 * #(@)LabelBean.java                ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package mybeans;

import java.beans.*;
import java.util.*;
import javax.swing.*;
import java.io.Serializable;
import java.awt.*;

/**
 * Cette classe est un écouteur d'ImageIterator. Elle réagit aux changements
 * d'image en affichant le nom de l'image, sa hauteur et sa largeur.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class LabelBean extends JLabel implements Serializable, ImageChangedListener {
    /** Le nom du fichier à afficher. */
    private String file;
    
    /** Le constructeur par défaut. */
    public LabelBean() { }
    
    /**
     * Cette méthode est invoquée lorsque l'image courante d'un ImageIterator a
     * changé.
     */
    public void imageChanged(ImageChangedEvent evt) {
        file = evt.getFileName();
        int h = evt.getImage().getHeight(this);
        int w = evt.getImage().getWidth(this);
        
        this.setText(file + "(" + h + "x" + w + ")");
    }
    
    /**
     * Méthode à usage interne, appelée lorsque les dimensions de l'image sont 
     * disponibles.
     */
    public boolean imageUpdate(Image img, int infoflags, int x, int y, int w, int h) {
        this.setText(file + "(" + h + "x" + w + ")");
        
        return true;
    }
}
