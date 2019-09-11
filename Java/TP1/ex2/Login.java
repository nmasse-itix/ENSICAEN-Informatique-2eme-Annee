/*
 * #(@)Login.java                  ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package ex2;

import java.io.*;

/**
 * Programme d'authentification qui lit sur l'entree standard un couple
 * login/mot de passe et qui l'authentifie en utilisant une methode native.
 * 
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
class Login {

	/* Chargement de la librarie partagee */
	static {
		System.loadLibrary("login");
	}
	
	/** La methode est implementee dans la librairie liblogin.so */
	native static boolean validate(String login, String passwd);
	
	/** Point d'entree du programme */
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader br = new BufferedReader(isr);
		String login = null;
		String passwd = null;
		
		/* Demande du login */
		System.out.print("Login: ");
		login = br.readLine();
		
		/* Demande du mot de passe */
		System.out.print("Passwd: ");
		passwd = br.readLine();

		System.out.println();
		
		/* Validation */
		if (validate(login, passwd)) {
			System.out.println("Welcome " + login + " !");
		} else {
			Thread.sleep(2000);
			System.out.println("Wrong login/passwd !");
		}
	}
}

