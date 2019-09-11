/********************************************************************************
* Origine du fichier l:\up\tp3\ex1\ex1.c (rev. 08-03-2004)                      *
* Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex1 		*
* pour être complété. 		 						*
*										*
* BINOME :									*
*********************************************************************************/

#define	COUNT_PS	100	/*On calcule 100 fois le même produit scalaire*/

/* Include Files */             
#include <stdio.h>	/* Pour pouvoir utiliser printf */
#include "ex1cfg.h"	/* Fichier généré par CCS lors de la sauvegarde du fichier de configuration .cdb */
#include "data.h"

/* Déclaration des fonctions écrites en assembleur (asm..) ou en assembleur linéaire (sa...)*/
extern int 	asm_ps0(short *, short *, int); /*Aucun souci d'optimisation*/
extern int 	asm_ps1(short *, short *, int); /*Optimisation grossière*/
extern int 	asm_ps2(short *, short *, int); /*Software pipelining sans épilogue LDH*/
extern int 	asm_ps3(short *, short *, int); /*Software pipelining avec épilogue LDH*/
extern int 	asm_ps4(short *, short *, int); /*Software pipelining sans épilogue LDW*/

extern int 	sa_ps0(short *, short *, int); /*Assembleur linéaire avec instructions LDH*/
extern int 	sa_ps1(short *, short *, int); /*Assembleur linéaire avec instructions LDW*/
extern float 	sa_ps2(float *, float *, int); /*Assembleur linéaire avec des flottants*/


/* Déclarations des variables globales */
short a[256] = {A_ARRAY};	/*Pour faire le calcul avec des entiers*/
short x[256] = {X_ARRAY};	/*Pour faire le calcul avec des entiers*/

float af[256]= {A_ARRAY};	/*Pour faire le calcul avec des flottants*/
float xf[256]= {X_ARRAY};	/*Pour faire le calcul avec des flottants*/

int   y;			/*Pour stocker le résultat du calcul avec des entiers*/
float yf;			/*Pour stocker le résultat du calcul avec des flottants*/

/************************************************
 * 		Fonction c_ps0()		*
 * Calcul du produit scalaire avec des entiers 	*
 ************************************************/ 
int c_ps0 (short *m, short *n, int count)
{
int i,sum;
/*Pour allonger le temps d'exécution de la fonction, on fait COUNT_PS fois le même calcul */
int count_ps=COUNT_PS;

while( count_ps-- != 0 )
	{
	sum = 0;
 
	for (i=0; i < count; i++)
		{
    		sum = sum + m[i] * n[i];
  		}
  	}
return(sum);
}

/*************************************************
 * 		Fonction c_ps1()		 *
 * Calcul du produit scalaire avec des flottants *
 *************************************************/
float c_ps1 (float *m, float *n, int count)
{
int i;
float sum;

/*Pour allonger le temps d'exécution de la fonction, on fait COUNT_PS fois le même calcul */
int count_ps=COUNT_PS;

while( count_ps-- != 0 )
	{
	sum = 0;
 
	for (i=0; i < count; i++)
		{
    		sum = sum + m[i] * n[i];
  		}
  	}
  	
return(sum);
}
/***********************
 * Programme principal *
 ***********************/
void main(void)
{
y=asm_ps0(a,x,256);
printf("asm_ps0 (AUCUN SOUCI D'OPTIMISATION)      => y= %x hex \n", y);

y=asm_ps1(a,x,256);
printf("asm_ps1 (OPTIMISATION GROSSIÈRE)          => y= %x hex \n", y);

y=asm_ps2(a,x,256);
printf("asm_ps2 (LDH ET PIPELINING SANS ÉPILOGUE) => y= %x hex \n", y);

y=asm_ps3(a,x,256);
printf("asm_ps3 (LDH ET PIPELINING AVEC ÉPILOGUE) => y= %x hex \n", y);

y=asm_ps4(a,x,256);
printf("asm_ps4 (LDW ET PIPELINING SANS ÉPILOGUE) => y= %x hex \n", y);

y=sa_ps0(a,x,256);
printf("sa_ps0  (ENTIERS LDH)                     => y= %x hex \n", y);

y=sa_ps1(a,x,256);
printf("sa_ps1  (ENTIERS LDW)                     => y= %x hex \n", y);

yf=sa_ps2(af,xf,256);
printf("sa_ps2  (FLOTTANTS)                       => y= %x hex \n",(int)yf);

y=c_ps0(a,x,256);
printf("c_ps0   (ENTIERS)                         => y= %x hex \n", y);

yf=c_ps1(af,xf,256);
printf("c_ps1   (FLOTTANTS)                       => y= %x hex \n", (int)(yf));
printf("TERMINÉ\n");

while(1);	/* On fera mieux plus tard */
}
