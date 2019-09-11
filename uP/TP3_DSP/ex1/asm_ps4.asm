*********************************************************************************
* Origine du fichier l:\up\tp3\ex1\asm_ps3.asm  (rev. 16-02-2004)		*
* Ce fichier est copié dans le répertoire (project) f:\up\tp3\ex1 		*
* pour être complété. 		 						*
*										*
* BINOME :									*
*********************************************************************************

*   		Fonction asm_ps4() en assembleur 
*		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^	
* Cette fonction peut être appelée dans un programme C dans lequel on a déclaré
* au début du fichier : extern int asm_ps3(short *,short *, int); 
*
* Exemple d'appel : y= asm_ps4(a, x, 256);
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
* LA DIFFÉRENCE AVEC asm_ps2 EST QUE L'ON CHERCHE À ALLER PUS VITE EN ALLANT LIRE
* LES ÉLÉMENTS D'UN VECTEUR 2 PAR 2 (LDW) AU LIEU DE 1 PAR 1 (LDH).
* VOIR ÉGALEMENT L'INSTRUCTION MPYH.
********************************************************************************* 
NBPS	.equ	100	
	.def	_asm_ps4
_asm_ps4:
	mvk	.s2	NBPS,b2		;On va calculer NBPS fois le produit




; todo on a un souci avec les data cross path il ny en a que 2
; et ils sont utilise obligatoirememt avec mpy & mpyh
; il faut donc mettre le branch et le sub du meme cote
; parce auil utilisent b0 donc todo; passer un add sur une unit 
; s et le sub sur une unit l

ps:					;Ce nombre est contrôlé par b2.
	mv		a4, a1
	mv		b4, b1
	zero		b5		; la somme finale
	zero		a9		; 1ere demi somme
	zero		b9		; 2eme demi somme

	mv		a6, b0		; init nb cases tableau

p1:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7


p2:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0


p3:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop



p4:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop



p5:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop



p6:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop
||	mpy	.m1	a7, b7, a8		
||	mpyh	.m2	a7, b7, b8


p7:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
||	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop
||	mpy	.m1	a7, b7, a8		
||	mpyh	.m2	a7, b7, b8


loop:	ldw 	.d1	*a1++,a7
||	ldw	.d2	*b1++,b7
|| [b0]	sub	.s2	b0, 2, b0
|| [b0]	b 	.s1	loop
||	mpy	.m1	a7, b7, a8		
||	mpyh	.m2	a7, b7, b8
||	add	.l1	a8, a9, a9
||	add	.l2	b8, b9, b9

; fin du calcul du produit scalaire: somme des demi sommes
	add		a9, b9, b5


	sub	.l2	b2,1,b2		;On calcule b2 fois le même produit scalaire
 [b2]	b 	.s2	ps
 	nop		5
	
	mv		b5, a4
	
	b	.s2	b3		;return
	nop		5

