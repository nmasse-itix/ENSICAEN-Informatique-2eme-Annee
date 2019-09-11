<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Welcome on JAVChat</title>
    </head>
    <body>

        <h1>Welcome on JAVChat</h1>

        <fieldset>
            <form action="JAVirc.jsp" method="post">
                <p>Nickname: <input type="text" name="nickname"></p>
                <p>Password: <input type="text" name="password"></p>
                <p><input type="submit" value="Submit"><input type="reset" value="Reset"></p>
            </form>
        </fieldset>

        <p>Don't have an account: please <a href="register.jsp">register</a></p>

        <p>Forgot your password? <a href="ForgotPassword.jsp">retrieve it</a></p>

    </body>
</html>
