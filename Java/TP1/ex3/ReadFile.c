 /**
 * #(@)ReadFile.h             ENSICAEN                       2005-02-20
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
 * (lecture d'un fichier)
 */ 


#include <stdio.h>
#include "ReadFile.h"


#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 

JNIEXPORT jbyteArray JNICALL Java_ReadFile_readFile(JNIEnv * env, jobject obj, jstring filename) {
  jbyteArray ba = NULL;
  const char * fname = (*env)->GetStringUTFChars(env, filename, JNI_FALSE);
  FILE * stream = fopen(fname, "r");

  if (stream != NULL) {

    // récupération de la taille du fichier
    struct stat s;
    stat(fname, &s);

    // création d'un noujeau tableau Java d'octet
    ba = (*env)->NewByteArray(env, s.st_size);

    // allocation d'un espace temporaire pour stocker le contenu du fichier
    unsigned char * buff = (unsigned char *) malloc(sizeof(unsigned char) * s.st_size);

    // lecture du fichier et copie dans le buffer
    fread(buff, sizeof(unsigned char), s.st_size, stream);

    // copie du buffer dans le tableau Java
    (*env)->SetByteArrayRegion(env, ba, 0, s.st_size, buff);

    // libération du buffer & fermeture du fichier
    free(buff);
    fclose(stream);
  }
 
  // libération de la chaine nom du fichier
  (*env)->ReleaseStringUTFChars(env, filename, JNI_FALSE);
  return ba;
}
