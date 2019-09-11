/***********************************************************************/
/*                      Fichier ex51.c                                 */
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
void interrupt (*save_int_0b)(); /*Déclaration d'un pointeur pour sauver le vecteur d'interruption*/
unsigned char   imr59_bak;
unsigned int    touche;
unsigned char data_byte = 0x01;
unsigned char cnt_byte = 0x01;


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


	/* masquer entree IRQ7 du controleur d'interruption */
	outportb(IMR59, 0x80 | inportb(IMR59));


	do {
		/* Effacer l'ecran */
		clrscr();

		printf("status = 0x%x\n", inportb(LPT1_STAT));

		printf("cnt envoye = 0x%02x\n", cnt_byte);
		outportb(LPT1_CNT, cnt_byte);
		printf("cnt lu = 0x%02x\n", inportb(LPT1_CNT));

		printf("data envoye = 0x%02x\n", data_byte);
		outportb(LPT1_DATA, data_byte);
		printf("data lu = 0x%02x\n", inportb(LPT1_DATA));

		data_byte <<= 1;
		if (!data_byte)
			data_byte = 0x01;

		cnt_byte <<= 1;
		if (!(cnt_byte & 0x0F))
			cnt_byte = 0x01;

		printf("\nPressez ESC pour quitter, une autre touche pour continuer\n");
	} while ((touche = getch()) != ESC);

	ms_dos();
}


