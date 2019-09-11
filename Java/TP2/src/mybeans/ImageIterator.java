/*
 * #(@)ImageIterator.java                ENSICAEN                     2005
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
import java.io.*;

/**
 * Cette classe se conforme à la spécification JavaBean. Il permet de parcourir
 * les images présentes dans un répertoire.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class ImageIterator extends Object implements Serializable {

    /** Le nom du répertoire à parcourir, valeur implicite : null */
    public static final String PROP_DIR_NAME = "dirName";
    private String dirName;

    /** Le nom de l'image courante, valeur implicite : première image du
     * répertoire, propriété en lecture seule. */
    public static final String PROP_CUR_IMAGE = "curImage";
    private String curImage;

    /** En fin de liste, retourne au début si vrai. Valeur implicite : faux */
    public static final String PROP_LOOP = "loop";
    private boolean loop;
    
    /** La liste des images contenues dans le répertoire */
    private File[] imageList;
    
    /** La position courante dans la liste des répertoires */
    private int imageIdx;
    
    /** Aide à la propagation d'évènements */
    private PropertyChangeSupport propertySupport;
    
    /**
     * Constructeur par défaut.
     */
    public ImageIterator() {
        this.propertySupport = new PropertyChangeSupport(this);
        this.loop = false;
        this.curImage = null;
        this.dirName = null;
        
        this.initialize();
    }

    /**
     * Getter pour la propriété "dirName".
     */
    public String getDirName() {
        return this.dirName;
    }
    
    /**
     * Getter pour la propriété "curImage".
     */
    public String getCurImage() {
        return this.curImage;
    }
    
    /**
     * Getter pour la propriété "loop".
     */
    public boolean isLoop() {
        return this.loop;
    }
    
    /** 
     * Setter pour la propriété "dirName".
     */
    public void setDirName(String value) {
        String oldValue = this.dirName;
        this.dirName = value;
        
        this.initialize();
        
        this.propertySupport.firePropertyChange(PROP_DIR_NAME, oldValue, value);
    }
    
    /**
     * Setter pour la propriété "curImage".
     */
    private void setCurImage(String value) {
        String oldValue = this.curImage;
        this.curImage = value;
        
        this.propertySupport.firePropertyChange(PROP_CUR_IMAGE, oldValue, value);
    }

    /**
     * Setter pour la propriété "loop".
     */
    public void setLoop(boolean val) {
        boolean oldValue = this.loop;
        this.loop = val;
        
        this.propertySupport.firePropertyChange(PROP_LOOP, oldValue, val);
    }
    
    /**
     * Place cet iterateur au début de la liste.
     */
    public void start() {
        if (imageList != null) {
            imageIdx = 0;
            setCurImage(imageList[imageIdx].getAbsolutePath());
        }
    }
    
    /**
     * Place cet itérateur à la fin de la liste.
     */
    public void end() {
        if (imageList != null) {
            imageIdx = imageList.length - 1;
            setCurImage(imageList[imageIdx].getAbsolutePath());
        }
    }
    
    /**
     * Place cet itérateur sur l'image précédente.
     */
    public void prev() {
        if (imageList != null) {
            if (imageIdx == 0 && isLoop()) {
                end();
            } else if (imageIdx != 0) {
                setCurImage(imageList[--imageIdx].getAbsolutePath());
            }
        }
    }
    
    /**
     * Place cet itérateur sur l'image suivante.
     */
    public void next() {
        if (imageList != null) {
            if (imageIdx == imageList.length - 1 && isLoop()) {
                start();
            } else if (imageIdx != imageList.length - 1) {
                setCurImage(imageList[++imageIdx].getAbsolutePath());
            }
        }
    }
    
    /**
     * Construit la liste des fichiers images du répertoire.
     */
    private void initialize() {
        if (dirName == null) {
            imageList = null;
            imageIdx = 0;
            setCurImage(null);
        } else {
            imageList = new File(dirName).listFiles(new ImageFileFilter());
            imageIdx = 0;
            if (imageList.length != 0) {
                curImage = null;
            } else {
                imageList = null;
            }
        }
    }
    
    /**
     * Enregistre un nouvel écouteur d'évènements.
     */
    public void addPropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.addPropertyChangeListener(listener);
    }
    
    /**
     * Enlève un écouteur d'évènements précédemment enregistré.
     */
    public void removePropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.removePropertyChangeListener(listener);
    }
}
