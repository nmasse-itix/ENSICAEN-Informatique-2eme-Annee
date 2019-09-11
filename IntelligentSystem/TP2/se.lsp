#|
 | #(@)se.lisp              ENSICAEN                       2006-02-01
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

(in-package :tp6)

(load "metaclos.lsp")


;;;; Définition de la classe attribut
(make-class attribut (unite) ( (demandable symbol ) (demande symbol) (but symbol ) (valeur)) "" ) 


;;;; Crée une instance d'attribut à partir des données présentes dans la
;;;; liste lst : (nom-attribut, booléen est-demandable?, booléen est-un-but?)
(defun make-attribute-from-list (lst)
  (make-instance 'attribut
		 :nom (car lst)
		 :demandable (cadr lst)
		 :but (caddr lst)
		 )
)


;;;; Charge dans l'environnement tous les attributs présents dans le fichier
;;;; nommé filename.
(defun load-attributes-from-file (filename)
  (let ((attribute nil))
    (with-open-file (fd filename :direction :input)
      (setq attribute (read fd nil 'eof))
      (loop until (eq attribute 'eof) do
	    (make-attribute-from-list attribute)
	    (setq attribute (read fd nil 'eof))))))


;;;; Définition de la classe règle
(make-class regle (unite) ( (declenchable symbol 'faux) (active symbol 'faux) (conditions list) (conclusions list)) "")


;;;; Crée une instance de règle à partir des données présentes dans la
;;;; liste lst : (nom-règle, liste-de-conditions, liste-de-conclusions)
(defun make-regle-from-list (lst)
  (make-instance 'regle
		 :nom (car lst)
		 :conditions (cadr lst)
		 :conclusions (caddr lst)))


;;;; Charge dans l'environnement toute les règles présentes dans le fichier
;;;; nommé filename.
(defun load-regles-from-file (filename)
  (let ((regle nil))
    (with-open-file (fd filename :direction :input)
      (setq regle (read fd nil 'eof))
      (loop until (eq regle 'eof) do
	    (make-regle-from-list regle)
	    (setq regle (read fd nil 'eof))))))


;;;; Associe un fait, c'est à dire une valeur connue d'un attribut à un
;;;; instant donné, a l'attribut correspondant => donne une valeur à un
;;;; attribut.
(defun set-attribut-avec-fait (lst)
  (setf (valeur (l-objet (car lst))) 
	(cadr lst)))


;;;; Associe aux attributs correspondants les fait présents dans le
;;;; fichier nommé filename.
(defun load-faits-from-file (filename)
  (let ((fait nil))
    (with-open-file (fd filename :direction :input)
      (setq fait (read fd nil 'eof))
      (loop until (eq fait 'eof) do
	    (set-attribut-avec-fait fait)
	    (setq fait (read fd nil 'eof))))))


;;;; Teste si la règle est déclenchable. C'est le cas si toute
;;;; les conditions de la règle sont vérifiées.
(defmethod regle-declenchablep ((oself regle))
  (if (not (eql (declenchable oself) 'vrai))
      (let
	  ((res t))
	(loop for x in (conditions oself) do
	  (setf res
		(and (condition-verifp x)
		     res)))
	(if res
	    (progn
	      (setf (declenchable oself)
		    'vrai)
	      (format t "Règle ~a déclenchable~%" (nom oself))
	      t)
	  (progn
	    (setf (declenchable oself)
		  'faux)
	    nil)))
    (not (eql 'vrai (active oself)))))


;;;; Vérifie si une condition est réalisée. C'est le cas lorsque l'attribut
;;;; cité dans la condition est valué et que sa valeur entraine la réalisation
;;;; de la condition.
(defun condition-verifp (condition)
  (if (eql 'non (car condition))
      ; regle négative
      (if (eql 'faux (valeur (l-objet (cadr condition))))
	  t
	nil)
      ; règle affirmative
      (if (eql 'vrai (valeur (l-objet (car condition))))
	  t
	nil)))


;;;; Ajoute dans la base de fait de l'environnement le fait apporté par le
;;;; parametre conclusion.
(defun appliquer-conclusion (conclusion)
  (let ((att nil) (val nil))
    (if (eql 'non (car conclusion))
	; fait négatif
	(progn	 
	  (setf att (l-objet (cadr conclusion)))
	  (setf val 'faux))
      	; fait affirmatif
      (progn
	(setf att (l-objet (car conclusion)))
	(setf val 'vrai)))
    (setf (valeur att) val)
    (format t " ~a: ~a" (nom att) val)
    (and (eql (but att) 'OUI) (eql val 'VRAI))))


;;;; Applique la règle (si elle n'est pas déjà active) => ajoute les faits
;;;; amenés par les conclusions de la règle.
(defmethod appliquer-regle ((oself regle))
  (if (regle-declenchablep oself)
      (let ((but nil))
	(format t "application de ~s: ~a =>" (nom oself) (conditions oself))
	(loop for x in (conclusions oself) do
	  (setf but (or
		    (appliquer-conclusion x)
		    but))
	  (setf (active oself)
	      'vrai))
	(format t "~%")
	(if but
	    (format t "la règle ~a a démontré un but~%" (nom oself)))
	but)))


;;;; Vérifie si l'attribut est demandable à l'utilisateur
(defmethod demandablep ((oself attribut))
  (and (not (eql 'VRAI (demande oself)))
       (eql 'OUI (demandable oself))))

;;;; Demande à l'utilisateur de donner une valeur a
;;;; l'attribut et retourne t si l'utilisateur a fourni une valeur
;;;; (par opposition à la valeur "je ne sais pas")
(defmethod demande-a-utilisateur ((oself attribut))
  (let ((rep nil)(rep-donnee nil))
    (loop until rep-donnee do
      (format t
	      "A votre avis l'attribut ~s est il \"vrai\" ou \"faux\" ou \"?\" => je ne sais pas ?~%"
	      (nom oself))
      (setf rep (read-line))
      (cond
       ((equal "vrai" rep)
	(setf (valeur oself) 'VRAI)
	(setf (demande oself) 'VRAI)
	(setf rep-donnee t))
       ((equal "faux" rep)
	(setf (valeur oself) 'FAUX)
	(setf (demande oself) 'VRAI)
	(setf rep-donnee t))
       ((equal "?" rep)
	(setf (valeur oself) nil)
	(setf (demande oself) 'VRAI)
	(setf rep-donnee t))))
    (not (equal "?" rep))))


;;;; Parcours la liste de règle à la recherche de règles applicables, et les
;;;; applique jusqu'à l'obtemption d'un but ou la saturation de la base de
;;;; faits (= plus de nouvelles règles applicables).
(defun moteur-inference ()
  ; parcours des règles pour voir celle qui sont applicables
  (let ((etat nil) (reg-dec nil) (but-demontre nil))
    (loop until etat do
      ; premier passage sur toutes les règles
      (dolist (re (les-instances 'regle))
	(if (regle-declenchablep re)
	    (progn
	      ; ajout de la règle sur la pile des règles déclanchables
	      (push re reg-dec))))

      ; application des règles déclenchables et vérification
      ; de la déclenchabilité des règle encore inactive
      (loop while (and (null etat) (consp reg-dec)) do
  	  ; utilisation & suppression du haut de la pile
	  (setf but-demontre (or (appliquer-regle (pop reg-dec)) but-demontre))
	  (dolist (re (les-instances 'regle))
	    (if (regle-declenchablep re)
		; ajout de la regle dans la liste des regle demandables
		(push re reg-dec))))
      (if but-demontre
	    (setf etat 'reussite)
	; demander un fait supplémentaire
	(let ((attrs nil) (attr nil) (rep nil))
	  (setf attrs (les-instances 'attribut))
	  (loop until (or etat rep) do
	    (setf attr (car attrs))
	    (setf attrs (cdr attrs))
	    (if (null attr)
		(setf etat 'echec)
	      (progn
		; recherche d'un attribut demandable
		(loop until (or etat (and (eql nil (valeur attr)) (demandablep attr))) do
		  (setf attr (car attrs))
		  (setf attrs (cdr attrs))
		  (if (null attr)
		      (setf etat 'echec)))
		(if (null etat)
		    (setf rep (demande-a-utilisateur attr)))))))))
    (cond
     ((eql 'reussite etat)
      (format t "RÉUSSITE: le but a été démontré~%"))
     ((eql 'echec etat)
      (format t "ÉCHEC: la base de fait est saturée ou les faits sont insuffisants~%")))))