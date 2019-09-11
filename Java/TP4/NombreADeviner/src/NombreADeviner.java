/*
 * #(@)NombreADeviner.java             ENSICAEN                 2005-12-14
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 *
 * @author MASSE Nicolas (2004-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2004-Groupe4-MASSE) <thomas.limin@laposte.net>
 * @version 1.0
 */

package nad;

import java.beans.*;
import java.io.Serializable;
import java.util.Random;

/**
 * JavaBean choisissant un nombre aléatoire
 * et organisant sa decouverte par une succession
 * de proposition / indices
 */
public class NombreADeviner extends Object implements Serializable {
    
    /**
     * Constructeur sans arguments du JavaBean
     */
    public NombreADeviner() {
        this.rand = new Random();
        this.number = rand.nextInt(99) + 1;
        this.numGuess = 0;
        this.hint = null;
        this.success = false;
        this.propertySupport = new PropertyChangeSupport(this);
    }
    
    /**
     * Le générateur de nombles aléaoires
     */
    private Random rand;
    
    /**
     * le nombre à deviner
     */
    private int number;
    
    
    
    /**
     * Nombre saisi par l'utilisateur
     */
    private int guess;
    
    /**
     * Nombre d'essais
     */
    private int numGuess;
    
    /**
     * Information (nombre trop petit ou trop grand)
     */
    private String hint;
    
    /**
     * True si le nombre a été deviné, false sinon
     */
    private boolean success;
    
    private PropertyChangeSupport propertySupport;
    
    public void setGuess(int guess) {
        if (guess >= 1 && guess <= 100) {
            // guess est dans la plage de valeur
            this.guess = guess;
            this.numGuess++ ;
            
            if (guess > this.number) {
                this.hint = "Choisissez un nombre plus petit";
            } else if (guess < this.number) {
                this.hint = "Choisissez un nombre plus grand";
            } else {
                this.success = true;
                this.hint = null;
            }
        } else if (guess == -1) {
            // réinitialisation du bean NombreADeviner
            this.success = false;
            this.numGuess = 0;
            this.number = rand.nextInt(99) + 1;
            this.hint = null;
        }
        
    }
    
    public int getGuess() {
        return guess;
    }
    
    public int getNumber() {
        return number;
    }
    
    public int getNumGuess() {
        return numGuess;
    }
    
    public String getHint() {
        return hint;
    }
    
    public boolean isSuccess() {
        return success;
    }
    
    
    
    /*
    public static final String PROP_SAMPLE_PROPERTY = "sampleProperty";
     
    private String sampleProperty;
     
     
    public String getSampleProperty() {
        return sampleProperty;
    }
     
    public void setSampleProperty(String value) {
        String oldValue = sampleProperty;
        sampleProperty = value;
        propertySupport.firePropertyChange(PROP_SAMPLE_PROPERTY, oldValue, sampleProperty);
    }
     
     
    public void addPropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.addPropertyChangeListener(listener);
    }
     
    public void removePropertyChangeListener(PropertyChangeListener listener) {
        propertySupport.removePropertyChangeListener(listener);
    }
     */
    
    
}
