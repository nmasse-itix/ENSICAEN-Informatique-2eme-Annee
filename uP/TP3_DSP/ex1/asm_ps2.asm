*********************************************************************************
* Origine du fichier l:\up\tp3\ex1\asm_ps2.asm  (rev. 16-02-2004)		*
* Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex1 		*
* pour être complété. 		 						*
*										*
* BINOME :									*
*********************************************************************************

*   		Fonction asm_ps2() en assembleur 
*		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
* Cette fonction peut être appelée dans un programme C dans lequel on a déclaré
* au début du fichier : extern int asm_ps2(short *,short *, int); 
*
* Exemple d'appel : y= asm_ps2(a, x, 256);
* Où le compilateur C va t-il mettre les paramètres? On peut trouver l'information
* dans TMS320C6000 Optimizing Compiler Guide (SPRU 1871) pages 8-18 et suivantes :
*
* Premier paramètre	(ici, adresse de a)	=> Registre A4
* Second paramètre	(ici, adresse de x)	=> Registre B4
* Troisième paramètre	(ici, 256)		=> Registre A6
*
* La valeur calculée doit être retournée dans le registre A4.
* Le compilateur a placé l'adresse de retour dans le registre B3.
*
* POUR CE PROGRAMME :
* ^^^^^^^^^^^^^^^^^^^
* PROGRAMMATION EN ASSEMBLEUR EN UTILISANT LE SOFTWARE PIPELINING SANS ÉPILOGUE.
* LECTURE DES ÉLÉMENTS DES VECTEURS AVEC L'INSTRUCTION LDH.
********************************************************************************* 
NBPS	.equ	100	
	.def	_asm_ps2
_asm_ps2:
	mvk	.s2	NBPS,b2		;On va calculer NBPS fois le produit
	mv 		a4,a8
	mv		b4,b8
	
ps:					;Ce nombre est contrôlé par b2.
	zero		a4
	mv		a6,b0
	mv		a8,a1
||	mv		b8,b1

p1:	ldh 	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4

p2:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0

p3:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2 	b0,1,b0
|| [b0]	b 	.s2	loop	

p4:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0
|| [b0] b 	.s2	loop

p5:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0
|| [b0] b 	.s2	loop

p6:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0
|| [b0] b 	.s2	loop
||	mpy	.M1x	a2,b4,a3

p7:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0
|| [b0] b 	.s2	loop
||	mpy	.M1x	a2,b4,a3

loop:	ldh	.d1	*a1++,a2
||	ldh	.d2	*b1++,b4
|| [b0]	sub	.l2	b0,1,b0
|| [b0] b 	.s2	loop
||	mpy	.M1x	a2,b4,a3
||	add	.l1	a4,a3,a4
	
	sub	.l2	b2,1,b2		;On calcule b4 fois le même produit scalaire
 [b2]	b 	.s2	ps
 	nop		5
	
	b	.s2	b3		;return
	nop		5