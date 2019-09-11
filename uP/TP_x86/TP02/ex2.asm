
page    60,80
title   Exercice II



name    ex2


; Procedure de retour au dos
extrn   dos:far


pile    segment stack 'stack'   ;Ouverture et déclaration d'un segment de nom pile avec
				;l'attribut stack et le class name 'stack'
dw      100 dup (?)             ;On réserve 100 mots pour la pile.
pile    ends                    ;Fermeture du segment.

;               -----------------------------------------------

data    segment         ;Les directives "segment" et "ends" servent à définir une partie ou la
			;totalité d'un segment dont le nom est ici "data". Le contenu du segment
			;correspond aux instructions et/ou aux initialisations et réservations
			;de mémoire qui apparaissent entre "segment" et "ends".
i       db ?            ;Réservation mémoire pour une variable de nom "i" et de type byte.
j	db ?            ;
z	dw 1000		;

tab1    db 100 dup (?)
tab2    db 100 dup (?)
data    ends            ;Fermeture du segment de nom data.

;               ------------------------------------------------

code    segment         ;Ouverture d'un segment de nom "code".
assume  cs:code,ds:data ;La directive assume permet à l'assembleur de savoir quels sont les
			;segments pointés par les registres de segment pendant l'exécution des
			;instructions qui suivent cette directive assume. Ici, par cette
			;directive, le programmeur s'engage à ce que les registres CS et DS
			;pointent respectivement les segments de nom "code" et "data".

start:                  ;Utilisation d'une étiquette. Ici, "start" représente l'adresse de la
			;première instruction à exécuter. Cette étiquette est indispensable et
			;sera à nouveau utilisée avec la directive end.

mov     ax,data         ;Initialisation -indispensable- du registre DS conformément à ce qui a
mov     ds,ax           ;été déclaré ci-dessus avec la directive assume.

;i = 03
;*****
mov     i,03

;i++
;*****
inc i 			;incremente i

;Comparer j avec 26
;********************
cmp     j,26

;j=i
;******
mov     al,i
mov     j,al


;j=8 bits de poids fort de z
;*****************************
mov ax,z
mov j,ah


;DH=tab1(0)
;**********
mov dh,tab1[0]

;tab2(99) = 55h
;****************
mov tab2[99],55h


;Comparer tab1(i) avec 30
;*************************
mov bl,i
mov bh,0
cmp tab1[bx],30


;Comparer tab1(i) avec tab2(j)
;*******************************
mov bl,j
mov bh,0
mov al,tab2[bx]
mov bl,i
cmp tab1[bx],al

;CX=tab2(i)
;***********
mov cl,tab2[bx]  ; bx = i
mov ch,0

;tab2(13) = tab2(23)
;*********************
mov al,tab2[23]
mov tab2[13],al

;i = i multiplie par 4 en effectuant un decallage
;*************************************************
mov cl,2
shl i,cl

call    dos             ;Retour à MS-DOS.

code    ends            ;Fermeture du segment de nom "code"

			;La dernière d'un fichier source doit toujours correspondre à la
			;directive "end". Si, comme ici, il s'agit du programme principal
end     start           ;(main module), il faut spécifier l'adresse de départ, ici: "start".
