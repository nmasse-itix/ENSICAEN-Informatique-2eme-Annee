/*
 * #(@)ImageChangedEvent.java             ENSICAEN                  2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package mybeans;

import java.util.*;
import java.awt.*;

/**
 * Représente un changement d'images dans la classe ImageIterator.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class ImageChangedEvent extends EventObject {
    /** Le nom du nouveau fichier image */
    private String fileName;
    
    /** Le contenu de la nouvelle image */
    private Image image;
    
    /** Construit un nouvel évènement. */
    public ImageChangedEvent(Object source, String fileName, Image img) {
        super(source);
        
        this.fileName = fileName;
        this.image = img;
    }
    
    /** Getter pour le nom de fichier */
    public String getFileName() {
        return fileName;
    }
    
    /** Getter pour le contenu de l'image */
    public Image getImage() {
        return image;
    }
}
