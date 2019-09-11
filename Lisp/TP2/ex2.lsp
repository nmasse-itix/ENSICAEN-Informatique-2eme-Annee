#|
 | #(@)ex2.lsp                  ENSICAEN                       2005-11-21
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
 | Exercices d'entrainement sur l'utilisation des fonctions d'ordre superieur.
 |#

#|
 | @version	21-11-2005
 |
 | @Fait:   tout
 |
 | @Afaire: -
 |#


#|
 | 1) Evaluer en sequence et tester les expressions suivantes :
 |#

; T car (a b) est une liste non vide.
(format t "(consp '(a b)) = ~s~%" (consp '(a b)) )

; NIL car () est une liste vide.
(format t "(consp '()) = ~s~%" (consp '()) )

; T car NIL est un atome.
(format t "(atom '()) = ~s~%" (atom '()) )

; T car NIL est un atome.
(format t "(atom ()) = ~s~%" (atom ()) )

; T car (a) n'a qu'un element.
(format t "(null (cdr '(a))) = ~s~%" (null (cdr '(a))) )

; ((1 2 A X) (3 4 B Y))
(format t "(mapcar 'append '((1 2) (3 4)) '((a) (b) (c)) '((x) (y) (z)) = ~s~%"
	(mapcar 'append '((1 2) (3 4)) '((a) (b) (c)) '((x) (y) (z)) ))

; ((1 2 . A) (3 . B))
(format t "(mapcar #'(lambda (x y) (append x y)) '((1 2) (3) (4 5 6)) '(a b)) = ~s~%" 
	(mapcar #'(lambda (x y) (append x y)) '((1 2) (3) (4 5 6)) '(a b)) )

; l = (A B C)
(setf l '(a b c))
(format t "~%") ; Saut de ligne
(format t "l = ~s~%" l)

; ((1 A) (2 B) (3 C) (4 A) (5 B))
(format t "(mapcar 'list '(1 2 3 4 5) (append l l)) = ~s~%"
	(mapcar 'list '(1 2 3 4 5) (append l l)) )

; (2 NIL 5)
(format t "(mapcar #'(lambda (u) (if (numberp u) u)) '(2 a 5)) = ~s~%"
	(mapcar #'(lambda (u) (if (numberp u) u)) '(2 a 5)) )

#|
 | 2) Evaluer, puis trouver les formes d'appel equivalentes avec "apply"
 |    ou avec "funcall" selon les cas.
 |#

(format t "~%") ; Saut de ligne
(setf addition '+)
(format t "addition = ~s~%" addition)
(format t "(funcall addition 2 3 4) = ~s~%" (funcall addition 2 3 4))
(format t "(apply addition '(2 3 4)) = ~s~%" (apply addition '(2 3 4)))

(format t "~%") ; Saut de ligne
(setf f #'(lambda (x y) (if (> x y) x y)))
(format t "f = ~s~%" f)
(format t "(funcall f 5 7) = ~s~%" (funcall f 5 7))
(format t "(funcall f 7 5) = ~s~%" (funcall f 7 5))
(format t "(apply f '(5 7)) = ~s~%" (apply f '(5 7)))
(format t "(apply f '(7 5)) = ~s~%" (apply f '(7 5)))


(format t "~%") ; Saut de ligne
(setf l '(list cons *))
(format t "l = ~s~%" l)
(format t "(apply (car l) '(a b c)) = ~s~%" (apply (car l) '(a b c)))
(format t "(funcall (car l) 'a 'b 'c) = ~s~%" (funcall (car l) 'a 'b 'c))

; ERREUR : cons n'admet que deux parametres
;(format t "(apply (cadr l) '(a b c)) = ~s~%" (apply (cadr l) '(a b c)))


(format t "~%") ; Saut de ligne
(setf m (list 'cons '*))
(format t "m = ~s~%" m)
(format t "(apply (cadr m) '(2 5)) = ~s~%" (apply (cadr m) '(2 5)))
(format t "(funcall (cadr m) 2 5) = ~s~%" (funcall (cadr m) 2 5))