<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Nombre à deviner</title>
    </head>
    <body>
    <jsp:useBean id="bean1" scope="session" class="nad.NombreADeviner"/>
        <%
        int guess = -1;
        String param = request.getParameter("guess");
        
        if (param != null) {
            try {
                guess = Integer.parseInt(param);
            } catch (NumberFormatException e) {
                guess = 0;
            }
        }
        bean1.setGuess(guess);
        %>
        <h1>Deviner un nombre</h1>
        <p>
            Bienvenue au jeu "Deviner un nombre"
        </p>
        <%
        if (bean1.getNumGuess() == 0) {
            
        }
        
        if (bean1.isSuccess()) {
            out.println("<p>Félicitations, vous l'avez trouvé en " + bean1.getNumGuess() + " essai(s)!!</p>");
            out.println("<p>Cliquer <a href=\"index.jsp\">ici</a> pour un nouvel essai</p>");
            
        } else {
            if (bean1.getNumGuess() == 0){
                out.println("<p>J'ai choisi un nombre entre 1 et 100.</p>");
            } else {
                
                out.println("<p>Non, désolé, essayez encore. Conseil: " + bean1.getHint() + "</p>");
                out.println("<p>Vous en êtes à " + bean1.getNumGuess() + " essai(s)</p>");
            }
            
            out.println("<form method=\"post\">" +
                    "<p>Choisissez un nombre:<input name=\"guess\"></p>" +
                    "<p><input type=\"submit\" name=\"submit\" value=\"Soumettre\">" +
                    "<input type=\"reset\" value=\"Réinitialiser\"></p></form>");
        }
        %>
    </body>
</html>
