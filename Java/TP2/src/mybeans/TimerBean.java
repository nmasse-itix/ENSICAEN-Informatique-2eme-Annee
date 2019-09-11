/*
 * #(@)TimerBean.java                ENSICAEN                     2005
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
import java.io.Serializable;

/**
 * Cette classe se conforme à la spécification JavaBean. C'est un déclencheur
 * d'évènements, tous les "time" secondes l'objet "main" de type "Runnable" 
 * est exécuté si la propriété booléenne "diaporama" est vraie.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class TimerBean extends Object implements Serializable, Runnable {
    /** Génère les évènements si vrai, valeur implicite : faux */
    public static final String PROP_DIAPORAMA = "diaporama";
    private boolean diaporama;
    
    /** Délai en secondes entre chaque évènement, valeur implicite : 1s */
    public static final String PROP_TIME = "time";
    private int time;
    
    /** Code à executer, valeur implicite : null */
    public static final String PROP_MAIN = "main";
    private Runnable main;

    /** Aide à la propagation d'évènements */
    private PropertyChangeSupport propertySupport;
    
    /** Thread générateur d'évènements */
    private Thread thread;
    
    /**
     * Construit un nouveau TimerBean.
     */
    public TimerBean() {
        this.propertySupport = new PropertyChangeSupport(this);
        
        this.diaporama = false;
        this.time = 1;
        this.main = null;
        
        this.thread = new Thread(this);
        this.thread.start();
    }
    
    /**
     * Getter pour la propriété "diaporama".
     */
    public boolean isDiaporama() {
        return diaporama;
    }
    
    /**
     * Getter pour la propriété "time".
     */
    public int getTime() {
        return time;
    }

    /**
     * Getter pour la propriété "main".
     */
    public Runnable getMain() {
        return main;
    }
    
    /**
     * Setter pour la propriété "diaporama".
     */
    public synchronized void setDiaporama(boolean newVal) {
        boolean oldValue = this.diaporama;
        this.diaporama = newVal;
        
        this.propertySupport.firePropertyChange(PROP_DIAPORAMA, oldValue, newVal);
        
        this.notify();
    }

    /**
     * Setter pour la propriété "main".
     */
    public synchronized void setMain(Runnable newMain) {
        Runnable oldValue = this.main;
        this.main = newMain;
        
        this.propertySupport.firePropertyChange(PROP_MAIN, oldValue, newMain);
    }
    
    /**
     * Setter pour la propriété "time".
     */
    public synchronized void setTime(int newTime) {
        int oldValue = this.time;
        this.time = newTime;
        
        propertySupport.firePropertyChange(PROP_TIME, oldValue, newTime);
    }

    /**
     * Enregistre un nouvel écouteur d'évènements.
     */
    public synchronized void addPropertyChangeListener(PropertyChangeListener listener) {
        this.propertySupport.addPropertyChangeListener(listener);
    }
    
    /**
     * Enlève un écouteur d'évènements précédemment enregistré.
     */
    public synchronized void removePropertyChangeListener(PropertyChangeListener listener) {
        this.propertySupport.removePropertyChangeListener(listener);
    }

    /**
     * Cette méthode est à usage interne uniquement.
     */
    public void run() {
        while (true) {
            while (! isDiaporama()) {
                synchronized(this) {
                    try {
                        wait();
                    } catch (InterruptedException ignored) {}
                }
            }
            try {
                Thread.sleep(getTime() * 1000);
                if (main != null) {
                    main.run();
                }
            } catch (InterruptedException ignored) {}
        }
    }
    
}
