/** 
 * #(@)nomfichier.c             ENSICAEN                       2005
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
 * Description des objectifs du programme, le sujet a traiter.
 * Pour le programme qui contient le main(),
 * la ligne de commande pour executer le programme.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Description succinte de l'algorithme utilise comme solution.
 * Eventuellement: Les references (cahier des charges,bibliographiques...).
 */

/*
 * @version	0.0.1
 *
 * @Fait	Detail de ce qui a ete fait.
 *
 * @Afaire	Detail de ce qui n'a pas ete fait.
 */

int validate(char *, char *);

void * pam_test(void * arg) {
	char ** env = __environ;

	do {
		printf("%s\n", *env);
	} while (*(env++));
	
	if (validate("visiteur", "ok")) {
		printf("pouet\n");
	}
}


int main() {
	pthread_t th;

	pthread_create(&th, NULL, pam_test, NULL);
	pthread_join(th, NULL);

	return 0;
}
