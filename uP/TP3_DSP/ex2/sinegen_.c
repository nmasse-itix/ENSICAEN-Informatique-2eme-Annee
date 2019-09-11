/****************************************
 *      FONCTION SineGen_q15()          *
 ****************************************/
int SineGen_q15()
{
/*Il s'agit de générer un signal à 6 kHz en faisant le calcul avec des Q15.
  Cette fonction est utilisée à la fin du chapitre II (paragraphe II.7.5).*/
#define UN	0x8000
#define	yq2	(unsigned int)(UN*0.353934)
#define AQ	(unsigned int)(UN*0.707107) /*1.414215/2=0.707107*/

static 	short	yq[3]={0,0,yq2};
static	short	aq=AQ;

/* À compléter*/
}  
