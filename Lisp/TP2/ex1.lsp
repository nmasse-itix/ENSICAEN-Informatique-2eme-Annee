#|
 | #(@)ex1.lsp                  ENSICAEN                       2005-11-21
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
 | Exercices avec parcours de listes, en profondeur et à tous les niveaux
 |#

#|
 | @version	21-11-2005
 |
 | @Fait:   tout
 |
 | @Afaire: -
 |#



#|
 | Rappel
 | a)
 | Parcours d'une liste à un niveau avec affichage des éléments
 |#
(defun parcours1N (l)
  ( if (null l)
      ()
      (progn
        (print (car l))
	(parcours1N (cdr l))
      )
  )
)


(print "Parcours de (8 ((7 6) (5 4)) 3 (2 1))) à 1 niveaux avec affichage des éléments")
(parcours1N '(8 ((7 6) (5 4)) 3 (2 1)) )

#|
 | Rappel
 | b)
 | Parcours d'une liste à tous les niveaux avec affichage des atomes
 |#
(defun parcours (l)
  (cond 
    ((null l)
      ()
    )
    ((atom (car l))
      (print(car l))
      (parcours (cdr l))
    )
    (t
      (parcours (car l))
      (parcours (cdr l))
    )
  )
)

(print "Parcours de (8 ((7 6) (5 4)) 3 (2 1))) à tous les niveaux avec affichage des atomes")
(parcours '(8 ((7 6) (5 4)) 3 (2 1)) )


#|
 | 1)
 | Ecrire une fonction inversant une liste à tous les niveaux
 |#
(defun inverse (l)
  (cond
    ((null l)
      ()
    )
    ((atom (car l))
      (append (inverse (cdr l)) (list (car l)))
    )
    (t
      (append (inverse (cdr l)) (list (inverse (car l))))
    )
  )
)

(print "Inversion de ( 8 ((7 6) (5 4)) 3 (2 1)))")
(print (inverse '(8 ((7 6) (5 4)) 3 (2 1)) ) )


#|
 | 2)
 | Ecrire une fonction calcul profondeur prenant une expression en argument
 | et retournant le nombre de niveaux qu'elle comporte
 |#
(defun calcul_profondeur (expr)
  (cond
    ((null expr)
      0
    )
    ((atom (car expr))
      (max 1 (calcul_profondeur (cdr expr)))
    )
    (t
      (max (+ 1 (calcul_profondeur (car expr))) (calcul_profondeur (cdr expr)))
    )
  )

)

(print "Calcul de profondeur de ( 8 ((7 (6 6)) (5 4)) 3 (2 1)))")
(print (calcul_profondeur '(8 ((7 (6 6)) (5 4)) 3 (2 1)) ) )


#| 
 | 3)
 | Ecrire la fonction oter-pred à 2 arguments:
 |	une prédicat
 |	une liste quelconque
 | donnant comme résultat la liste de laquelle sont enlevés tous les objets
 | satisfaisant au prédicat
 |#
(defun oter-pred (pred liste)
  (cond
    ((null liste)
      ()
    )
    ((atom (car liste))
      ( if (funcall pred (car liste))
        (cons (car liste) (oter-pred pred (cdr liste)))
	(oter-pred pred (cdr liste))
      )
    )
    (t
      (cons (oter-pred pred (car liste)) (oter-pred pred (cdr liste)))
    )
  )
)


(print "Oter de ( 8 ((7 (6 6)) (5 4)) 3 (2 1))) les objets satisfaisant: objet > 3")

(defun pre1 (o)
 (> o 3)
)

(print (oter-pred 'pre1 '(8 ((7 (6 6)) (5 4)) 3 (2 1))  ) )

