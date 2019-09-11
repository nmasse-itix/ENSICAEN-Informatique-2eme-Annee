name    ex7
extrn	dos:far
extrn	clrcrt:far
extrn	inicrt:far
extrn	ci:far

pile    segment stack 'stack'
dw      50 dup (?)
pile    ends




;Programme principal
;*******************


code segment

assume	cs:code

start:

	call	clrcrt
	call	inicrt
	mov	ds, dx		; l'extra segment correspond a la memoire ecran

	mov	ah, 07h		; AX = caractere a afficher
init:	mov 	si, 0		; SI = pointeur de colonne
	mov	bx, 0		; BX = pointeur de ligne
	mov	al, 0

debut:
	mov	[si+bx], ax	; Affichage du caractere

	add	si, 4		; Deux caracteres plus loin
	mov	cx, si
	cmp	cx, 160
	jne     non_saut
	add	bx, 320
	mov	si,0
non_saut:
	inc	al
	jnz	debut


	mov	cx,ax
	call	ci		; met une touche dans al
	cmp	al,1Bh
	je	fin
	mov	ax,cx

cbn:	cmp	ah,07h
	jne	cjb
	mov     ah,1Eh
	jmp     init

cjb:	cmp     ah,1Eh
	jne	cnr
	mov	ah,40h
	jmp	init

cnr:	cmp	ah,40h
	jne	cbccfgc
	mov	ah,0F9h
	jmp	init

cbccfgc:
	mov	ah,07h


	jmp	init

fin:
	call    dos

code    ends

end     start
