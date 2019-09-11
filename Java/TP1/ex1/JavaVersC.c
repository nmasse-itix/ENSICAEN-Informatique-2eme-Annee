 /**
 * #(@)JavaVersC.c             ENSICAEN                       2005-02-27
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


/**
 * Implémentation en C d'une fonction native Java
 * (affichage de bonjour)
 */ 


#include <stdio.h>
#include "JavaVersC.h"



JNIEXPORT void JNICALL Java_JavaVersC_bonjour(JNIEnv * env, jobject obj) {
  fprintf(stdout, "Bonjour\n");
}
