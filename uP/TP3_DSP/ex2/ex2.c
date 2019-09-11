/********************************************************************************
 * Origine du fichier L:\up\tp3\ex2\ex2.c (rev. 05-05-2004)                     *
 * Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex2 pour être    *
 * complété.                                                                    *
 *                                                                              *
 * BINOME : Thomas LIMIN - Nicolas MASSE                                        *
 ********************************************************************************/

/*Include files*/
#include "ex2cfg.h"             /* Fichier généré par CCS lors de sauvegarde du fichier de configuration */
#include <dsk6713.h>            /* Prototypes des API générales de BSL */
#include <dsk6713_aic23.h>      /* Prototypes des API de BSL relatives au codec */

/*Variables globales*/
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

#define UN	0x8000

typedef enum {LEFT = 0, RIGHT = 1} channel;

/**
 * Si elle est exécutée 48000 fois par seconde, cette fonction génère un signal à
 * 6 kHz avec une amplitude de 0,5
 */
int SineGen(void) {
	static float y[3] = {0, 0, 0.353934};
	const float a = 1.414215;
	
	y[0] = y[1] * a - y[2];
	y[2] = y[1];
	y[1] = y[0];
	
	return (int) (0x7FFF * y[0]);
}

/**
 * Genere une tonalite identique a la touche 1 d'un telephone.
 */
int DtmfTone(void) {
	static float y1[3] = {0, 0, 0.045618};
	const float a1 = 1.991682;
	static float y2[3] = {0, 0, 0.078906};
	const float a2 = 1.975007;

	y1[0] = y1[1] * a1 - y1[2];
	y1[2] = y1[1];
	y1[1] = y1[0];

	y2[0] = y2[1] * a2 - y2[2];
	y2[2] = y2[1];
	y2[1] = y2[0];

	return (int) (0x7FFF * ((y1[0] + y2[0]) / 2));
} 

/**
 * Multiplie deux nombres Q15.
 */
short int q15_times_q15(short int q1, short int q2) {
	int res = (int) q1 * q2;
	res >>= 15;
	
	return (short int) res;
}

/*
 * Si elle est exécutée 48000 fois par seconde, cette fonction génère un signal à
 * 6 kHz avec une amplitude de 0,5. 
 *
 * Calcul avec des entiers uniquement !
 */
int SineGenQ15(void) {
	static short yq[3] = {0, 0, UN * 0.353934};
	const short int aq = (unsigned int) (UN * 0.707107);

	int tmp = q15_times_q15(yq[1], aq);
	yq[0] = tmp + tmp - yq[2];
	yq[2] = yq[1];
	yq[1] = yq[0];

	return (int) yq[0];
}


/**
 * Cette fonction est exécutée suite à une demande d'interruption
 * du McBSP1 en transmission.
 * Elle envoie au codec un signal dont l'amplitude est calculée par SineGen()
 */
void XINT1_HWI(void) {
	/* The value sent to the DAC */
	static int signal;
	
	/* The DIP values */
	static short unsigned int dip0, dip3;
	
	/* LEFT or RIGHT */
	static channel ch = RIGHT;        

	/* Read DIP values */
	dip0 = DSK6713_DIP_get(0);
	dip3 = DSK6713_DIP_get(3);


	if (ch == RIGHT) {
		switch ((dip3 << 4) | dip0) {
		/* dip3 = UP, dip0 = UP */
		case 0x11: 
			signal = 0;
			break;
			
		/* dip3 = UP, dip0 = DOWN */
		case 0x10: 
			signal = SineGenQ15();
			break;
		
		/* dip3 = DOWN, dip0 = UP */
		case 0x01:
			signal = DtmfTone();
			break;
			
		/* dip3 = DOWN, dip0 = DOWN */
		case 0x00: 
			signal = SineGen();
			break;
		
		default:
			/* TODO : do something */
			break;
		}
		
		ch = LEFT;
	} else {
		ch = RIGHT;
	}

	DSK6713_AIC23_write(hAIC23, signal);
}

/**
 * Point d'entree du programme
 */
void main(void) {
	/* Initialisation BSL du DSK6713 */
	DSK6713_init();

	/* Open et configuration du codec AIC23 */
	hAIC23 = DSK6713_AIC23_openCodec(0, &confAIC23);

	/* Démasquage global des interruptions */
	IRQ_globalEnable();

	/* Démasquage de l'interruption du port McBSP1 en transmission */
	IRQ_enable(IRQ_EVT_XINT1);

	/* Initialisation des interrupteurs DIP */
	DSK6713_DIP_init();

	while(1);       /* On fera mieux plus tard... */
}
