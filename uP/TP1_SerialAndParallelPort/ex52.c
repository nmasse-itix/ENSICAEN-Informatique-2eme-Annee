/***********************************************************************/
/*                      Fichier ex52.c                                 */
/*                                                                     */
/* BINOME : b17.an2 LIMIN MASSE                                        */
/*                                                                     */
/***********************************************************************/


#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define LPT1_DATA       0x378
#define LPT1_STAT       (LPT1_DATA + 1)
#define LPT1_CNT	(LPT1_DATA + 2)

#define ESC             0x1B

#define	CNT59		0x20
#define IMR59		0x21



/*Variables globales*/
/********************/

unsigned char * message = "ABCDEFGHIJKLMNOP";


/*************************************************************************/
/* Fonction ms_dos()    Fonction exécutée pour revenir à MS-DOS          */
/*************************************************************************/
void ms_dos(void)
{
	/* demasquer l'entree IRQ7 du controleur d'interruption */
	outportb(IMR59, 0x7F & inportb(IMR59));

	exit(0);
}


/**************************************/
/*  Programme principal main          */
/**************************************/
void main(void) {
	int i;

	/* masquer entree IRQ7 du controleur d'interruption */
	outportb(IMR59, 0x80 | inportb(IMR59));

	clrscr();

	for (i = 0; i <= 16; i++) {

		/* polling en attendant que busy passe au niveau 1 */
		while (! (inportb(LPT1_STAT) & 0x80)) {
			printf("[%02X, %02X] Polling sur busy, attente de niveau 0\n", i, inportb(LPT1_STAT));
		}

		/* envoi des donnees */
		outportb(LPT1_DATA, message[i]);

		/* avertir la maquette de l'arrivee de donnees mise a 0 de strobe */
		outportb(LPT1_CNT, inportb(LPT1_CNT) & ~0x04);

		/* polling sur busy, en attendant le retour du niveau 0 */
		while ((inportb(LPT1_STAT) & 0x80)) {
			printf("[%02X, %02X] Polling sur busy, attente de niveau 0\n", i, inportb(LPT1_STAT));
		}

		/* remise a 1 du signal strobe */
		outportb(LPT1_CNT, inportb(LPT1_CNT) | 0x04);

	}

	ms_dos();
}


