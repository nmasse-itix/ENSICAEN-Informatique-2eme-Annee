name    ex6
extrn   dump:far
extrn	dos:far

pile    segment stack 'stack'
dw      50 dup (?)
pile    ends



data	segment

bidon           db 10 dup(55h)
test_dump       db 5  dup(00,01,02,03,04,05,06,07,08,09,0ah,0bh,0ch,0dh,0eh,0fh)
		db 5  dup(80h,81h,82h,83h,84h,85h,86h,87h,88h,89h,8ah,8bh,8ch,8dh,8eh,8fh)
test_end        db 55h

data	ends




;Programme principal
;*******************


code segment

assume	cs:code, ds:data

start:
	; appel de la procedure dump(segment, offset, taille)

	mov	ax, 160
	push	ax
	mov	ax, offset test_dump
	push	ax
	mov	ax, seg test_dump
	push	ax
	call    dump
	call    dos

code    ends

end     start
