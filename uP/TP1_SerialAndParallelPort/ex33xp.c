/**************************************************************************/
/*                      Fichier f:\up\tp1\ex33xp.c                        */
/*                                                                        */
/* BINOME :                                                               */
/*                                                                        */
/*                                                                        */
/**************************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

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


int             touche;
unsigned int    vitesse;

/****************************************************************************/
/* Fonction ms_dos()                                                        */
/****************************************************************************/
void ms_dos(void)
{
exit(0);
}

/***************************************************************************/
/* Fonction init_uart()    Initialisation du 16550 avec FIFO disable       */
/***************************************************************************/
void init_uart(void)
{

outportb(LCR,0x80);     /*DLAB=1 pour accéder au baud rate generator*/
switch(vitesse)
	{
	case 1200  :      outportb(DLL, 96);break;
	case 19200 :      outportb(DLL, 6);break;
	case 56000 :      outportb(DLL, 2);break;
	}
outportb(DLM, 0);

outportb(LCR, 0x03);      /*DLAB=0 / 8 bits de data / 1 Stop / Pas de parité*/

outportb(FCR,0x00);     /*FIFO disable*/
outportb(IER,0x00);     /*Pas de demandes d'IT*/

inportb(RBR);           /*DEUX lectures de RBR pour "vider"*/
inportb(RBR);           /*d'éventuels "vieux" caractères*/
}

/**************************************/
/*  Programme principal main          */
/**************************************/
void main(void)
{
int ctrl;
clrscr();
printf("                                 PROGRAMME EX33XP (Polling)\n\n");
printf("0 =>  1200 Bauds (pour utiliser la maquette dans le mode 330)\n");
printf("1 => 19200 Bauds (pour utiliser la maquette dans le mode 331)\n");
printf("2 => 56000 Bauds (pour utiliser la maquette dans le mode 332)\n\n");

	printf("                        ENTRER VOTRE CHOIX POUR CONTINUER                      ");

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

	init_uart();
	clrscr();

	printf("\nINITIALISATION DU PORT COM : ");
	printf("Vitesse : %u bauds, 8 bits, pas de parité \n",vitesse);
	printf("             LE FIFO DE L'UART N'EST PAS EN SERVICE\n");
	printf("\nFRAPPER SUR UNE TOUCHE POUR DECLENCHER L'ARRIVEE DE CARACTERES SUR LE PORT COM\n\n");

	if( getch() == ESC ) {
		ms_dos();
	}


	while( !((ctrl = inportb(LSR)) & 0x20));       /*Attendre transmetteur prêt*/

	/*Envoi d'un caractère à la maquette, peu importe le caractère*/
	outportb(THR,0x55);

while(1)
	{
	if( kbhit() != 0 ) {
		touche=getch();

		if( touche == ESC ) ms_dos();

		else
			{
			while( ! (inportb(LSR) & 0x20));     /*Attendre transmetteur pret*/
			outportb(THR,touche);
			}

		}

	if( inportb(LSR) & 0x01)      /*Un caractère est disponible sur COM ?*/
		{
		char c = inportb(RBR);
		putchar(c);     /*Afficher le caractère reçu*/

		if( (ctrl = inportb(LSR)) & 0x0E)             /*Test erreur réception*/
			{
			printf("\nErreur réception : code %.2xH", ctrl);
			ms_dos();
			}

		if(c == '\0' )                /*Test fin d'émission*/
			{
			    /* ms_dos(); */
			}
		}
	}
}