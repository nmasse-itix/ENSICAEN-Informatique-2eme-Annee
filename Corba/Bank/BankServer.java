/*
 * #(@)BankServer.java                ENSICAEN                     2005
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

import java.util.Properties;

/**
 * Make a bank servant availlable on the corba bus
 */
public class BankServer {

    /**
     * Lauch the bank server.
     */
    public static void main(String args[]) {

	String host = "localhost";
	String port = "1050";

	if (args.length >= 1) {
	    port = args[0];
	}

	if (args.length >= 2) {
	    host = args[1];
	}


	try{
	    // Step 1: Instantiate the ORB
	    ORB orb = ORB.init(new String[] {"-ORBInitialPort", host, "-ORBInitialPort", port }, null);

	    // Step 2: Instantiate the servant
	    BankImpl bankServ = new BankImpl();

	    // get reference to rootpoa & activate the POAManager
	    POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
	    rootpoa.the_POAManager().activate();
            
            rootpoa.activate_object(bankServ);


	    // Resolve RootNaming context and bind a name for the
            // servant.
            // NOTE: If the Server is persistent in nature then using Persistent
            // Name Service is a good choice. Even if ORBD is restarted the Name
            // Bindings will be intact. To use Persistent Name Service use
            // 'NameService' as the key for resolve_initial_references() when
            // ORBD is running.
            org.omg.CORBA.Object obj = orb.resolve_initial_references("NameService" );
            NamingContextExt rootContext = NamingContextExtHelper.narrow(obj);

            NameComponent[] nc = rootContext.to_name("Bank");
            rootContext.rebind(nc, rootpoa.servant_to_reference(bankServ));
	    System.out.println("Bank server ready and waiting ...");

	    // wait for invocations from clients
	    orb.run();
	} 
        
	catch (Exception e) {
	    System.err.println("ERROR: " + e);
	    e.printStackTrace(System.out);
	}
          
	System.out.println("Bank Server Exiting ...");
        
    }
}
 
