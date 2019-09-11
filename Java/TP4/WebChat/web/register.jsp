<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
   
   <jsp:useBean id="javchat" scope="request" class="WebChat.JAVChat" />
       
       <%! String message="", nickname, password, cpassword, firstname, lastname, email, picture_url; %>
       
       <%
       
       nickname = request.getParameter("nickname");
       password = request.getParameter("password");
       cpassword = request.getParameter("cpassword");
       firstname = request.getParameter("firstname");
       
       if (nickname == null) {
           nickname = "";
       }
       if (firstname == null) {
           firstname = "";
       }
       String lastname = request.getParameter("lastname");
       if (lastname == null) {
           lastname = "";
       }
       String email = request.getParameter("email");
       if (email == null) {
           email = "";
       }
       String picture_url = request.getParameter("picture_url");
       if (picture_url == null) {
           picture_url = "";
       }
       if (!nickname.equals("")) {
           
           if (password.equals(cpassword)) {
               if (!javchat.checkExists(nickname)) {
                   if (javchat.insertUser(nickname, password, firstname, lastname, email, picture_url)) {
                       message = "<p> User correctly registered </p>";
                   } else {
                       message = "Error... no more explanations sorry...";
                   }
               } else {
                   message = "<p> User already exists, please change your nickname</p>";
               }
           } else {
               message = "<p>Please retype your password, they does'nt match";
           }
       } else {
           nickname = "";
       }

       %>
   
   
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>JAVChat user registration</title>
    </head>
    <body>

        <h1>JAVChat USER REGISTRATION</h1>
        <%= message %>
        <fieldset>
            <form action="register.jsp" method="post">
                <p>Nickname*: <input type="text" name="nickname" value="<%=nickname%>" ></p>
                <p>First Name*: <input type="text" name="firstname" value="<%=firstname%>"></p>
                <p>Last Name*: <input type="text" name="lastname" value="<%=lastname%>"></p>
                <p>Password*: <input type="password" name="password"></p>
                <p>Confirm Password*: <input type="password" name="cpassword"></p>
                <p>E-Mail*: <input type="text" name="email" value="<%=email%>"></p>
                <p>URL of your picture: <input type="text" name="picture_url" value="<%=picture_url%>"></p>
                <p><input type="submit" value="Submit"><input type="reset" value="Reset"></p>
            </form>
        </fieldset>

    
    </body>
</html>
