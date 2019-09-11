page    60,135
title   Interruption clavier


;               *************************************************
;               *                                               *
;               *     Assembleur 8086 sur PC     Exercice 10    *
;               *                                               *
;               *************************************************







name e10

extrn   ci:far ,co:far
extrn   dos:far


CNT53   equ     43h
TIM0    equ     40h
CNT59   equ     20h
COUNT	equ	100
PA_8255	equ	60h
PB_8255	equ	61h

pile    segment stack 'stack'
dw      50      dup (?)
pile    ends



data    segment
it9	dd	?	;Sauvegarde du vecteur d'interruption INT9 (clavier)
touche	db	?	;contenu du port a du 8255 (code touche frappee)
statkb	db	0	;flag, mis a 1 des qu'une touche est frappee
data    ends
;-------------------------------------------------------------------------------

code    segment
assume  cs:code,ds:data

start:  cli             ;Masquer l'entree INTR du 8086
	mov     ax,data
	mov     ds,ax   ;DS permet d'acceder aux variables du segment data


	;Sauvegarde des vecteurs d'interruption de MS-DOS
	;------------------------------------------------
	mov     al,9
	mov     ah,35h
	int     21h     ;Le vecteur d'interruption numero 9 est placé dans ES:BX
	mov     word ptr it9,bx
	mov     word ptr it9+2,es


	;Mise en place de nos propres vecteurs d'interruption
	;----------------------------------------------------
	push	ds

	mov     al,9h
	mov     bx,seg itclav
	mov     ds,bx
	mov     dx,offset itclav
	mov     ah,25h
	int     21h     ;Initialisation du vecteur numero 9 avec DS:DX

	pop	ds


	;Programmation du 8255 : gestion clavier
	;---------------------------------
	in	al, PB_8255
	and	al, 01111111b	;mise du bit 7 a 0
	or	al, 01000000b	;mise du bit 6 a 1
	out	PB_8255, al

	sti

	;Programme principal
	;-------------------

boucle:	call	key
	jnc	boucle
	call	co
	jmp	boucle




;                       ********************************************
;                       * Programme d'interruption clavier	   *
;                       ********************************************


itclav:

	push    ax
;	push    bx
;	push    cx
;	push    dx
;	push    si
;	push    di
	push    ds
;	push    es

	; Restitution du segment de donnees
	mov	ax,data
	mov	ds,ax

	; lire le code de la touche frappee
	in      al,PA_8255
	mov	touche,al

	mov	statkb,1

	; acknowledgememt
	in	al, PB_8255
	or	al, 10000000b
	out     PB_8255, al
	and	al, 01111111b
	out	PB_8255, al

	; envoi d'un EOI non specifique
	mov	al, 20h
	out	CNT59, al


	cmp	touche,1
	jne	nesc

	;Restitution des vecteurs d'interruptions de MS-DOS
	;--------------------------------------------------
	xor     ax,ax
	mov     es,ax           ;es=0 pour acceder à la table des vecteurs.
	mov     ax,data         ;ds pointe sur le segment data pour pouvoir acceder aux sauvegardes des vecteurs
	mov     ds,ax           ;des vecteurs d'interruption.

	push    ds
	lds     bx,it9          ;DS:BX = vecteur INT9 MS-DOS
	mov     es:[4*9h],bx
	mov     es:[(4*9h)+2],ds
	pop     ds


	call	dos



nesc:
;	pop     es
	pop     ds
;	pop     di
;	pop     si
;	pop     dx
;	pop     cx
;	pop     bx
	pop     ax
	sti
	iret



key	proc	near
	mov	al,statkb
	add	al,0FFh		; CF = 1 SSI statkb > 0
	jnc	nc
	mov	statkb,0
	mov	al,touche

nc:
	ret
key	endp


code    ends
end     start

