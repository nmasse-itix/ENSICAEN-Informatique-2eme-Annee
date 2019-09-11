/********************************************************************************
* Origine du fichier L:\up\tp3\ex2\ex2_0.c (rev. 17-03-2004)                    *
* Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex2               *
* Il n'a pas lieu d'être modifié.                                               *
*                                                                               *
* BINOME :                                                                      *
*********************************************************************************/
#define TAILLE_BUFFER   32      /*Taille du tableau sinus*/

/* Include Files */             
#include "ex2cfg.h"     /* Fichier généré par CCS lors de la sauvegarde du fichier de configuration .cdb */


/*Variables globales*/
int sinus[TAILLE_BUFFER];       /* Utilisé uniquement pour "voir" le signal généré par SineGen()*/


/**********************
 * FONCTION SineGen() *
 **********************
 Si cette fonction est exécutée 48.000 fois par seconde, elle retourne un signal 
 sinusoidal à 6 kHz avec une amplitude de 0,5*/
int SineGen(void)
{
static float y[3]={0,0,0.353934};
static float a=1.414215;

y[0]=y[1]*a - y[2];
y[2]=y[1];
y[1]=y[0];

return( (int)(0x7FFF*y[0]) );
} 


/***********************
 * PROGRAMME PRINCIPAL *
 ***********************/
void main(void)
{
unsigned int i;

/********************************************************************************
 Le remplissage du tableau sinus ne sert que pour "voir" le signal généré par SineGen().
 On utilise View -> Graph -> Time/Frequency proposé par CCS*/
for(i=0; i<TAILLE_BUFFER; i++)
	{
	sinus[i]=SineGen();
	}
/********************************************************************************/      
	 
while(1);
} 


