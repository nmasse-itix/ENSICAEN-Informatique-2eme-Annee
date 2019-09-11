#|
 | #(@)ex1.lsp                 ENSICAEN                       2005-12-05
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
 |#


#|
 | @version	2006
 |
 | @Fait	-
 |
 | @Afaire	-
 |#


#|
 | b) Passage d'un mot (symbole) à une liste de caractères
 |
 | @param mot		le mot à exploser
 | @return		une liste de symbole: 1 par caracère du mot
 |#
(defun explode (mot)
    (loop for x from 0 to (- (length(string mot)) 1)
        collect  
            (read-from-string (string (elt (string mot) x)))
    )
)

(format t "(explode \'test) = ~s~%" (explode 'test))

#|
 | a) Représentation pour la grille et les mots:
 |
 | Les mots disponibles sont dans une liste. La grille est repésentée par
 | une liste de noms de liste de caractères, chaque liste de caracteres devant
 | correspondre à un mot.
 |
 | Les contraintes sont exprimées comme suit:
 | (equal (nth 2 lig1) (nth 1 col1))
 |#
(setq 
 lig1 '(()()()()())
 lig2 '(()()()()()())
 col1 '(()()()()())
 col2 '(()()()()())
 l_mots (mapcar 'explode '(arbre simple savante sage vague agile legere varie))
)

(setq grille '(lig1 lig2 col1 col2))

(format t  "grille = ~s~%" grille)
(format t  "lig1 = ~s~%" lig1)
(format t  "lig2 = ~s~%" lig2)
(format t  "col1 = ~s~%" col1)
(format t  "col2 = ~s~%" col2)


#|
 | c) Représenter les contraintes liées à cette grille sous forme de liste
 |#
(setf contraintes
      '(
	(if (and (nth 2 lig1) (nth 1 col1)) (equal (nth 2 lig1) (nth 1 col1)) t)
	(if (and (nth 1 lig2) (nth 4 col1)) (equal (nth 1 lig2) (nth 4 col1)) t)
	(if (and (nth 4 lig2) (nth 2 col2)) (equal (nth 4 lig2) (nth 2 col2)) t)
       )
)



#|
 | d) Fonction permettant de placer un mot dans la grille
 |
 |#
(defun placer (emplacement mot)
  (if (equal (length (eval emplacement)) (length mot))
      (progn 
	(format t "Mot placé: ~s = ~s~%" emplacement mot) 
	(set emplacement mot) ; on utilise un set car il faut evaluer "emplacement"
	t ; ne pas oublier la valeur de retour
      )
      nil
  )
)

#|
 | remplace le mot par une liste de nil
 |
 | @param emplacement	le mot a réinitialisé
 | @return		nil
 |#

(defun reinit (emplacement)
  (format t  "Effacement de ~s, ancienne valeur = ~s~%" emplacement (eval emplacement))
  
  ; on utilise un set car il faut evaluer "emplacement"
  (set emplacement (loop for x in (eval emplacement) collect nil))

  nil ; la valeur de retour
)


#|
 | e) Écrire la fonction permettant de vérifier que la grille est correctement remplie
 |
 | @param c		la liste contraintes
 | @return		validité des contraintes
 |#
(defun verifier (c)
  (if (consp c)
      (and 
	(eval (eval (car c))) ; TODO : expliquer le double eval
	(verifier (cdr c))
      )
      t
  )
)

; Doit retourner t car la grille est vide
(format t "(verifier contraintes) = ~s~%" (verifier contraintes))

#|
 | f) Fonction permettant de trouver la solution par un mecanisme de type
 | "essai systematique de toutes les configurations" avec backtrack. 
 |
 | @param rangees	une liste des noms des rangees de la grille
 | @param mots		
 |#

(defun chercher (rangees mots)
  (cond
    ((null mots) ; Plus de mots a essayer ?
      (format t "[BACKTRACK]~%")
      (reinit (car rangees)) ; On efface la rangee
    )
    
    ((null rangees) ; Plus de rangees a remplir ?
       (progn 
	  (format t "Solution = ~a~%" (mapcar 'eval grille)) ; On a la solution !
	  t
       )
     )
    
    (t ; Cas par defaut
       (if (and ; On doit pouvoir placer le mot (verification de la longueur)
	        (placer (car rangees) (car mots))
	        ; ET les contraintes de la grille doivent etre verifiees
	        (verifier contraintes))
       ;then
	  (progn
	    (format t "[FORWARD]~%")
	    
	    ; Le mot est place, mais peut on remplir les colonnes suivantes ?
	    (if (chercher (cdr rangees) l_mots) 
	    ;then
	      t ; Oui
	    ;else
	      (chercher rangees (cdr mots))
	    ;endif
	    )
	    
	  ;endprogn
	  )
       ;else
	    (chercher rangees (cdr mots))
       ;endif
       )
    )

  ;endcond
  )
)


(chercher grille l_mots)

