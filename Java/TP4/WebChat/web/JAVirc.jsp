<%@page contentType="text/html"%>
<%@page pageEncoding="UTF-8"%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<!--
	                (c)   dp   04/02

	Fichier de connexion au serveur irc. Certains parametres
	doivent etre completes.
-->

<jsp:useBean id="javchat" scope="request" class="WebChat.JAVChat" />

    
<html>
<head>

    <%
        if (!javchat.checkAccount(
                request.getParameter("nickname"),
                request.getParameter("password"))) {
         // authentification failed, redirect to connect.jsp
            out.println("<meta http-equiv=\"refresh\" content=\"10; url=connect.jsp\" />");
            out.println("acces refusé: nickname: " + request.getParameter("nickname"));
        }
    %>

<script language=javascript>
function openWaitingWindow()
{
    	WaitingWindow = window.open ('http://www.javirc.com/JAVirc/wait.html','','width=350,height=100') ;
}

function closeWaitingWindow ()
{
	WaitingWindow.close () ;
}

openWaitingWindow () ;

</script>

</head>
<body>
<applet code="irc.class"
	name="JAVirc"
	codebase="http://www.javirc.com/JAVirc"
	archive="JAVirc.jar"
	width=100%
	height=80%
	mayscript>
<param name=cabbase value="JAVirc.cab">
<param name=server  value="irc.javirc.com">
<param name=port     value=6667>

<!--
	Parametre IRCName a completer avec une valeur constituee par le
	nom, prenom et email
-->

<param name=IRCName  value="<%= javchat.getLastName() + javchat.getFirstName() + javchat.getEmail() %>">
<param name=Nick value="<%= javchat.getNickname() %>">
<param name=Password value="<%= javchat.getPassword() %>">
    
