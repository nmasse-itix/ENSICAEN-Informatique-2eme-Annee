<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Did you forget your password ?</title>
    </head>
    <body>

    <h1>Did you forget your password ?</h1>
    
    <fieldset>
        <form method="POST" action="sendPassword.jsp">
            <p>Nickname:<input type="text" name="nickname"></p>
            <p><input type="submit" value="Recover password"></p>
        </form>
    </fieldset>
    </body>
</html>
