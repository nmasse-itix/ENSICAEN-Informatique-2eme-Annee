*********************************************************************************
* Origine du fichier l:\up\tp3\ex1\asm_ps0.asm  (rev. 16-02-2004)		*
* Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex1 		*
* pour être complété. 		 						*
*										*
* BINOME :									*
*********************************************************************************

*   		Fonction asm_ps0() en assembleur 
*		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
* Cette fonction peut être appelée dans un programme C dans lequel on a déclaré
* au début du fichier : extern int asm_ps0(short *,short *, int); 
*
* Exemple d'appel : y= asm_ps0(a,x,256);
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
* PROGRAMMATION EN ASSEMBLEUR SANS AUCUN SOUCI D'OPTIMISATION
********************************************************************************* 
	.def	_asm_ps0	;.def équivaut à public de l'assembleur 8085
				;Pour pouvoir être appelée par le C, le nom d'une
				;fonction en assembleur doit commencer par
				;un caractère underscore _
NBPS	.equ	100	

_asm_ps0:
	mvk	.s2	NBPS,b2		;On va calculer NBPS fois le produit
ps:					;Ce nombre est contrôlé par b2.
	; Registre A1 = element i du vecteur A
	; Registre B1 = element i du vecteur B
	; Registre A5 = A1 * B1
	; Registre A8 = index mobile (copie de A4)
	; Registre B8 = index mobile (copie de B4) 
	; Registre A3 = somme des A2 
	; Registre A2 = nb elements restants
	
	zero	.l	a3
	mv		a6,a2
	mv		a4,a8
	mv		b4,b8
	
loop:
	sub	.s	a2,1,a2
	
	ldh	.d	*a8++,a1
	nop		4
	ldh	.d	*b8++,b1
	nop		4
	
	mpy	.m	a1,b1,a5
	nop		1
	add	.l	a5,a3,a3

 [a2]	b 	.s	loop
	nop		5

	sub	.l2	b2,1,b2		;On calcule b2 fois le même produit scalaire
 [b2]	b 	.s2	ps
 	nop		5
 		
	mv		a3,a4
	
	b	.s2	b3		;return
	nop		5
