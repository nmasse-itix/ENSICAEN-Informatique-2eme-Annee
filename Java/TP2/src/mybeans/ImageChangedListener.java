/*
 * #(@)ImageChangedListener.java             ENSICAEN                  2005
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

/**
 * Spécifie la méthode appelée lors d'un changement d'image dans la classe
 * ImageIterator.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public interface ImageChangedListener extends EventListener {
    /**
     * Cette méthode est appelée lors d'un changement d'image dans
     * la classe ImageIterator.
     */
    public void imageChanged(ImageChangedEvent evt);
}
