/********************************************************************************
 * Origine du fichier l:\up\tp3\ex3b\ex3b.c (rev. 19-04-2004)			*
 * Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex3b pour être	*
 * complété.									*
 * On utilise l'EDMA et on le programme avec l'aide graphique CSL de DSP/BIOS	*
 *										*
 * BINOME :									*
 ********************************************************************************/

#include "ex3bcfg.h"
#include "ex3b.h"

#include <dsk6713.h>
#include <dsk6713_aic23.h>
#include <csl_edma.h>

extern void BlockGen(short *pbuffer, int taille);

/* Variables globales */

DSK6713_AIC23_CodecHandle hAIC23;
DSK6713_AIC23_Config confAIC23 = { 
    0x0017,  /* 0 DSK6713_AIC23_LEFTINVOl  left line input channel volume */ 
    0x0017,  /* 1 DSK6713_AIC23_RIGHTINVOl Right line input channel volume */
    0x01f9,  /* 2 DSK6713_AIC23_LEFTHPVOl  left channel headphone volume */  
    0x01f9,  /* 3 DSK6713_AIC23_RIGHTHPVOl Right channel headphone volume */ 
    0x0011,  /* 4 DSK6713_AIC23_ANAPATH    Analog audio path control */      
    0x0000,  /* 5 DSK6713_AIC23_DIGPATH    Digital audio path control */     
    0x0000,  /* 6 DSK6713_AIC23_POWERDOWN  Power down control */             
    0x0043,  /* 7 DSK6713_AIC23_DIGIF      Digital audio interface format */ 
    0x0081,  /* 8 DSK6713_AIC23_SAMPLERATE Sample rate control 48 kHz */            
    0x0001   /* 9 DSK6713_AIC23_DIGACT     Digital interface activation */   
};

short buffer[BUFFERSIZE];


/**
 * INITIALISATION DU CODEC AIC23
 */
void Codec_init() {
	/* Open et configuration du codec AIC23 */	
	DSK6713_init();
	
	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);	
}

/**
 *                     PROGRAMME D'INTERRUPTION                        
 * Ce programme d'IT est exécuté à la demande de l'EDMA.               
 * Il s'agit donc de l'INT8. On utilise le fichier de configuration    
 * pour faire le nécessaire afin que cette fonction corresponde au     
 * programme d'interruption à exécuter :                               
 *  - Mise en place du vecteur et "dispatcher".                        
 */
void EDMA_HWI(void) {
	/* Remise à 0 du bit TCC dans le registre CIPR */
	EDMA_intClear(TCC);	
	
	/* Rafraîchir le buffer */
	BlockGen(buffer, BUFFERSIZE);


}

/**
 * PROGRAMME PRINCIPAL
 */
void main(void) {
	/* Initialisation du buffer */
	BlockGen(buffer, BUFFERSIZE);		
	
	/* Initialise le codec */
	Codec_init();

	/* Démasquage total de l'interruption EDMA pour l'Event XEVT1 */
	EDMA_intEnable(TCC);

	/* Démasquage de l'interruption du port EDMA */
	IRQ_enable(IRQ_EVT_EDMAINT);

	/* Démasquage global des interruptions */
	IRQ_globalEnable();
	
	/* A défaut de mieux ... */
	while(1);
}
