/**
 * #(@)ReadFile.java              ENSICAEN                       2005-02-20
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

package ex3;

/**
 * Ecriture d'une classe ReadFile capable de lire et d'afficher à l'écran
 * le contenu d'un fichier. La lecture du fichier proprement dite sera
 * effectuées par uen fonction native et retournera le fichier sous la forme
 * d'un tableau de bytes
 */

public class ReadFile {

    public static void main(String[] args) {
	if (args.length < 1) {
	    System.err.println("Usage : java ReadFile <filename>");
	} else {
	    byte[] tableau = new ReadFile().readFile(args[0]);
	    if (tableau != null) {
		System.out.println(new String(tableau));
	    }
	}
    }
    
    public native byte[] readFile(String filename);
    

    static {
	try {
	    System.loadLibrary("ReadFile");
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
 
