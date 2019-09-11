#|
 | #(@)ex3.lsp                  ENSICAEN                       2005-11-21
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
 | Ex 3 : Ecriture de fonctions utilisant les fonctions d'ordre supérieur.
 |#

#|
 | @version	21-11-2005
 |
 | @Fait:   tout
 |
 | @Afaire: -
 |#


#|
 | Génère la liste des nombres entiers compris entre 0 (inclus)
 | et n (inclus)
 | 
 | @param nb la limite supérieure
 | @param liste la liste déjà générée (usage interne)
 |
 | @return la liste des nombres, en ordre
 |#
(defun genere (nb &optional(asc t) (liste NIL))
	(if (>= nb 0)
		(genere (- nb 1) asc
			(if asc
			  (cons nb liste)
			  (append liste (list nb))
			)
		)
		liste
	)
)


(format t "(genere 5 NIL) = ~s~%" (genere 5 NIL))
(format t "(genere 5 t) = ~s~%" (genere 5 t))

#|
 | Génère une liste de nombre entiers entre 0 (inclus) et n (inclus)
 | en commençant par les impairs en ordre décroissant et en finissant
 | par les pair en ordre croissant.
 |
 |#
(defun generel (nb)
    (append 
      (mapcan 
	#'(lambda (v) 
	 	(if (oddp v) 
		  (list v) 
		  NIL
		)
	)
	(genere nb nil)
      )
      (mapcan 
	#'(lambda (v) 
	    (if (evenp v) 
	      (list v) 
	      NIL
	    )
	) 
	(genere nb t)
      )
    )
)


(format t "(generel 5) = ~s~%" (generel 5))


#|
 | Effectue la somme S 
 | 
 | @param nb la limite supérieure
 |
 | @return la somme
 |#
(defun calcul (nb)
  (let ((l (genere nb t)))
   (apply '+ (mapcar '* l l l))
  )
)


(format t "(calcul 5) = ~s~%" (calcul 5))
(format t "(calcul 0) = ~s~%" (calcul 0))

#|
 | 3)
 | Prend 2 parametres : el et l1, où el est un objet Lisp quelconque
 | et l1 une liste de N objets, et retourne comme résultat une liste de
 | N+1 listes, chacune étant constituée de N+1 objets. Ces objets sont les
 | N objets de L plus l'objet X inséré à toutes les positions possibles 
 | dans L.
 |
 |#
(defun insert (el l1 &optional (l2 nil))
    (append 
      (list (append l2 (list el) l1))
      (if (consp l1)
	(insert el 
		(cdr l1) 
		(append l2 (list (car l1)) )
	)
      )
    )
)

(format t "(insert 'u '(a b c)) = ~s~%" (insert 'u '(a b c)))

#|
 | 4) 
 | La fonction PERMUTE prend en entrée une liste de N objets et renvoie
 | la liste de toutes les permutations de ces N objets.
 |
 |#
(defun permute (l &optional (lorig nil))
  (if (null lorig)
      (permute l l)
      (if (consp l)
        (append (insert (car l) (remove (car l) lorig)) (permute (cdr l) lorig))
      )
  )
)


(format t "(permute '(a b c)) = ~s~%" (permute '(a b c)))

#|
 |
 | 6) Cryptarithmetique
 |
 |#

(setq les-variables '(A B C D E F))
(setq variables-libres '(A B C))

(format t "les-variables = ~s~%" les-variables)
(format t "variables-libres = ~s~%" variables-libres)

(setq affect1
      '(if (and B C)
	 (setf F (mod 
		   (+ B C)
		   10
		 )
	 )
      )
)

(setq affect2
      '(if (and A B C)
	 (setf E (mod 
		   (+ A B (floor 
			    (+ B C) 
			    10
			  )
		   )
		   10
		 )
	 )
      )
)

(setq affect3
      '(if (and A B C)
	 (setf D (floor 
		   (+ A B (floor 
			    (+ B C) 
			    10
			  )
		   )
		   10
		 )
	 )
      )
)

(setq affectations (list affect1 affect2 affect3))
(format t "affectations = ~s~%" affectations)

(setq contr1 '(if A (/= A 0) t))
(setq contr2 '(if B (/= B 0) t))
(setq contr3 '(if D (/= D 0) t))
(setq contr4
      '(if (and A B C D E F) 
	 (/= A B C D E F)
      )
)

(setq contraintes (list contr1 contr2 contr3 contr4))
(format t "contraintes = ~s~%" contraintes)

(defun initialiser (var)
  (mapcar #'(lambda (v) (set v nil)) var)
)

(defun affecter (varl val aff)
  (progn 
    (mapcar #'(lambda (lv rv) (set lv rv)) varl val)
    (mapcar 'eval aff)
  )
)

(defun verifier (varl aff contr val)
  (affecter varl val aff)
  (every #'(lambda (v) (eval v)) contr)
)

(initialiser les-variables)

(format t "(verifier variables-libres affectations contraintes '(1 2 3)) = ~s~%" 
	(verifier variables-libres affectations contraintes '(1 2 3))
)

(defun possible (n)
  (if (= n 1)
    (mapcar 'list '(0 1 2 3 4 5 6 7 8 9))
    (mapcan #'(lambda (el)
		(mapcar #'(lambda (el2) (cons el2 el))
			'(0 1 2 3 4 5 6 7 8 9)
		)
	    )
	    (possible (- n 1))
    )
  )
)

(format t "(possible 1) = ~s~%" (possible 1))
(format t "(possible 3) = ~s~%" (possible 3))
    
(defun cryptarithmetique (varl aff contr)
  (mapcan
    #'(lambda (val) (if (verifier varl aff contr val) (list val)))
    (possible (length varl))
  )
)


(format t "(cryptarithmetique variables-libres affectations contraintes) = ~s~%"
	(cryptarithmetique variables-libres affectations contraintes)
)
