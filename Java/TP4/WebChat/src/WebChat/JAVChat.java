/*
 * JAVChat.java
 *
 * Created on 11 janvier 2006, 17:07
 */

package WebChat;

import java.beans.*;
import java.util.*;
import java.io.Serializable;
import java.sql.*;
import javax.mail.*;
import javax.mail.internet.*;
import javax.activation.*;


/**
 * This beans handle user connection, registration and mail sending
 * for javchat connection system
 *
 * @author limint
 */
public class JAVChat extends Object implements Serializable {
    
    /**
     * Constructor
     */
    public JAVChat() {
        if (JAVChat.con == null) {
            try {
                Class.forName("org.postgresql.Driver");
            } catch (ClassNotFoundException e) {
                System.err.println(e);
            }
            JAVChat.initConnection("jdbc:postgresql://localhost/javchat?user=limint&password=vilest");
        }
    }
    
    /**
     * the user's nickname
     */
    private String nickname;
    
    /**
     * The user's password
     */
    private String password;
    
    /**
     * The user's first name
     */
    private String firstName;
    
    
    /**
     * The user's last name
     */
    private String lastName;
    
    /**
     * The user's email
     */
    private String email;
    
    /**
     * The user's picture's url
     */
    private String pictureURL;
    
    /**
     * Use provided login and password to conect the chat user
     *
     * @return      true if the user with given nickname and password
     *              is registered, false otherwise
     */
    public boolean checkAccount(String nickname, String password) {
        boolean result = false;
        this.nickname = null;
        this.password = null;
        this.firstName = null;
        this.lastName = null;
        this.email = null;
        this.pictureURL = null;
        PreparedStatement ppst = JAVChat.getStCheckAccount();
        
        try {
            ppst.setString(1, nickname);
            ResultSet rs = ppst.executeQuery();
            
            if (rs.next()) {
                String storedPwd = rs.getString("password");
                if (password.equals(storedPwd)) {
                    result = true;
                    this.nickname = nickname;
                    this.password = password;
                    this.firstName = rs.getString("first_name");
                    this.lastName = rs.getString("last_name");
                    this.email = rs.getString("email");
                    this.pictureURL = rs.getString("picture_url");
                }
                
            }
        } catch(SQLException e) {
            e.printStackTrace(System.err);
        }
        
        return result;
    }
    
    /**
     * Check if the specified user already exist in the database
     *
     * @param nickname      the nickname to check
     * @return              wether the nickname is already in the database
     */
    public static boolean checkExists(String nickname) {
        boolean result = false;
        PreparedStatement ppst = JAVChat.getStCheckAccount();
        
        try {
            ppst.setString(1, nickname);
            ResultSet rs = ppst.executeQuery();
            
            if (rs.next()) {
                result = true;
            }
        } catch(SQLException e) {
            e.printStackTrace(System.err);
        }
        
        return result;
    }
    
