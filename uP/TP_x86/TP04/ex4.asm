page 60,95
title Solution Exercice 4


;               ********************************************
;               *     SOLUTION DE L'EXERCICE NUMERO 4      *
;               ********************************************


name ex4

extrn   dos : far
extrn	co : far
extrn   read:far, write:far

CR      equ     0dh             ;Code ASCII de carriage return
LF      equ     0ah             ;Code ASCII de line feed

pile    segment stack 'stack'
dw      20      dup (?)
pile    ends


data    segment
bidon   db      "ERREUR"        ;Ne sert à rien dans le cadre de cet exercice.
buffer  db      132 dup (?)     ;pour stocker les caracteres entres au clavier.
data    ends


code    segment
assume  cs:code , ds:data, es:data

messag  db "Entrer une ligne:", CR, LF

start:  mov     ax,data
	mov     ds,ax           ;Initialisation de ds.
	mov	es,ax		;Initialisation de es.

	mov     ax,seg messag
	push    ax
	mov     ax,offset messag
	push    ax              ;passage de parametres avant l'appel de la
				;procedure WRITE.

	call    write

	mov     ax,seg buffer
	push    ax
	mov     ax,offset buffer
	push    ax              ;passage de parametres avant l'appel de READ


	call    read



; recherche de CR
	cld	; Flag D = 0
	mov cx, length buffer ; CX = nombre d'elements dans le buffer
	mov di, offset buffer ; DI = offset buffer
	mov al, CR
	repnz scas buffer


	mov si,di
	dec si
	mov ax,di
	sub ax, offset buffer
	mov cx, ax

	std
boucle:	lods buffer
	call co
	loop boucle



	call    dos

code    ends

end     start

