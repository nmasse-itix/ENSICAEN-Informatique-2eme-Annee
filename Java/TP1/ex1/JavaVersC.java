/**
 * #(@)JavaVersC.java              ENSICAEN                       2005-02-27
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

package ex1;

/**
 * Exemple du cours: affichage d'une chaine de caractères
 */

public class JavaVersC {

    public static void main(String[] args) {
	new JavaVersC().bonjour();
    }
    
    public native void bonjour();
    
    static {
	try {
	    System.loadLibrary("JavaVersC");
	} catch (SecurityException e) {
	    System.err.println(e.getMessage());
	    System.exit(1);
	} catch (UnsatisfiedLinkError e) {
	    System.err.println(e.getMessage());
	    System.exit(1);
	} catch (NullPointerException e) {
	    System.err.println("Error, System.loadLibrary called with null libname");
	    System.exit(1);
	}
    }

}
 
