/*
 * #(@)Movie.java              ENSICAEN                       2006
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
 * This class represents a movie.
 *
 * @author Thomas LIMIN
 */
public class Movie {
    
    /** Creates a new instance of Movie */
    public Movie(int movieId, String title, int kindId, int year, int directorId, String synopsis) {
        this.setMovieId(movieId);
        this.setTitle(title);
        this.setKindId(kindId);
        this.setYear(year);
        this.setDirectorId(directorId);
        this.setSynopsis(synopsis);
    }
    
    
    /**
     * Ask the database for a list of movies in which the actor appear.
     *
     * @param actorNamePart     an actor
     * @return                  a list of movies
     */
    public static java.util.List<Movie> getMoviesWith(Actor actor) {
        java.util.List<Movie> result = new ArrayList<Movie>(8);
        PreparedStatement ppst = Movie.getStMoviesWith();
        
        try {
            ppst.setInt(1, actor.getActorId());
            ResultSet rs = ppst.executeQuery();            
            
            while (rs.next()) {
                int tmpMovieId = rs.getInt("numf");
                String tmpTitle = rs.getString("titre");
                int tmpKindId = rs.getInt("numg");
                int tmpYear = rs.getInt("annee");
                int tmpDirectorId = rs.getInt("numr");
                String tmpResume = rs.getString("resume");
                
                result.add(new Movie(tmpMovieId, tmpTitle, tmpKindId, tmpYear, 
                        tmpDirectorId, tmpResume));
            }
            
            rs.close();
            
        } catch (SQLException e) {
            e.printStackTrace(System.err);
        }
        
        return result;
    }
    
     /**
      * Return the instance (singloton) PreparedStatement that
      * managed the SQL query used to retrieve movies with a
      * provide actor.
      *
      * @return the prepared statement
      */
    private static PreparedStatement getStMoviesWith() {
        if (Movie.stMoviesWith == null) {
            try {
                Movie.stMoviesWith = 
                        GestionBase.getConnection().prepareStatement(
                        "SELECT numf, titre, numg, annee, numr, resume " +
                        "FROM film NATURAL JOIN role " +
                        "WHERE numc = ?");
            } catch (SQLException e) {
                e.printStackTrace(System.err);
            }
        }
        
        return Movie.stMoviesWith;
    }
    
    public int getMovieId() {
        return movieId;
    }
    
    public void setMovieId(int movieId) {
        this.movieId = movieId;
    }
    
    public String getTitle() {
        return title;
    }
    
    public void setTitle(String title) {
        this.title = title;
    }
    
    public int getKindId() {
        return kindId;
    }
    
    public void setKindId(int kindId) {
        this.kindId = kindId;
    }
    
    public int getYear() {
        return year;
    }
    
    public void setYear(int year) {
        this.year = year;
    }
    
    public int getDirectorId() {
        return directorId;
    }
    
    public void setDirectorId(int directorId) {
        this.directorId = directorId;
    }
    
    public String getSynopsis() {
        return synopsis;
    }
    
    public void setSynopsis(String synopsis) {
        this.synopsis = synopsis;
    }
    
    /**
     * Returns the string representation of this movie.
     *
     * @return  the string representation of this movie
     */
    public String toString() {
        return this.getTitle() + ", " + this.getYear();
    }
    
    /**
     * The identifier of the movie
     */
    private int movieId;
    
    /**
     * The title of the movie
     */
    private String title;
    
    /**
     * The identifier of this movie's kind
     */
    private int kindId;
    
    /**
     * The release year of the movie
     */
    private int year;
    
    /**
     * The movie's diretctor's identifier
     */
    private int directorId;
    
    /**
     * The synopsis of the movie
     */
    private String synopsis;
    
    /**
     * The SQL query that retrieves the movies with
     * a provide actor
     */
    private static PreparedStatement stMoviesWith;
}
