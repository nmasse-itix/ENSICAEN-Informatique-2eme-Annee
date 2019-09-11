page    60,135
title   Chronometre 25eme ligne


;               *************************************************
;               *                                               *
;               *     Assembleur 8086 sur PC     Exercice 8     *
;               *                                               *
;               *************************************************

name e8

extrn   ci:far ,co:far
extrn   inicrt:far
extrn   clrcrt:far

CNT53   equ     43h
TIM0    equ     40h
CNT59   equ     20h
COUNT	equ	100


pile    segment stack 'stack'
dw      50      dup (?)
pile    ends

data    segment
h10     db      '9'     ;Dizaine d'heure en ASCII
h       db      '9:'    ;Unité d'heure suivi de ':' en ASCII
m10     db      '5'     ;Dizaine de minutes en ASCII
m       db      '9:'    ;Unité de minute suivi de ':' en ASCII
s10     db      '5'     ;Dizaine de seconde en ASCII
s       db      '9'     ;Unité de seconde en ASCII

it8     dd      ?       ;Sauvegarde du vecteur d'interruption INT8 de MS-DOS
it23    dd      ?       ;Sauvegarde du vecteur d'interruption INT23H de MS-DOS

nit     db      1       ;Compteur d'interruption de type 8.
memvid	dw	?	;Segment de memoire video
data    ends
;-------------------------------------------------------------------------------

code    segment
assume  cs:code,ds:data

start:  cli             ;Masquer l'entree INTR du 8086
	mov     ax,data
	mov     ds,ax   ;DS permet d'acceder aux variables du segment data

	call    clrcrt  ;Effacer l'ecran
	call	inicrt
	mov	memvid,dx	;Memoire video

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

	sti

	;Programme principal
	;-------------------

always: call    ci
	jmp     always


;                       ************************************
;                       *  Programme d'interruption Timer  *
;                       ************************************

; Le temps affiché varie de 00:00:00 a 99:59:59, puis repasse a 00:00:00 une
;seconde plus tard.

ittim:  push    ax
	push    bx
	push    cx
	push    dx
	push    si
	push    di
	push    ds
	push    es

	mov     ax,data
	mov     ds,ax   ;Au cas ou ci modifie ds



	dec     nit     ;On n'intervient que toutes les secondes cad toutes les 100 IT
	jz      non_saut
	jmp	fin

non_saut:

	inc	s
	cmp	s, '9'
	jle	fin_inc
	mov	s, '0'
	inc	s10
	cmp	s10, '5'
	jle	fin_inc
	mov     s10,'0'
	inc	m
	cmp	m, '9'
	jle	fin_inc
	mov	m,'0'
	inc	m10
	cmp	m10, '5'
	jle	fin_inc
	mov	m10, '0'
	inc	h
	cmp	h, '9'
	jle	fin_inc
	mov     h,'0'
	inc	h10
	cmp	h10,'9'
	jle	fin_inc
	mov	h10,'0'


fin_inc:

	mov	es,memvid
	mov 	cx,8
	mov	bx,0
	mov	di,0
aff:    mov	al,[h10+di]
	mov	es:[3984+bx],al
	add	bx,2
	inc	di
	loop	aff


	mov	nit,COUNT

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

	call    clrcrt          ;Effacer l'ecran

	;Initialisation de es pour le jmp inter-segment
	;----------------------------------------------
	mov     ax,data
	mov     es,ax

	pop     ds
	pop     bx
	pop     ax
	jmp     es:dword ptr it23

code    ends
end     start

