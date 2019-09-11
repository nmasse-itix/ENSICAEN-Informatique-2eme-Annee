/*
 * #(@)CinemaJava.java              ENSICAEN                       2006
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

package cineservlet;

import java.io.*;
import java.net.*;
import java.util.*;

import javax.servlet.*;
import javax.servlet.http.*;

import cinejava.*;

/**
 * This servlet allows the user to show the movies in which an actor played.
 *
 * @author Nicolas MASSE
 * @version 2006
 */
public class Cinema extends HttpServlet {
    public void init() throws ServletException {
            String dburl = getInitParameter("db-url");
            String dbdriver = getInitParameter("db-driver");
            
            if (dburl == null || dbdriver == null) {
                return;
            }
            
            try {
                Class.forName(dbdriver);
            } catch (Exception ignored) { }

            GestionBase.initConnection(dburl);
    }

    /** Processes requests for both HTTP <code>GET</code> and <code>POST</code> methods.
     * @param request servlet request
     * @param response servlet response
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Gestion cinematographique</title>");
        out.println("</head>");
        out.println("<body bgcolor=\"white\">");
        out.println("<h1>Gestion cinematographique</h1>");
        out.println("<form action=\"" + request.getContextPath() + request.getServletPath() + "\" method=\"GET\">");
        out.println("<input type=\"text\" name=\"acteur\">");
        out.println("<input type=\"submit\">");
        out.println("</form>");

        String acteur = request.getParameter("acteur");
        if (acteur != null && !acteur.equals("")) {
                List acteurs = Actor.getActors(acteur);
                if (acteurs.size() == 0) {
                        out.println("<h2>Acteur inconnu !</h2>");
                } else if (acteurs.size() == 1) {
                        out.println("<h2>Filmographie :</h2>");
                        List films = Movie.getMoviesWith((Actor) acteurs.get(0));
                        
                        out.println("<ul>");
                        Iterator it = films.iterator();
                        while (it.hasNext()) {
                            out.println("<li>" + it.next() + "</li>");
                        }
                        out.println("</ul>");
                } else {
                        out.println("<h2>Trop de resultats</h2>");
                }
        }

        out.println("</body>");
        out.println("</html>");
        
        out.close();
    }
    
    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /** Handles the HTTP <code>GET</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    }
    
    /** Handles the HTTP <code>POST</code> method.
     * @param request servlet request
     * @param response servlet response
     */
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException {
        processRequest(request, response);
    }
    
    /** Returns a short description of the servlet.
     */
    public String getServletInfo() {
        return "Database MMI";
    }
    // </editor-fold>
}