    /**
     * Insert a new javchat user in the database
     *
     * @param nickname
     * @param password
     * @param first name
     * @param lastname
     * @param email
     * @param picture_url
     * @return the insert state
     */
    public static boolean insertUser(String nickname, String password, String firstname,
            String lastname, String email, String picture_url) {
        boolean result = false;
        PreparedStatement st = JAVChat.getStInsertUser();
        try {
            st.setString(1, nickname);
            st.setString(2, password);
            st.setString(3, firstname);
            st.setString(4, lastname);
            st.setString(5, email);
            
            if (picture_url == null) {
                picture_url = "";
            }
            st.setString(6, picture_url);
            
            result = st.executeUpdate() == 1;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        
        return result;
    }
    
    
    
    /**
     * If the provided nickname exists in the database
     * and the e-mail address is fullfilled so this method
     * send the password via an email to the registered
     * email address
     *
     * @param nickname      the user's nickname
     */
    public static boolean sendPasswordTo(String nickname) {
        boolean result = false;
        PreparedStatement ppst = JAVChat.getStCheckAccount();
        
        try {
            ppst.setString(1, nickname);
            ResultSet rs = ppst.executeQuery();
            
            if (rs.next()) {
                String storedPwd = rs.getString("password");
                String storedEmail = rs.getString("email");
                
                Properties props = System.getProperties();
                props.put("mail.host", "mailhost.ecole.ensicaen.fr");
                props.put("mail.transport.protocol", "smtp");
                
                Session mailSession = Session.getDefaultInstance(props, null);
                
                Message mesg = new MimeMessage(mailSession);
                
                mesg.setFrom(new InternetAddress("limin@ecole.ensicaen.fr"));
                InternetAddress[] addresses = {new InternetAddress(storedEmail)};
                mesg.setRecipients(Message.RecipientType.TO, addresses);
                mesg.setSubject("Sending of javachat password");
                mesg.setSentDate(new java.util.Date());
                mesg.setText("Hello " + nickname +" this is your password to access javchat: " + storedPwd);
                Transport.send(mesg);
                result = true;     
            }
        } catch(SQLException e) {
            e.printStackTrace(System.err);
        } catch(MessagingException e) {
            e.printStackTrace(System.err);
        }
        
        return result;
    }
    
    /**
     * Build the SQL statement who retrieve info thanks to
     * a nickname
     */
    private static PreparedStatement getStCheckAccount() {
        if (JAVChat.stCheckAccount == null) {
            try {
                JAVChat.stCheckAccount =
                        JAVChat.getConnection().prepareStatement(
                        "SELECT nickname, password, first_name, last_name, email, picture_url " +
                        "FROM javchat_user " +
                        "WHERE nickname = ?");
            } catch (SQLException e) {
                e.printStackTrace(System.err);
            }
        }
        
        return JAVChat.stCheckAccount;
    }
    
    private static PreparedStatement stCheckAccount = null;
    
    /**
     * Build the SQL statement who inserts a new user's data;
     */
    private static PreparedStatement getStInsertUser() {
        if (JAVChat.stInsertUser == null) {
            try {
                JAVChat.stInsertUser =
                        JAVChat.getConnection().prepareStatement(
                        "INSERT INTO javchat_user " +
                        "(nickname, password, first_name, last_name, email, picture_url) " +
                        "VALUES (?, ?, ?, ?, ?, ?)");
            } catch (SQLException e) {
                e.printStackTrace(System.err);
            }
        }
        
        return JAVChat.stInsertUser;
    }
    
    private static PreparedStatement stInsertUser = null;
    
    
    /**
     * Provide a login and password to the database
     *
     * @param dbUrl     data to reach the database, url formed
     */
    public static void initConnection(String dbUrl) {
        if (JAVChat.con == null) {
            try {
                JAVChat.con = DriverManager.getConnection(dbUrl);
            } catch (SQLException e) {
                e.printStackTrace(System.err);
                throw new IllegalArgumentException(e);
            }
        }
    }
    
    /**
     * To retrieve the current connection
     *
     * @return  the current connection
     */
    public static Connection getConnection() {
        Connection ret;
        
        if (JAVChat.con == null) {
            throw new IllegalStateException("The database connection has been closed");
        } else {
            ret = JAVChat.con;
        }
        
        return ret;
    }
    
    /**
     * Close the current connection.
     */
    public static void closeConnection() {
        try {
            JAVChat.getConnection().close();
        } catch (SQLException e) {
            e.printStackTrace(System.err);
        }
        
        JAVChat.con = null;
    }
    
    /**
     * this Connection instance is a way to reach the database
     */
    private static Connection con;
    
    public String getNickname() {
        return nickname;
    }
    
    public String getPassword() {
        return password;
    }
    
    public String getFirstName() {
        return firstName;
    }
    
    public String getLastName() {
        return lastName;
    }
    
    public String getEmail() {
        return email;
    }
    
    public String getPictureURL() {
        return pictureURL;
    }
    
}