<param name=FloatingWindows value="no">
<param name="Language" value="us">
<param name="SignedApplet" value="yes">
<param name="ExpertMode" value="yes">
<param name="AllowLineCommand" value="yes">
<param name=ChangeNick	value="no">
<param name=TryANotherNickWhenUsed value="yes">
<param name=useRandomNick value="no">
<param name=ListSize value="50">
<param name=EnableList value="yes">
<param name=IdentServer	value="yes">
<param name=UserName value="JAVchat">
<param name=FirstCommand value="MOTD;JOIN #JAVirc">
<param name=ChangeChannel value="yes">
<param name=ChatName	value="JAVirc">
<param name="CompanyHeader" value="^******************************^   Welcome to JAVirc Chat^******************************^">
<param name="ChannelReadOnly" value="no">
<param name="QueryReadOnly" value="no">
<param name="NoticePopupWindow" value="no">
<param name=InvisibleMode value="yes">
<param name=Silence value="yes">
<param name=RestrictWhois value="yes">
<param name=QuitMessage value="JAVirc http://www.javirc.com">
<param name="URLUserGuide" value="http://www.javirc.com/JAVirc/UserGuide/JAVircUserGuide.html">
<param name=UsePopupMenu value="yes">
<param name=Sound value="yes">
<param name=ChannelBackground	value="background.jpg">
<param name=QueryBackground	value="background.jpg">
<param name=ColorBackground value="f0f0d0">
<param name=ColorConnectButtonBackground value="f0f0d0">
<param name=ColorBackgroundApplet value="ffffff">
<param name=ChannelFamilyFont value="SansSerif">
<param name=ChannelStyleFont value="Plain">
<param name=ChannelSizeFont value="12">
<param name=QueryFamilyFont value="SansSerif">
<param name=QueryStyleFont value="Plain">
<param name=QuerySizeFont value="12">
<param name=ColorBackgroundDisplayChannel	  value="f0f0ff">
<param name=ColorBackgroundScrollbarChannel	  value="fff0ff">
<param name=ColorForegroundScrollbarChannel	  value="c0c0c0">
<param name=ColorBackgroundTextfieldChannel	  value="f0f0ff">
<param name=ColorForegroundTextfieldChannel	  value="000000">
<param name=ColorBackgroundListusersChannel	  value="f0f0ff">
<param name=ColorForegroundListusersChannel	  value="000000">
<param name=ColorBackgroundTotalusersChannel	  value="f0f0ff">
<param name=ColorForegroundTotalusersChannel	  value="000000">
<param name=ColorToolbarChannelBackground	  value="f0f0ff">
<param name=ColorChoiceChannelBackground	  value="f0f0ff">
<param name=ColorChoiceChannelForeground	  value="000000">
<param name=ColorButtonsChannelBackground	  value="f0f0ff">
<param name=ColorButtonsChannelForeground	  value="000000">
<param name=ColorChannelModeBackground		  value="f0f0ff">
<param name=ColorListBackground			  value="f0f0ff">
<param name=ColorListForeground			  value="000000">
<param name=ColorBackgroundDisplayQuery	  	value="c0c0ff">
<param name=ColorBackgroundScrollbarQuery 	value="c0c0c0">
<param name=ColorForegroundScrollbarQuery 	value="c0c0c0">
<param name=ColorBackgroundTextfieldQuery 	value="c0c0ff">
<param name=ColorForegroundTextfieldQuery 	value="000000">
<param name=ColorToolbarQueryBackground   	value="c0c0ff">
<param name=ColorChoiceQueryBackground	 	value="c0c0ff">
<param name=ColorChoiceQueryForeground	  	value="000000">
<param name=ColorButtonsQueryBackground		value="c0c0ff">
<param name=ColorButtonsQueryForeground	  	value="000000">
<param name=ColorPrivateMessage         value="000000">
<param name=ColorPublicMessage          value="000000">
<param name=ColorSystem                 value="000000">
<param name=ColorInvite                 value="006400">
<param name=ColorQuit                   value="ff0000">
<param name=ColorChannelMessage         value="006400">
<param name=ColorWallops                value="ff0000">
<param name=ColorNickChange             value="006400">
<param name=ColorTopicChange            value="006400">
<param name=ColorShowTopic		value="006400">
<param name=ColorCtcp                   value="ff0000">
<param name=ColorJoinChannel            value="006400">
<param name=ColorNotice                 value="ff0000">
<param name=ColorAction                 value="ff0fed">
<param name=ColorBroadcastMessage       value="ff0000">
<param name=Smiley	value="yes">
<param name=Smiley0 value="smile.gif|:)|yes">
<param name=Smiley1 value="smiled.gif|:d|yes">
<param name=Smiley2 value="smilep.gif|:p|yes">
<param name=Smiley3 value="wink2.gif|;)|yes">
<param name=Smiley4 value="sad.gif|:(|yes">
<param name=Smiley5 value="thumbu.gif|(y)|yes">
<param name=Smiley6 value="thumbd.gif|(n)|yes">
<param name=Smiley7 value="love.gif|(l)|yes">
<param name=Smiley8 value="unlove2.gif|(u)|yes">
<param name=Smiley9 value="camera.gif|(p)|no">
<param name=Smiley10 value="beer2.gif|(b)|no">
<param name=Smiley11 value="coctail.gif|(d)|no">
<param name=Smiley12 value="emphone.gif|(t)|no">
<param name=Smiley13 value="cat1.gif|(@)|no">
<param name=Smiley14 value="break.gif|(c)|no">
<param name=Smiley15 value="n_bulb.gif|(i)|no">
<param name=Smiley16 value="sleepz.gif|(s)|no">
<param name=Smiley17 value="hottie.gif|(h)|no">
<param name=Smiley18 value="star1.gif|(*)|no">
<param name=Smiley19 value="email.gif|(e)|no">
<param name=Smiley20 value="note.gif|(8)|no">
<param name=Smiley21 value="messenger.gif|(m)|no">
<param name=Smiley22 value="rose.gif|(f)|yes">
<param name=Smiley23 value="man.gif|(z)|no">
<param name=Smiley24 value="lips.gif|(k)|no">
<param name=Smiley25 value="gift.gif|(g)|no">
<param name=Smiley26 value="girl.gif|(x)|no">
<param name=MircColors	value="yes">
<param name=Toolbar Value="yes">
<param name=EnableURL   value="yes">
<param name=EnableNick   value="yes">
<param name=Channels value="#help;#aide;#france;#caen">
<param name=Actions value="applauds;hugs %;kisses % strongly">
<param name=ChannelOperator value="no">
<param name=ProfilURL value="http://testchat.javirc.com:8080/testchat/getProfil.jsp?nick=">
<param name=ColorTabbedPaneBackground		  value="f0f0ff">
<param name=ColorTabbedPaneUsed			  value="ff0000">
<param name=ColorTabbedText			  value="000000">
<param name=ColorTabbedActiveText		  value="0000ff">
<param name=ColorBackgroundTopic		  value="f0f0ff">
<param name=ColorForegroundTopic		  value="000000">
<param name=ColorBackgroundCloseChannelButton	  value="f0f0ff">
<param name=ColorForegroundCloseChannelButton	  value="000000">
<param name=NickLength value=9>
<param name=StatusFamilyFont value="SansSerif">
<param name=StatusStyleFont value="Plain">
<param name=StatusSizeFont value="12">
<param name=StatusLineSpacing value="16">
<param name=ChannelLineSpacing value="16">
<param name=QueryLineSpacing value="16">
<param name=ListChannelsFamilyFont value="SansSerif">
<param name=ListChannelsStyleFont value="Italic">
<param name=ListChannelsSizeFont value="20">
<param name=ColorListStatusBackground             value="f0f0ff">
<param name=ColorListStatusForeground             value="000000">
<param name=ColorListCloseBackground              value="f0f0ff">
<param name=ColorListCLoseForeground              value="000000">
<param name=EnableChannel value="yes">
<param name="AllowQuery" value="yes">
<param name="Encode" value="8859_1">

</applet>
</body>
</html>
