page    60,135
title   melodie


;               *************************************************
;               *                                               *
;               *     Assembleur 8086 sur PC     Exercice 9     *
;               *                                               *
;               *************************************************

name e9

extrn   ci:far ,co:far
extrn   inicrt:far
extrn   clrcrt:far

CNT53   equ     43h
TIM0    equ     40h
CNT59   equ     20h


TIM2	equ	42h
CNT53_2	equ	43h
PB	equ	61h
TEMPO	equ	100
NB_NOTE	equ	70 ; = 2 x le nb de note - 1 (car 2 octet par note)



pile    segment stack 'stack'
dw      50      dup (?)
pile    ends

data    segment

it8     dd      ?       ;Sauvegarde du vecteur d'interruption INT8 de MS-DOS
it23    dd      ?       ;Sauvegarde du vecteur d'interruption INT23H de MS-DOS

nit     db      1       ;Compteur d'interruption de type 8.
note	db	0	;Note en cours

data    ends
;-------------------------------------------------------------------------------

code    segment
assume  cs:code,ds:data

start:  cli             ;Masquer l'entree INTR du 8086
	mov     ax,data
	mov     ds,ax   ;DS permet d'acceder aux variables du segment data


	;Sauvegarde des vecteurs d'interruption de MS-DOS
	;------------------------------------------------
	mov     al,8
	mov     ah,35h
	int     21h     ;Le vecteur d'interruption numero 8 est placé dans ES:BX
	mov     word ptr it8,bx
	mov     word ptr it8+2,es

	mov     al,23h
	mov     ah,35h
	int     21h     ;Le vecteur d'interruption numero 23h est placé dans ES:BX
	mov     word ptr it23,bx
	mov     word ptr it23+2,es


	;Mise en place de nos propres vecteurs d'interruption
	;----------------------------------------------------
	push	ds

	mov     al,8
	mov     bx,seg ittim
	mov     ds,bx
	mov     dx,offset ittim
	mov     ah,25h
	int     21h     ;Initialisation du vecteur numero 8 avec DS:DX

	mov     al,23h
	mov     bx,seg itbrk
	mov     ds,bx
	mov     dx,offset itbrk
	mov     ah,25h
	int     21h     ;Initialisation du vecteur numero 23h avec DS:DX

	pop	ds

	;Programmation du timer0 du 8253 :
	;---------------------------------
	mov     al,00110110b    ;tim0 => 2 octets ,mode 3, binaire
	out     CNT53,al
	mov     al,9ch
	out     TIM0,al
	mov     al,2eh
	out     TIM0,al         ;Pour obtenir une IT toutes les 10 ms


	;Programme principal
	;-------------------

	; initialisation du timer 2 em mode 3,
	; 2 octet, comptage binaire

	mov	al, 10110110b
	out	CNT53_2, al


	; activation des lignes pb0 et pb1
	in	al, PB
	or	al, 00000011b
	out	PB, al


	sti

always: call    ci
	jmp     always


;                       ************************************
;                       *  Programme d'interruption Timer  *
;                       ************************************



ittim:  push    ax
	push    bx
	push    cx
	push    dx
	push    si
	push    di
	push    ds
	push    es

	mov     ax,data
	mov     ds,ax   	; Au cas ou ci modifie ds



	dec     nit     ;On n'intervient que toutes les secondes cad toutes les 100 IT
	jz      non_saut
	jmp	fin

non_saut:

	mov	al, note	; On recupere la note courante
	mov	ah, al
	mov	bx, offset gamme
	xlat	byte ptr gamme
	xchg	al, ah
	inc	al
	mov	dl,al		; sauvegarde de note courante + 1
	xlat	byte ptr gamme		; la frequence de la note courante est recuperee
	xchg	al,ah
	out	TIM2, al
	xchg	al,ah
	out	TIM2, al	; reglage freq timer2
	inc	dl		; increment de la note (note courante + 2)
	mov	note, dl	; sauvegarde de la nouvelle note courante
	mov	nit, TEMPO
	cmp	dl, NB_NOTE
	jne	fin

	mov note, 0		; redemarrage des gammes

fin:    mov     al,20h
	out     CNT59,al                ;Envoi d'un EOI non specifique au 8259A
	pop     es
	pop     ds
	pop     di
	pop     si
	pop     dx
	pop     cx
	pop     bx
	pop     ax
	sti
	iret

;                       ********************************************
;                       * Programme d'interruption pour CTRL+BREAK *
;                       ********************************************

itbrk:  nop
	push    ax
	push    bx
	push    ds

	;Restitution des vecteurs d'interruptions de MS-DOS
	;--------------------------------------------------
	xor     ax,ax
	mov     es,ax           ;es=0 pour acceder à la table des vecteurs.
	mov     ax,data         ;ds pointe sur le segment data pour pouvoir acceder aux sauvegardes des vecteurs
	mov     ds,ax           ;des vecteurs d'interruption.

	push    ds
	lds     bx,it8          ;DS:BX = vecteur INT8 MS-DOS
	mov     es:[4*8h],bx
	mov     es:[(4*8h)+2],ds

	pop     ds
	lds     bx,it23         ;DS:BX = vecteur INT23 MS-DOS
	mov     es:[4*23h],bx
	mov     es:[(4*23h)+2],ds

	;Reprogrammation du timer0 conformément à MS-DOS
	;-----------------------------------------------
	xor     al,al
	out     TIM0,al
	out     TIM0,al         ;Il faut charger le timer avec 0000


	; mort au timer 2
	in	al, PB
	and	al, 11111100b
	out	PB, al

	;Initialisation de es pour le jmp inter-segment
	;----------------------------------------------
	mov     ax,data
	mov     es,ax

	pop     ds
	pop     bx
	pop     ax
	jmp     es:dword ptr it23


gamme	dw      4561, 4305, 4063, 3835, 3620, 3417, 3225, 3044, 2873, 2712, 2560, 2416
	dw	2280, 2152, 2032, 1918, 1810, 1708, 1612, 1522, 1437, 1356, 1280, 1208
gamme2	dw	1140, 1076, 1016, 959, 905, 854, 806, 761, 718, 678, 640, 604


code    ends
end     start



boucle:

	mov	al, ds:[si]
	mov	ah, al
	shr	al, 1
	shr     al, 1
	shr     al, 1
	shr     al, 1

	xlat    table
	call	co
	mov	al, ah
	and	al, 0fh
	xlat	table
	call	co
	inc	si
	inc	dx

	mov	al,' '
	call	co

	and	dx,0fh
	jnz	suite


	mov 	al,CR
	call	co
	mov	al,LF
	call	co

suite:	loop	boucle

	pop	bp	; restaure bp

	ret	6
dump	endp


table	db	"0123456789ABCDEF"

code	ends


end
