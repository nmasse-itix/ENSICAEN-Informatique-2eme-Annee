
extrn	co:far
public	dump

CR	equ	0dh
LF	equ	0ah





code	segment

	assume	cs:code

dump	proc	far
	push	bp		; sauve bp
	mov	bp, sp
	add	bp, 6		; bp pointe sur le dernier parametre

	mov	cx, [bp + 4]	; init du compteur de boucle avec la taille du tableau
	mov	si, [bp + 2]
	mov     ds, [bp]	; le segment es contient la zone a dumper
	mov	bx, offset table
	mov	dx, 0

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








