/*
 * #(@)ImageBean.java                ENSICAEN                     2005
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
import java.awt.*;
import java.awt.image.*;
import java.io.Serializable;
import java.util.*;

/**
 * Cette classe se conforme à la spécification JavaBean. C'est un afficheur
 * d'images. Elle génère des évènements ImageChangedEvent reçu par des objets
 * de type ImageChangedListener lorsque l'image à afficher change.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class ImageBean extends Canvas implements Serializable {
    /** Le nom de l'image à afficher, valeur implicite : null */
    public static final String PROP_IMAGE_FILENAME = "imageFileName";
    private String imageFileName;

    /** Le contenu de l'image */
    private Image img;
    
    /** Aide à la propagation d'évènements */
    private PropertyChangeSupport propertySupport;
    
    /** La liste de tous les écouteurs */
    private java.util.List<ImageChangedListener> listenerList;
    
    /** Construit un nouvel afficheur */
    public ImageBean() {
        this.propertySupport = new PropertyChangeSupport(this);
        this.listenerList = new ArrayList<ImageChangedListener>();
    }
    
    /** 
     * Getter pour le nom de fichier.
     */
    public String getImageFileName() {
        return this.imageFileName;
    }
    
    /**
     * Setter pour le nom de fichier.
     */
    public void setImageFileName(String value) {
        String oldValue = this.imageFileName;
        this.imageFileName = value;
        
        this.img = java.awt.Toolkit.getDefaultToolkit().getImage(this.imageFileName);
        
        this.repaint();
        
        this.propertySupport.firePropertyChange(PROP_IMAGE_FILENAME, oldValue, value);
        this.fireImageChangedEvent();
    }

    /**
     * Enregistre un nouvel écouteur de changement de propriété.
     */
    public void addPropertyChangeListener(PropertyChangeListener listener) {
        this.propertySupport.addPropertyChangeListener(listener);
    }
    
    /**
     * Enlève un écouteur de changement de propriété précédemment enregistré.
     */
    public void removePropertyChangeListener(PropertyChangeListener listener) {
        this.propertySupport.removePropertyChangeListener(listener);
    }
    
    /**
     * Enregistre un nouvel écouteur de changement d'image.
     */
    public void addImageChangedListener(ImageChangedListener ice) {
        this.listenerList.add(ice);
    }
    
    /**
     * Enlève un écouteur de changement d'image précédemment enregistré.
     */
    public void removeImageChangedListener(ImageChangedListener ice) {
        this.listenerList.remove(ice);
    }

    /**
     * Provoque l'émission d'évènements de changement d'image.
     */
    private void fireImageChangedEvent() {
        ImageChangedEvent evt = new ImageChangedEvent(this, this.imageFileName, this.img);
        
        ListIterator<ImageChangedListener> li = this.listenerList.listIterator();
        ImageChangedListener ice;
        
        while (li.hasNext()) {
            ice = li.next();
            ice.imageChanged(evt);
        }
    }
    
    /**
     * Affiche le composant à l'écran.
     */
    public void paint(Graphics g) {
        g.clearRect(0, 0, this.getWidth(), this.getHeight());
        
        if (img != null) {
            g.drawImage(img, 0, 0, this);
        }
    }
}
