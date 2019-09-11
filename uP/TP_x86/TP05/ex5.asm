page 60,95
title Solution Exercice 5


;               ********************************************
;               *     SOLUTION DE L'EXERCICE NUMERO 5      *
;               ********************************************





; TODO  question 3, l'affichage du pourcentage n'est pas correct



name ex5

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
buffer  db      256 dup (?)     ;pour stocker les caracteres entres au clavier.
tablo	db	26 dup (0)      ;pour stocker le nombre d'occurences des lettres
cont	db	1		;continuer ?
max	db	0		;stockage du nombre d'occurences de caractere max
cmax	db	0		;caractere le plus tape
total	db	0		;nombre total de caracteres lus
data    ends


code    segment
assume  cs:code , ds:data, es:data

messag  db "Entrer une ligne:", CR, LF

start:  mov     ax,data
	mov     ds,ax           ;Initialisation de ds.
	mov	es,ax		;Initialisation de es.

deb_p:  call	raz
	mov	max,0
	mov	total,0

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



; comptage des caracteres
	cld	; clear direction flag
	mov	si,offset buffer
	mov	di,si

boucle:
	mov	ah,0
	lods	buffer
	cmp	al,61h
	jl	test_esc
	cmp	al,7Ah
	jg	test_esc
	sub	al,61h
	mov	bx,ax
	inc	tablo[bx]
	inc	total

	mov	al,max
	cmp	tablo[bx],al
	jle	suite

	; on a depasse le nb d'occurences max, maj de max
	mov	al,tablo[bx]
	mov	max,al
	add	bl,61h
	mov	cmax,bl

	jmp	suite

test_esc:
	cmp	al,1bH
	jne	suite
	mov	cont,0


suite:
	mov	ax,CR
	scas	buffer
	jnz	boucle


	call	aff
	call	prc


	cmp	cont,1
	je	deb_p

	call    dos


; affiche le tableau de stats
;
aff	proc near
	; BX = index dans le tableau
	; AX = Caractere a afficher
	; CX = variable de boucle (loop et rep)
	; DX = sauvegarde de CX

	mov	cx,length tablo

debut:	mov	bx,length tablo
	sub	bx,cx


	mov	dx,cx
	mov	ch,0
	mov	cl,tablo[bx]
	cmp	cl,0
	je	fin

	; normalisation
	push	dx
	mov 	ax,60
	mul	cx
	mov	dx,0
	mov	cl,max
	div	cx
	mov	cx,ax
	pop	dx

	cmp	cx,0
	je	fin

	mov	ax,bx
	add	ax,'a'
	call	co

	mov	ax,' '
	call	co

	mov	al,'*'
c_loop:	call	co
	loop	c_loop
	mov	al,CR
	call	co
	mov	al,LF
	call	co

fin:	mov	cx,dx	; restauration de CX

	loop	debut
	ret
aff	endp



raz	proc	near
	mov	cx,length tablo
	mov	bx,0

braz:
	mov	tablo[bx],0
	inc	bx
	loop	braz
	ret
raz	endp


; procedure d'affichage du pourcentage
prc	proc	near
	mov	al,max
	cmp	al,0
	je	aff_fin


	mov	al,cmax
	call	co
	mov	al,' '
	call	co

	mov	al,max
	mov	dl,100
	mul	dl      ; AX = AL * DL (nombre max * 100)

	mov	cl,total
	div	cl      ; AL = AX / CL ((nombre max * 100) / total)
	mov	ah,0    ; Mise a zero du reste

	cmp	al,100	; 100 % ?
	je	aff100

	mov	cl,10
	div	cl      ; Conversion en decimal

	add	al,30H	; Conversion en ASCII
	call	co

	mov	al,ah
	add	al,30H  ; Conversion en ASCII
	call	co
	jmp	aff_s

aff100:	mov	al,'1'
	call	co
	mov	al,'0'
	call	co
	mov	al,'0'
	call	co


aff_s:	mov	al,'%'
	call	co
	mov	al,CR
	call	co
	mov	al,LF
	call	co

aff_fin:
	ret
prc endp


; procedure de normalisation du tableau
normal proc near

	mov	cx,length tablo
	mov	bx,0
	mov	al,tablo[bx]
	mov	dx,0
bnorm:
	cmp	tablo[bx],al
	jle	pa_plus
	mov	al,tablo[bx]
	mov     dx,bx
pa_plus:
	inc	bx

	loop	bnorm

	; on a le nb d'occurence max dans al
	; et l'indice dans tablo de cet occurence max

	; maintenant parcours du tableau pour normaliser
	mov	cx,length tablo

bnorm2:


	ret
normal endp


code    ends

end     start

