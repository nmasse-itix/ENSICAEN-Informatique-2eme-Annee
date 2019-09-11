 #|
 | #(@)nomfichier.c              ENSICAEN                       2005-11-21
 |
 | @author MASSE Nicolas (2005-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
 | @author LIMIN Thomas (2005-Groupe4-MASSE) <thomas.limin@laposte.net>
 |
 | ENSICAEN
 | 6 Boulevard Marechal Juin
 | F-14050 Caen Cedex
 |
 | Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 | reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 |#

#|
 | TP n° 1 de Programation symbolique
 |#

#|
 | @version	1.0.0
 |
 | @Fait:  -
 |
 | @Afaire: énoncé
 |#


#| CAR = Content of Address Register
 | First element of list
 | Also named FIRST
 |#
(print (car '(p h w)))             ; P

#| CDR = List minus the first element
 | Also named REST
 |#
(print (cdr '(b a c d)))           ; (A C D)

(setq x '((anne emma) (marc michel)))
(print (first x))                  ; (ANNE EMMA)
(print (rest x))                   ; ((MARC MICHEL))
(print (first (rest x)))           ; (MARC MICHEL)
(print (rest (first x)))           ; (EMMA)
(print (rest (first (rest x))))    ; (MICHEL)
(print (first (rest (first x))))   ; EMMA

#| ((a b) (c d) (e f)) => Y |#
(setq y '((a b) (c d) (e f)))

(print (cadadr y))                 ; D
(print (caaddr y))                 ; E
#| Doesn't function, because CAR performed on non-list argument, replace by CADR 
 | (print (caadr '(cdr y)))
 |#

#| CDDR is not a list, so CAAR cannot perform on it, replace by CAR
 | (print (caar '(cddr y)))
 |#

; the list following the quote is handled as data 
(print (car '(caddr ((a b) (c d) (e f)))))  ; CADDR
(print '(car (car (cdr (cdr y)))))          ; (CAR (CAR (CDR (CDR Y))))

#|
 | Ex 2
 |#

(print (caddr '(a b c d) ))
(print (caadr '((a b) (c d)) ))
; CAADDAR is not defined (too long) 
(print (car (caddar '(((a) (b) (c) (d))) )))
(print (caaddr '((((a))) ((b)) (c) d) ))
(print (cadar '((((a) b) c) d) ))

#|
 | Ex 3
 |#

; (A B) => L
(print (setq l '(a b)))

(print (append l l))                  ; (A B A B) 
;(print (append 'l l))                  L is not a list
(print (append l 'l))                 ; (A B . L)        

(print (car (cons 'a '(b c))))        ; A
(print (cdr (cons 'a '(b c))))        ; (B C)
(print (cons (car l) (cdr l)))        ; (A B)

(print (cons (car nil) (cdr nil)))    ; (NIL) because of (car nil)
(print (cons l l))                    ; ((A B) A B)
(print (cons 'l l))                   ; (L A B)

#|
 | Ex 4
 |#
(print (cons '(a b x) '()))           ; ((A B X))
(print (append '(a b) '(c d)))        ; (A B C D)
(print (list l l))                    ; ((A B) (A B))
(print (cons 'l l))                   ; (L A B)
(print (list '(a b c) '()))           ; ((A B C) NIL)
(print (append '(a b c) '()))         ; (A B C)
(print (cons '(a b) '(c d)))          ; ((A B) C D)


#|
 | Ex 5
 | a)
 |#
(defun decale (liste) 
	(append (cdr liste) 
		(list (car liste))
	)
)
(print (decale '(a b c d)))          ; (B C D A)


#|
 | Ex 5
 | b)
 |#
(defun inverse (liste) 
	(if (NULL liste) 
		NIL 
		(append 
			(inverse (cdr liste)) 
			(list (car liste))
		)
	)
)

(print (inverse '(a b c d)))         ; (D C B A)
(print (inverse NIL))                ; NIL


#|
 | Ex 5
 | c)
 | Calculer la liste formée par la répétition inverse d'une liste
 |#
(defun duplique (liste)
	(let ((inv_liste (inverse liste)))
	  (append inv_liste inv_liste)
	)
)

(print (duplique '(a b c d)))


#|
 | Ex 5
 | d)
 | the list following "&optional" defines the name of the parameter
 | and its default value
 |#
(defun nbatome (liste &optional (nb 0))
  (if (null liste)
    nb ; terminal recursivity
    (nbatome (cdr liste)
	     (if (atom (car liste))
		 (+ 1 nb)
		 nb
	     )
    )
  )
)

(print (nbatome '(a b c (2) r (3) s)))


#|
 | Ex 5
 | e)
 | Calculer la liste composée du premier et du dernier élément d'une liste
 |#
(defun premder (liste)
	(let ((fin (cdr (cdr liste))))
	(if (NULL fin) 
		liste
		(premder (cons (car liste) (cdr (cdr liste)))))
	)
)

(print (premder '(76 45 34 90 2 9 4 8 56 4 2 87)))


#|
 | Ex 5
 | f)
 | Calcul du PGCD
 |#
(defun pgcd (p q)
  (if (= q 0)
    p
    (pgcd q (rem p q))
  )
)

(print (pgcd 23 21))
(print (gcd 23 21))

(print (pgcd 24 15))
(print (gcd 24 15))


#|
 | Ex 5
 | g)
 | Suite de Syracuse 
 |#
(defun syra (un)
  (progn 
    	(print un)
  	(if (= un 1)
   	  ()
  	  (syra 
  	    (if (evenp un)
  	    	(/ un 2)
  	    	(+ 1 (* 3 un))
  	    )
  	  )
  	)
  )
)

;(print "U0 = ")
;(syra (read))


#|
 | Ex 5
 | h)
 | Vérifier qu'un mot éclaté en liste est un palyndrome
 |#
(defun palindromep (liste) (equal liste (inverse liste)))

(print (palindromep '(e s o p e r e s t e e t s e r e p o s e) ))
(print (palindromep '(b a t e a u) ))


#|
 | Ex 5
 | i)
 | Construire la liste décroissante des n premiers entiers positifs ou nuls
 |#
(defun genere (nb &optional(liste NIL))
	( if (>= nb 0)
		(genere (- nb 1) (append liste (list nb)))
		liste
	)
)

(print (genere 10 ))


#|
 | Ex 5
 | j)
 | Determiner le nombre médian de 3 nombres
 |#
(defun median (n1 n2 n3)
	(max (max (min n1 n2) (min n2 n3)) (min n3 n1))
)

(print (median 1 2 3 ))
(print (median 2 3 1 ))
(print (median 3 1 2 ))

#|
 | Ex 5
 | k)
 | Returns the list of the different elements
 |#
(defun diff (liste)
  (if (null liste)
    ()
    (if (member (car liste) (cdr liste))
      (diff (cdr liste))
      (cons (car liste) (diff (cdr liste)))
    )
  )
)

(print (diff '(6 4 9 10 3 6 2 9 3 3 4)))


#|
 | Ex 5
 | l)
 | Trier une liste dans l'ordre croissant
 |#
(defun inserer (liste nb)
  (if (null liste)
    (list nb)
    (if (> (car liste) nb)
      (cons nb liste)
      (cons (car liste) (inserer (cdr liste) nb))
    )
  )
)
(defun trier (liste &optional(res NIL))
  (if (null liste)
    res
    (progn 
      (trier (cdr liste) (inserer res (car liste)))
    )
  )
)


(print (trier '(2 3 10 9 4 6)))
       
#|
 | Ex 5
 | m)
 | Calculer l'histogramme d'une liste de nombre, c'est à dire le nombre d'occurences de chaque nombre
 |#
(defun addoccur (dat nb)
  (if (null dat)
    (list (list nb 1))
    (if (= (caar dat) nb)
      (cons (list nb (1+ (cadar dat))) (cdr dat))
      (if (> (caar dat) nb)
    	(cons (list nb 1) dat)
	(cons (car dat) (addoccur (cdr dat) nb))
      )
    )
  )
)
(defun histo (liste &optional(dat NIL))
  (if (null liste)
    dat
    (histo (cdr liste) (addoccur dat (car liste)))
  )
)

(print (histo '(6 4 9 10 3 6 2 9 3 3 4)))

#|
 | Ex 5
 | n)
 | Se servir de cet histogramme pour calculer le nombre médian de cette liste.
 |#
(defun median (liste &optional(nb NIL))
  (if (null nb)
    (median (histo liste) (/ (length liste) 2))
    (if (<= nb (cadar liste))
      (caar liste)
      (median (cdr liste) (- nb (cadar liste)))
    )
  )
)

(print (median '(6 4 9 10 3 6 2 9 3 3 4)))

