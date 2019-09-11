;;;;
;;;; decision-tree.lisp               ENSICAEN              2006-02-01
;;;;
;;;; @author MASSE Nicolas (2005-Groupe4-LIMIN) <nicolas27.masse@laposte.net>
;;;; @author LIMIN Thomas (2005-Groupe4-MASSE) <thomas.limin@laposte.net>
;;;;
;;;; ENSICAEN
;;;; 6 Boulevard Marechal Juin
;;;; F-14050 Caen Cedex
;;;;
;;;; Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
;;;; reproduit, utilise ou modifie sans l'avis express de ses auteurs.

;;;;
;;;; Packages definitions
;;;;

(in-package :net.homeip.nmasse.lisp.tp1.tree)

;;;;
;;;; Exported methods
;;;;

;;;
;;; Retourne la meilleure destination pour un client
;;; suivant un arbre de décision donné
;;;
(defmethod decide (arbre client)
  (if (null (cdr arbre))
   ;; si la liste ne contient qu'un élement, alors une feuille est atteinte
   ;; et la destination toute trouvée => on retourne cette destination
   (car arbre)
   ;; sinon on lance l'évaluation du test d'un critère sur la liste des
   ;; valeurs possibles pour ce critère
   (evalueCritere (cdr arbre) client (car arbre))))


;;;;
;;;; Hidden methods
;;;;

;;;
;;; Pour un critère donné, evalue les clauses
;;; lorsque qu'une clause est vérifiée, la fonction decide
;;; est appelée su rle sous arbre correspondant
;;;
(defmethod evalueCritere (clauses client attribut)
  (cond
   ; si il ne reste plus de clauses, ben souci...
   ((null clauses) 
    (print "Souci, aucune possibilité ne correspond au client"))
   ; on evalue la première clause après substitution de la variable par la
   ; valeur fournie par le client, si elle est vraie on prend une décision
   ; sur le sous arbre
   ((eval (subst (trouveAttribut attribut client) :val-att (caar clauses) ))
    (decide (cadar clauses) client))
   (t 
     (evalueCritere (cdr clauses) client attribut))))


;;;
;;; Trouve pour un critère donné la valeur correspondant au client
;;;
(defmethod trouveAttribut (n l)
  (cond 
   ; si la liste est vide => echec de la recherche, retourne nil
   ((null l)
       nil)
   ; on teste le premier element (nom attribut) du premier
   ; couple nom / att de la liste
   ((eq (caar l) n) 
       (cadar l))
   ; si le premier couple de la liste n'est pas le bon, on relance
   ; récursivement trouveAttribut sur le reste de la liste
   (t
       (trouveAttribut n (cdr l)))))

