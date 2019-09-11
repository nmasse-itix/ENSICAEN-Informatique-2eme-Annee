/********************************************************************************
 * Origine du fichier L:\up\tp3\ex3a\ex3a.c (rev. 24-05-2004)                   *
 * Ce fichier est copié dans le répertoire (project) F:\up\tp3\ex3a pour être   *
 * complété.                                                                    *
 * On utilise l'EDMA et on le programme sans l'aide graphique CSL de DSP/BIOS   *
 *                                                                              *
 * BINOME : Nicolas MASSE & Thomas LIMIN                                        *
 ********************************************************************************/

#include "ex3acfg.h"
#include "ex3a.h"

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

EDMA_Handle hEdmaReload;        /*Handle pour la table de reload*/
EDMA_Handle hEdma14;            /*Handle pour le canal14 (XEVT1)*/

EDMA_Config confEDMA = {
	EDMA_OPT_RMK(
		EDMA_OPT_PRI_LOW,
		EDMA_OPT_ESIZE_16BIT, 
		EDMA_OPT_2DS_NO,
		EDMA_OPT_SUM_INC,
		EDMA_OPT_2DD_NO,
		EDMA_OPT_DUM_NONE,
		EDMA_OPT_TCINT_YES,
		EDMA_OPT_TCC_OF(TCC),
		EDMA_OPT_LINK_YES,
		EDMA_OPT_FS_NO
	),
	EDMA_SRC_OF(buffer),   
	EDMA_CNT_OF(BUFFERSIZE),
	EDMA_DST_OF(DXR1),
	EDMA_IDX_OF(0),
	EDMA_RLD_OF(0)  /* Provisoire */
};

/**
 * INITIALISATION DE L'EDMA
 */
void Edma_init(void) {
	/* Open du canal 14 (XEVT1). */
	hEdma14 = EDMA_open(EDMA_CHA_XEVT1, EDMA_OPEN_RESET);

	/* On va maintenant obtenir un handle pour la table de Reload. 
	 * Pour cela on utilise EDMA_allocTable(-1). En passant -1 comme 
	 * paramètre on laisse le soin à CSL de choisir une table 
	 * disponible parmi les 69 existantes.
	 */
	hEdmaReload = EDMA_allocTable(-1);

	/* Maintenant que l'on sait quelle est la table de Reload utilisée, 
	 * il faut mettre à jour le paramètre rld de myConfig
	 */
	confEDMA.rld = (confEDMA.rld & 0xffff0000) | (EDMA_RLD_RMK(0,hEdmaReload));

	/* Configuration de l'EDMA pour le canal 14 */
	EDMA_config(hEdma14, &confEDMA);

	/* Configuration de la table Reload utilisée */
	EDMA_config(hEdmaReload, &confEDMA);

	/* Démasquer l'Event XEVT1 (canal14) en mettant à jour le registre EER */
	EDMA_enableChannel(hEdma14);
}                               

/**
 * INITIALISATION DU CODEC AIC23
 */
void Codec_init() {
	/* Open et configuration du codec AIC23 */
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
	/* Rafraîchir le buffer */
	BlockGen(buffer, BUFFERSIZE);

	/* Remise à 0 du bit TCC dans le registre CIPR */
	EDMA_intClear(TCC);	
}

/**
 * PROGRAMME PRINCIPAL
 */
void main(void) {
	BlockGen(buffer, BUFFERSIZE);   /* Initialisation du buffer */    

	/* Initialisation BSL du DSK6713 */
	DSK6713_init();
	
	/* Initialisation de l'EDMA */
	Edma_init();

	/* Initialisation du CODEC AIC23 */
	Codec_init();

	/* Démasquage total de l'interruption EDMA pour l'Event XEVT1 */
	EDMA_intEnable(TCC);

	/* Démasquage de l'interruption du port EDMA */
	IRQ_enable(IRQ_EVT_EDMAINT);

	/* Démasquage global des interruptions */
	IRQ_globalEnable();
	
	// A défaut de mieux ... 
	while(1);
}
