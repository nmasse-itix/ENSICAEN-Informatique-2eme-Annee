/*
 * #(@)BankClient.java                ENSICAEN                     2005
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

package Bank;

import BankManagement.*;

import java.io.*;
import java.util.*;
import org.omg.CosNaming.*;
import org.omg.CORBA.*;
 
/**
 * Le client qui permet d'accéder au serveur.
 *
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 * @version	0.0.1
 */
public class BankClient {
    public static void main(String args[]) {

	String host = "localhost";
	String port = "1050";

	if (args.length >= 1) {
	    port = args[0];
	}

	if (args.length >= 2) {
	    host = args[1];
	}

	displayHelp();

	try {
	    // create and initialize the ORB
 	    ORB orb = ORB.init(new String[] {"-ORBInitialPort", host, "-ORBInitialPort", port }, null);

            // get the root naming context
            org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
            NamingContext ncRef = NamingContextHelper.narrow(objRef);

            // resolve the Object Reference in Naming
            // make sure there are no spaces between ""
            NameComponent nc = new NameComponent("Bank", "");
            NameComponent path[] = {nc};
            Bank bankRef = BankHelper.narrow(ncRef.resolve(path));
 

	    int accNum = -1;
	    int sessionId = -1;
	    String user = null;
	    String pass = null;
	    Account accRef = null;

	    boolean quit = false;
	    
	    BufferedReader buff = new BufferedReader(new InputStreamReader(System.in));


	    while (!quit) {
		StringTokenizer stk = new StringTokenizer(buff.readLine(), " \t");

		try {

		    while (!quit && stk.hasMoreTokens()) {
			String token = stk.nextToken();


			if (token.equals("login")) {
			    System.out.print("[ LOGIN       ] (void)");
			    if (stk.hasMoreTokens()) {
				user = stk.nextToken();
				System.out.println(" : login = " + user);
			    } else {
				throw new Exception("Syntax error at '" + token + "'");
			    }
			} else if (token.equals("pass")) {
			    System.out.print("[ PASS        ] (void)");
			    if (stk.hasMoreTokens()) {
				pass = stk.nextToken();
				System.out.println(" : pass = " + pass);
			    } else {
				throw new Exception("Syntax error at '" + token + "'");
			    }

			} else if (token.equals("connect")) {
			    System.out.print("[ CONNECT     ] (login = " + user + ", pass = " + pass + ")");
			    sessionId = bankRef.connect(user, pass);
			    System.out.println(" : sessionId = " + sessionId);
			    if (sessionId == 0) {
				System.out.println("wrong login or password");
			    }
			} else if (token.equals("disconnect")) {
			    System.out.print("[ DISCONNECT  ] (sessionId = " + sessionId + ")");
			    bankRef.disconnect(sessionId);
			    sessionId = -1;
			    System.out.println(" : OK");
			} else if (token.equals("create")) {
			    accNum = bankRef.create(sessionId);
			    if (accNum == 0) {
				System.out.println("Please log-in before create account: login <user_login> pass <user_password> connect ");
			    } else {
				System.out.print("[ CREATE      ] (sessionId = " + sessionId + ")");
				System.out.println(" : accNum = " + accNum);
				System.out.println(" : OK");
			    }
			} else if (token.equals("getacc")) {
			    if (stk.hasMoreTokens()) {
				accNum = Integer.parseInt(stk.nextToken());
			    } else {
				throw new Exception("Syntax error at '" + token + "'");
			    }
			    System.out.print("[ GET ACCOUNT ] (sessionId = " + sessionId + ", accNum = " + accNum + ")");
			    accRef = bankRef.getAccount(accNum, sessionId);
			    System.out.println(" : OK");
			} else if (token.equals("deposit")) {
			    int m;
			    if (stk.hasMoreTokens()) {
				m = Integer.parseInt(stk.nextToken());
			    } else {
				throw new Exception("Syntax error at '" + token + "'");
			    }

			    System.out.print("[ DEPOSIT     ] (sessionId = " + sessionId + ", accNum = " + accNum + ", amount = " + m + ")");
			    accRef.deposit(m);
			    System.out.println(" : OK");
			} else if (token.equals("withdraw")) {
			    int m;
			    if (stk.hasMoreTokens()) {
				m = Integer.parseInt(stk.nextToken());
			    } else {
				throw new Exception("Syntax error at '" + token + "'");
			    }
			    System.out.print("[ WITHDRAW    ] (sessionId = " + sessionId + ", accNum = " + accNum + ", amount = " + m + ")");
			    accRef.withdraw(m);
			    System.out.println(" : OK");
			} else if (token.equals("balance")) {
			    System.out.print("[ BALANCE     ] (sessionId = " + sessionId + ", accNum = " + accNum + ")");
			    int b = accRef.balance();
			    System.out.println(" : balance = " + b);
			} else if (token.equals("quit")) {
			    quit = true;
			} else if (token.equals("del")) {
			    bankRef.del(accNum, sessionId);
			    System.out.println("[ DEL     ] (accNum = " + accNum + ")");
			    accNum = -1;
			    accRef = null;
			} else if (token.equals("help")) {
			    displayHelp();
			} else {
			    throw new Exception("Syntax error at '" + token + "'");
			}
		    } 

		} catch (Exception e) {
		    System.out.println("\nERROR : " + e) ;
		}

	    }
 
	} catch (Exception e) {
	    System.out.println("\n\n\nERROR : " + e) ;
	    e.printStackTrace(System.out);
	}

    }

    private static void displayHelp() {
	System.out.println("Syntax: command [argument]");
	System.out.println("login <user_login>");
	System.out.println("pass <user_password>");
	System.out.println("connect");
	System.out.println("create");
	System.out.println("getacc <account_number>");
	System.out.println("deposit <amount>");
	System.out.println("withdraw <amount>");
	System.out.println("balance");
	System.out.println("disconnect");
	System.out.println("del");
	System.out.println("help");
	System.out.println("quit");
	System.out.println("\nHint: login utest pass ptest is valid");
    }

}
