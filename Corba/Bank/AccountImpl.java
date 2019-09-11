/*
 * #(@)AccountImpl.java                ENSICAEN                     2005
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

import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.*;

/**
 * Un compte bancaire concret: le servant
 */
class AccountImpl extends AccountPOA {

    /**
     * Le solde du compte.
     */
    private int balance = 0;

    /**
     * Le possesseur du compte.
     */
    private String username;

    /**
     * La liste des operations.
     */
    private List<String> opList;


    /**
     * Construit un nouveau compte bancaire.
     */
    public AccountImpl(String username) {
	setUsername(username);
	opList = new ArrayList<String>();
    }

    private void setUsername(String user) {
	this.username = user;
    }

    public String getUsername() {
	return this.username;
    }

    /**
     * Retourne le solde du compte.
     */
    public int balance() {
	return balance;
    }

    /**
     * Effectue un retrait.
     */
    public void withdraw(int amount) {
	balance -= amount;
	opList.add("withdraw[amount = " + amount + "]");
    }

    /**
     * Effectue un retrait.
     */
    public void deposit(int amount) {
	balance += amount;
	opList.add("deposit[amount = " + amount + "]");
    }
  
    public String operations() {
  	StringBuffer sb = new StringBuffer();
	
	Iterator it = opList.iterator();
	while (it.hasNext()) {
	    sb.append(it.next());
	    sb.append(Character.LINE_SEPARATOR);
	}

	return sb.toString();
    }
  
}

