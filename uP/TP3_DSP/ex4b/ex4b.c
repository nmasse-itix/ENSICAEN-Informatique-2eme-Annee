/********************************************************************************
 * Origine du fichier L:\up\tp3\ex4b\ex4b.c (rev. 14-01-2005)                   *
 * Ce fichier est copié dans le répertoire (project) F:\up\tp3\ex4b pour être   *
 * complété.                                                                    *
 * DSP/BIOS : HWI et SWI. module STS,                                           *
 *                                                                              *
 * BINOME :                                                                     *
 ********************************************************************************/

/* Include Files */
/* ============= */
#include <stdio.h>              /*Absolument obligatoire si on utilise printf;
				  Si on l'oublie, pas d'erreur ni de warning ..
				  MAIS printf ne fonctionne pas !!*/
#include "ex4bcfg.h"
#include <dsk6713.h>
#include <dsk6713_led.h>
#define  TEMPO  0x01F00000      /*Pour une tempo logicielle d'environ 1 seconde*/

/********************************************************************************
 *         PROGRAMME D'INTERRUPTION DU TIMER1                                   *
 * Ce programme d'interruption est exécuté 20 fois par secondes (période 50 ms).*
 * Il s'agit :                                                                  *
 * -1- D'inverser l'état de la LED 0 pour qu'elle clignote 10 fois par seconde. *
 * -2- De poster avec SWI_dec() la SWI_ex4b dont la mailbox est initialisée     *
 *     à 100. 100 fois 50 ms => la SWI va être exécutée toutes les 5 secondes.  *
 ********************************************************************************/
void TIMER1_HWI(void)
{
		DSK6713_LED_toggle(0);
		SWI_dec(&SWI_ex4b);
}

/********************************************************************************
 *              SOFTWARE INTERRUPT SWI_ex4b                                     *
 * Avec le fichier de configuration on a défini une SWI de nom SWI_ex4b.        *
 * Les propriétés de SWI_ex4b sont les suivantes :                              *
 * Fonction exécutée : ALGO_SWI.                                                *
 * Mailbox : 100.                                                               *
 * Cette SWI est exécutée toutes les 5 secondes. Le traitement consiste à       *
 * allumer la LED 1, puis à attendre environ 1 seconde en exécutant une boucle  *
 * de décrémentation logicielle. Pour cela, on utilise la constante TEMPO	*
 * d‚finie au d‚but de ce fichier. On termine en éteignant la LED 1.            *
 ********************************************************************************/
void ALGO_SWI(void)
{

	unsigned int tempo = 20000000;
	DSK6713_LED_on(1);
	STS_set(&STS_algo, CLK_gethtime());
	while(--tempo);
	STS_delta(&STS_algo, CLK_gethtime());
	DSK6713_LED_off(1);
	

}

/********************************************************************************
 *                      PROGRAMME PRINCIPAL                                     *
 * Il se limite aux initialisations necessaires.Ceci étant fait, il se termine  *
 * par return. DSP/BIOS prend alors le contrôle de l'application.               *
 ********************************************************************************/
void main(void)
{
DSK6713_init();
DSK6713_LED_init();

printf("EXERCICE 4b\n");

/* Démasquage total de l'interruption du TIMER1
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
IRQ_enable(IRQ_EVT_TINT1);
IRQ_globalEnable();

return;
}               
