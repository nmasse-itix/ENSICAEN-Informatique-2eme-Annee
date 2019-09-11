/*
 * #(@)Actor.java              ENSICAEN                       2006
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

package cinejava;

import java.sql.*;
import java.util.*;

/**
 * Represents an actor.
 *
 * @author Thomas LIMIN
 */
public class Actor {
    
    /**
     * Creates a new instance of Actor
     */
    public Actor(int actorId, String name) {
        this.setActorId(actorId);
        this.setActorName(name);
    }
    
    /**
     * Retrieve the actor with a name matching the given parameter. If more than
     * one actor may be returned, an error occur so null is returned
     *
     * @param actorNamePart     a part of the actor name
     * @return                  an actor or null
     */
    public static java.util.List<Actor> getActors(String actorName) {
        java.util.List<Actor> result = new ArrayList<Actor>(2); 
        PreparedStatement ppst = Actor.getStActorFromName();
        
        try {
            ppst.setString(1, "%" + actorName + "%");
            ResultSet rs = ppst.executeQuery();
            
            while (rs.next()) {
                int tmpId = rs.getInt("numc");
                String tmpName = rs.getString("identc");                
                result.add(new Actor(tmpId, tmpName));
            }
            
            rs.close();
            
        } catch (SQLException e) {
            e.printStackTrace(System.err);
        }
        
        return result;
    }
    
    
    public int getActorId() {
        return this.actorId;
    }
    
    public void setActorId(int actorId) {
        this.actorId = actorId;
    }
    
    public String getActorName() {
        return this.actorName;
    }
    
    public void setActorName(String actorName) {
        this.actorName = actorName;
    }
    
    
    /**
     * Return the instance (singloton) PreparedStatement that
     * managed the SQL query used to retrieve actor with a matching
     * name.
     *
     * @return the prepared statement
     */
    public static PreparedStatement getStActorFromName() {
        
        if (Actor.stActorFromName != null) {
            return Actor.stActorFromName;
        } else {
            try {
                Actor.stActorFromName = GestionBase.getConnection().prepareStatement(
                        "SELECT numc, identc FROM com WHERE upper(identc) LIKE upper(?)");
            } catch (SQLException e) {
                e.printStackTrace(System.err);
            }
        }
        
        return Actor.stActorFromName;
    }
    
    /**
     * Identification number of the actor
     */
    private int actorId;
    
    /**
     * Last and first name of the actor
     */
    private String actorName;
    
    /**
     * the statement needed to retrieve an actor from its name
     */
    private static PreparedStatement stActorFromName = null;
    
}