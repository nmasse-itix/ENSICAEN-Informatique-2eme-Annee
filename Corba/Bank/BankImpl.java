/*
 * #(@)BankImpl.java             ENSICAEN                       2006-04-04
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

package Bank;

import BankManagement.*;
import java.util.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;


/**
 * A Bank servant.
 */
class BankImpl extends BankPOA {

    /**
     * Bank servant constructor
     */
    public BankImpl() {
	//this.account = account;
	this.currentAccountNumber = 0;
	this.currentSessionID = 0;
	this.accounts = new HashMap<Integer, AccountImpl>(16);
	this.users = new HashMap<String, String>(16);
        this.sessions = new HashMap<Integer, String>(16);
	
	// Workaround : file storage not implemented (not very "corba related")
	// so users are created here and account related data are reinitialized
	// every BankServer relaunch. (interessant kind of periodic revolution ;-) )
	users.put("Thomas", "grouik");
	users.put("Nicolas", "pouet");
	users.put("utest", "ptest");
    }
    
    /**
     * Create a new account. If the session is incorrect
     * it returns 0;
     *
     * @param sessionID
     * @return the new account number
     */
    public int create (int sessionID) {
	int accNumber = 0;
	String username = sessions.get(sessionID);
	if (username != null) {
	    accNumber  = this.getNextAccountNumber();
	    AccountImpl acc = new AccountImpl(username);
	    
	    try {
		_default_POA().activate_object(acc);
		
	    } catch (org.omg.PortableServer.POAPackage.ServantAlreadyActive e) {
		System.err.println(e.getMessage());
	    } catch (org.omg.PortableServer.POAPackage.WrongPolicy e) {
		System.err.println(e.getMessage());
	    }
	    
	    this.accounts.put(accNumber, acc);
	    System.out.println("User " + username + " create a new account with number: " + accNumber + "(session id: " + sessionID + ")" );
	} else {
    	    System.out.println("Invalid session id: " + sessionID);
	}

	return accNumber;
    }


    /**
     * Provide an account stub.
     *
     * @param sessionID
     * @param acc_num
     * @return the account stub
     */
    public BankManagement.Account getAccount (int acc_num, int sessionID) throws BankManagement.no_such_account {
	String username = null;
	AccountImpl acc = null;
	Account aref = null;

	username = this.sessions.get(sessionID);

	if (username != null) {
	    acc = this.accounts.get(acc_num);
	} else {
      	    System.out.println("Invalid session id: " + sessionID);
	    throw new BankManagement.no_such_account();
	}

	if ((acc == null || !(acc.getUsername().equals(username)))) {
    	    System.out.println("No account " + acc_num + " for user " + username +" (session id: " + sessionID + ")");
	    throw new BankManagement.no_such_account();
	}

    	System.out.println("Provide account " + acc_num + " to " + username + " (session id: " + sessionID + ")");

	try {
	    //get object reference from the servant
	    //aref = AccountHelper.narrow(_default_POA().servant_to_reference(acc));



	    // aref = acc._this(); // doesn't work, WHY ?????
	    aref = AccountHelper.narrow(this._default_POA().servant_to_reference(acc));
	    
	} catch (Exception e){}

	return aref;
    }


    /**
     * Connect a user and give him a session id or 0 if login
     * or password are wrong.
     *
     * @param login
     * @param password
     * @return the session id
     */
    public int connect (String login, String password) {
	String storedPassword = this.users.get(login);
	int sessionID = 0;

	if ((storedPassword == null) || ! password.equals(storedPassword)) {
    	    System.out.println("Connection refused for user " + login);
	} else {
	    sessionID = this.getNextSessionID();
	    this.sessions.put(sessionID, login);
	    System.out.println("User " + login + " connected (session id: " + sessionID + ")");
	}

	return sessionID;
    }

    /**
     * Discard a session id so the user have to log-in
     * again to send commands.
     *
     * @param sessionID
     */
    public void disconnect (int sessionID) {
	String login = null;
	login = this.sessions.remove(sessionID);

	if (login != null) {
	    System.out.println("User " + login + " is now disconnected (previously connected with session id: " + sessionID + ")");
	} else {
    	    System.out.println("Error disconnecting session: session " + sessionID + " unknown");
	}
    }


    /**
     * Destroy an account. But where is the remaining cash deposited??
     *
     * @param acc_num
     * @param sessionID
     */
    public void del (int acc_num, int sessionID) {
	String username = null;
	username = this.sessions.get(sessionID);

	if (username != null) {
	    AccountImpl acc = accounts.get(acc_num);
	    if (acc.getUsername().equals(username)) {
		this.accounts.remove(sessionID);
	    }
	}
    }
    
    private int getNextAccountNumber() {
	return ++ this.currentAccountNumber;
    }

    private int getNextSessionID() {
	return ++ this.currentSessionID;
    }

    private Account account;
    private int currentAccountNumber;
    private int currentSessionID;
    private Map<Integer, AccountImpl> accounts;
    private Map<String, String> users;
    private Map<Integer, String> sessions;

}