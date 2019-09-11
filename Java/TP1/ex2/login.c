/** 
 * #(@)login.c                  ENSICAEN                       2005
 *
 * @author MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
 * @author LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin
 * F-14050 Caen Cedex
 *
 * Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 * reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 */

/**
 * Definition des methodes natives qui seront inclues dans la librairie
 * chargee par le programme Login ecrit en java.
 */

#include <stdio.h>
#include <security/pam_appl.h>

#include <string.h>
#include <stdlib.h>

#include "Login.h"

/*
 * @version	0.0.1
 *
 * @Fait	-
 *
 * @Afaire	Lecture a partir du fichier
 */

static int conversationFct(int num_msg, const struct pam_message ** msg,
		struct pam_response ** resp, void * appdata_ptr) {
	char * pass = (char *) appdata_ptr;
	size_t len = strlen(pass);
	
	switch (msg[num_msg - 1]->msg_style) {
	case PAM_PROMPT_ECHO_OFF:
		(*resp) = malloc(sizeof(struct pam_response));
		(*resp)[num_msg - 1].resp = malloc(len + 1);
		strncpy((*resp)[num_msg - 1].resp, pass, len + 1)[len] = '\0';
		(*resp)[num_msg - 1].resp_retcode = 0;
		
		break;
	default:
		break;
	}
	
	return PAM_SUCCESS;
}


int validate(const char * login, const char * pass) {
	int res;
	pam_handle_t * pamHandle = NULL;
	struct pam_conv pamConversation = {conversationFct, (void *) pass};
	
	printf("login: %s\n", login);
	res = pam_start("java_login", login, &pamConversation, &pamHandle);
	printf("pam_start: %s\n", pam_strerror(pamHandle, res));

	res = pam_authenticate(pamHandle, 0);
	printf("pam_authenticate: %s\n", pam_strerror(pamHandle, res));
	
	res = pam_acct_mgmt(pamHandle, 0);
	printf("pam_acct_mgmt: %s\n", pam_strerror(pamHandle, res));
	
	res = pam_end(pamHandle, res);
	printf("pam_end: %s\n", pam_strerror(pamHandle, res));

	return 0;
}

/*
 * @see Login.h
 */
JNIEXPORT jboolean JNICALL Java_Login_validate
  (JNIEnv * env, jclass class, jstring login, jstring passwd) {
	  /* Copie des chaines passees en parametre */
	  const char * l = (*env)->GetStringUTFChars(env, login, 0);
	  const char * p = (*env)->GetStringUTFChars(env, passwd, 0);
	  jboolean ret;

	  /* Creation du booleen retourne */
	  if (validate(l, p)) {
		  ret = JNI_TRUE;
	  } else {
		  ret = JNI_FALSE;
	  }
	  
	  /* On libere les copies des chaine de caracteres */
	  (*env)->ReleaseStringUTFChars(env, login, l);
	  (*env)->ReleaseStringUTFChars(env, passwd, p);
	  
	  return ret;
}


