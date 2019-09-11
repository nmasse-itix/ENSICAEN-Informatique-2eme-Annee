/*************************************************************************/
/*                                                                       */
/*                      Fichier f:\up\tp1\ex320.c                        */
/*                                                                       */
/* BINOME :                                                              */
/*                                                                       */
/*                                                                       */
/*************************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>

#define ESC             0x1b

#define BASE_COM       0x2F8

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

/*********************************************/
/* Fonction ms_dos  Permet de revenir au DOS */
/*********************************************/
void ms_dos(void)
{
exit(0);
}

/*********************************************************************/
/* Fonction init_uart()    Initialisation du 16550 avec FIFO disable */
/*********************************************************************/
void init_uart(void)
{
outportb(LCR,0x80);     /*DLAB=1 pour acceder au baud rate generator*/
outportb(DLL,0x2 );
outportb(DLM,0x0 );     /*Vitesse 56 Kbauds*/
outportb(LCR,0x03);     /*DLAB=0 / 8 bits de data / 1 stop / Pas de Parité*/


outportb(FCR,0x00);     /*FIFO disable*/
outportb(IER,0x00);     /*Pas de demandes d'IT*/

inportb(RBR);           /*DEUX lectures de RBR pour "vider"*/
inportb(RBR);           /*d'éventuels "vieux" caractères*/
}


/*************************************************************************************************/
/* Programme principal                                                                           */
/*************************************************************************************************/
void main(void)
{
int             touche;
unsigned char   ctrl;

clrscr();
init_uart();
printf("                  EX320\n\n");
printf("Caractères de 8 bits, sans bit de parité\n");
printf("Frapper sur une touche pour envoyer le code de la touche à la maquette\n");
printf("ESC pour sortir\n\n");


while(1)
	{
	touche=getch();
	if( touche == ESC ) ms_dos();

	while(!((ctrl = inportb(LSR)) & 0x20));    /*Attendre transmetteur pret*/

	outportb(THR,touche);
	printf("Caractère transmis : %.2XH ",touche);

	while(!((ctrl = inportb(LSR)) & 0x01));  /*Attendre caractère reçu*/

	touche = inportb(RBR);

	printf("Caractere recu : %.2XH ", touche);/*Affichage du code reu*/
	printf("Status : %.2XH\r\n", (int) ctrl); /*Affichage du status*/
	}
}
