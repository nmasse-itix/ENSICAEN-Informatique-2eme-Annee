/********************************************************************************
 * Origine du fichier l:\up\tp3\ex4a\ex4a.c (rev. 26-05-2004)			*
 * Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex4a pour être	*
 * complété.									*
 * DSP/BIOS : Mise en évidence de l'avantage de LOG_printf par rapport à printf	*
 *										*
 * BINOME :									*
 ********************************************************************************/
 
/* Include Files */
#include <stdio.h>		/* Absolument obligatoire si on utilise printf;
				 * Si on l'oublie, pas d'erreur ni de warning ..
				 * MAIS printf ne fonctionne pas !! */
#include "ex4acfg.h"
#include <dsk6713.h>
#include <dsk6713_led.h>

unsigned int 	nit;		/* Compteur d'interruption du Timer1 */ 
unsigned int	time;		/* Temps écoulé en secondes */
unsigned int	print_choix = 0;/* 0, 1, 2, ou 3 */

/**
 *         PROGRAMME D'INTERRUPTION DU TIMER1					
 * Ce programme d'interruption est exécuté 20 fois par secondes.		
 * Il s'agit d'inverser l'état des 4 LED du DSK. De plus :			
 * - Si le DIP 0 est enfoncé => Afficher un message avec printf. 		
 * - Si le DIP 3 est enfoncé => Afficher un message avec LOG_printf. 		
 */
void TIMER1_HWI(void) {
	DSK6713_LED_toggle(0);
	DSK6713_LED_toggle(1);
	DSK6713_LED_toggle(2);
	DSK6713_LED_toggle(3);

	if(--nit == 0) {
		nit=20;
		++time;
		
		switch (print_choix) {
		case 0:
			break;
		case 1:
			printf("Time= %d secondes\n", time);
			break;
		case 2:
			LOG_printf(&LOG_it_timer1, "Time= %d secondes\n", time);
			break;
		case 3:
			printf("Time= %d secondes\n", time);
			LOG_printf(&LOG_it_timer1, "Time= %d secondes\n", time);
			break;
		}
			
	}
}

/**
 *         		PROGRAMME PRINCIPAL					
 * Il se limite aux initialisations necessaires.Ceci étant fait, il se termine	
 * par return. DSP/BIOS prend alors le contrôle de l'application. 		
 */
void main(void) {
	DSK6713_init();
	DSK6713_LED_init();

	nit = 1;
	time = 0;
	printf("EXERCICE 4a\n");

	/* Démasquage total de l'interruption du TIMER1 */
	IRQ_enable(IRQ_EVT_TINT1);
	
	/* Ce n'est pas indispensable car c'est automatique dans
	 * la mesure où main() se termine par return */
	IRQ_globalEnable();
	
	return;
}		
