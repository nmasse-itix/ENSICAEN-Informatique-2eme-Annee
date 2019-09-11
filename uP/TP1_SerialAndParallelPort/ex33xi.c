/***********************************************************************/
/*                      Fichier ex33xi.c                               */
/*                                                                     */
/* BINOME :                                                            */
/*                                                                     */
/***********************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define CNT59           0x20
#define IMR59           0x21

#define ESC             0x1B
#define BASE_COM        0x2F8

#define RBR             (BASE_COM+0)
#define THR             (BASE_COM+0)
#define IER             (BASE_COM+1)
#define IIR             (BASE_COM+2)
#define FCR             (BASE_COM+2)
#define LCR             (BASE_COM+3)
#define MCR             (BASE_COM+4)
#define LSR             (BASE_COM+5)
#define MSR             (BASE_COM+6)
#define DLL             (BASE_COM+0)
#define DLM             (BASE_COM+1)


/*Variables globales*/
/********************/
void interrupt (*save_int_0b)(); /*Déclaration d'un pointeur pour sauver le vecteur d'interruption*/

unsigned char   imr59_bak;
unsigned int    touche;
volatile unsigned char flag_recu;
unsigned int vitesse;
unsigned int fifo;
unsigned char ctrl;
unsigned char c;


/*************************************************************************/
/* Fonction ms_dos()    Fonction exécutée pour revenir à MS-DOS          */
/*************************************************************************/
void ms_dos(void)
{
setvect(0x0b,save_int_0b);   /*Restitution du vecteur d'IT MS-DOS pour IRQ3*/
outportb(IMR59,imr59_bak);   /*Restitution du registre IMR du 8259A*/
exit(0);
}


/*****************************/
/* Interruption 0BH (COM2)   */
/*****************************/
void interrupt it_com2(void)
{
flag_recu = 0x01;
outportb(CNT59,0x20);           /*Envoi d'un EOI non spécifique*/
}

/************************************************************************/
/* Fonction init_uart()    Initialisation de COM2                       */
/************************************************************************/
void init_uart(void)
{
unsigned char code;
outportb(LCR,0x80);     /*DLAB=1 pour accéder au baud rate generator*/
switch(vitesse)
	{
	case 1200    :      outportb(DLL, 96);break;
	case 19200    :     outportb(DLL, 6);break;
	case 56000   :      outportb(DLL, 2);break;
	default:	printf("Erreur\n");break;
	}
outportb(DLM, 0);

outportb(LCR, 0x03);      /*DLAB=0 / 8 bits de data / 1 Stop / Pas de parité*/

switch (fifo) {
	case 0:
		code = 0x00;
		break;
	case 1:
		code = 0x07;
		break;
	case 4:
		code = 0x47;
		break;
	case 8:
		code = 0x87;
		break;
	case 14:
		code = 0xc7;
		break;
	default:
		printf("Erreur\n");
		break;
	}


outportb(FCR, code);


inportb(RBR);           /*DEUX lectures de RBR pour "vider"*/
inportb(RBR);           /*d'éventuels "vieux" caractères*/

outportb(IER, 0x01);     /*IT en réception*/
outportb(MCR, 0x08);     /*Activer la sortie OUT 2 de l'UART (Cf Figure 11)*/
}

/**************************************/
/*  Programme principal main          */
/**************************************/
void main(void)
{
clrscr();                       /*Effacer l'écran*/

save_int_0b=getvect(0x0b);      /*Sauvegarde du vecteur d'interruption MS-DOS*/
setvect(0x0b,it_com2);          /*Mise en place de notre propre vecteur*/
imr59_bak = inportb(IMR59);       /*Sauvegarde du registre de masque du 8259A*/
outportb(IMR59,(inportb(IMR59) & 0xf7));/*Démasquer IRQ3*/




printf("                                 PROGRAMME EX33XP (INT)\n\n");
printf("0 =>  1200 Bauds (pour utiliser la maquette dans le mode 330)\n");
printf("1 => 19200 Bauds (pour utiliser la maquette dans le mode 331)\n");
printf("2 => 56000 Bauds (pour utiliser la maquette dans le mode 332)\n\n");

	printf("                        ENTRER VOTRE CHOIX POUR CONTINUER                      \n");

vitesse=0;
while( vitesse == 0 )
	{
	switch(getch())
		{
		case '0'   :      vitesse=1200 ;break;
		case '1'   :      vitesse=19200;break;
		case '2'   :      vitesse=56000;break;
		case ESC :      ms_dos()     ;break;

		default  :      putchar(0x07);  /*Emmission d'un bip sonore*/
		}
	}


printf("0=> pas de fifo\n");
printf("1=> fifo 1\n");
printf("4=> fifo 4\n");
printf("8=> fifo 8\n");
printf("9=> fifo 14\n");

fifo=16;
while( fifo == 16 )
	{
	switch(getch())
		{
		case '0'   :      fifo=0 ;break;
		case '1'   :      fifo=1 ;break;
		case '4'   :      fifo=4 ;break;
		case '8'   :      fifo=8 ;break;
		case '9'   :      fifo=14 ; break;
		case ESC :      ms_dos()     ;break;

		default  :      putchar(0x07);  /*Emmission d'un bip sonore*/
		}
	}


	init_uart();
	clrscr();

	printf("\nINITIALISATION DU PORT COM : ");
	printf("Vitesse : %u bauds, 8 bits, pas de parité \n",vitesse);
	printf("             FIFO = %u\n", fifo);
	printf("\nFRAPPER SUR UNE TOUCHE POUR DECLENCHER L'ARRIVEE DE CARACTERES SUR LE PORT COM\n\n");

	if( getch() == ESC ) {
		ms_dos();
	}


	while( !((ctrl = inportb(LSR)) & 0x20));       /*Attendre transmetteur prêt*/

	/*Envoi d'un caractère à la maquette, peu importe le caractère*/
	outportb(THR,0x55);



while(1)
	{

	if( kbhit() != 0 )
		{
		touche=getch();
		if( touche == ESC )

			ms_dos();
		else
			{
			while( ! (inportb(LSR) & 0x20));     /*Attendre transmetteur pret*/
			outportb(THR,touche);
			}

		}



	if( flag_recu != 0 )    /*Au moins un caractère est disponible sur COM*/
		{
                if( (ctrl = inportb(LSR)) & 0x0E)             /*Test erreur réception*/
			{
			printf("\nErreur réception : code %.2xH", ctrl);
			ms_dos();
			}

		while (inportb(IIR) & 0x4) {
			c = inportb(RBR);
			putchar(c);
		}

		flag_recu = 0;

	}


	}
}