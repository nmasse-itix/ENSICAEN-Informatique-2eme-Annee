
/********************************************************************************
 * Origine du fichier L:\up\tp3\ex3a\bloc_gen.c (rev. 17-04-2004)               *
 * Ce fichier est copié dans le répertoire (project) F:\up\tp3\ex3a             *
 *                      NE PAS MODIFIER CE FICHIER                              *
 *                      **************************                              *
 ********************************************************************************/



/****************************************
 *          FONCTION SineGen()          *
 ****************************************/
int SineGen(void) {
	/* Pour une fréquence d'échantillonnage égale à 48 kHz,
	 * cette fonction génère un signal sinusoidal à 6 kHz 
	 * avec une amplitude égale à 0,5
	 */ 
	static float y[3] = {0, 0, 0.353934};
	static float a = 1.414215;
	
	y[0] = y[1] * a - y[2];
	y[2] = y[1];
	y[1] = y[0];
	
	return (int) (0x7FFF * y[0]);
} 

/************************************************************************
 *      FONCTION BlockGen() POUR GÉNÉRER UN BLOC DE "SINUS"             *
 * Cette fonction remplit un buffer avec des valeurs successives de     *
 * SineGen().                                                           *
 * Chaque valeur est doublée : une valeur pour chaque voie de l'AIC23   *
 * L'adresse du buffer et la taille du buffer sont passée en paramètres.*
 ************************************************************************/
void BlockGen(short * pbuf, int taille) {
	int i = 0;
	short signal;

	while (i != taille) {
		signal = SineGen();
		pbuf[i++] = signal;      /* Valeur du signal pour une voie */
		pbuf[i++] = signal;      /* Même valeur pour l'autre voie */
	}
}
