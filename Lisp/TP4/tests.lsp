#|
 | #(@)tests.lsp              ENSICAEN                       2006-01-09
 |
 | @author MASSE Nicolas <nicolas27.masse@laposte.net>
 | @author LIMIN Thomas  <thomas.limin@laposte.net>
 |
 | ENSICAEN
 | 6 Boulevard Marechal Juin
 | F-14050 Caen Cedex
 |
 | Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
 | reproduit, utilise ou modifie sans l'avis express de ses auteurs.
 |#

#|
 | Ce fichier aide à la compréhension du modèle objet de LISP.
 |#


#|
 | version:	0.0.1
 |
 | done:	-
 |
 | todo:	-
 |#

(defclass plat () ())

(defmethod cuisiner ((x plat))
  (format t "Preparer un plat~%")
)

(defmethod cuisiner :before ((x plat))
  (format t "Un plat va etre cuisine~%")
)

(defmethod cuisiner :after ((x plat))
  (format t "Un plat a ete cuisine~%")
)

(defclass tarte (plat)
  ((garniture :reader lire-garniture :writer changer-garniture :initarg :garniture :initform '(poire)))
)

(defmethod cuisiner ((x tarte))
  (format t "Preparer une tarte a ~s~%" (lire-garniture x))
  (changer-garniture (cons 'cuite (lire-garniture x)) x)
)

(defmethod cuisiner :before ((x tarte))
  (format t "Une tarte a ~s va etre cuisinee~%" (lire-garniture x))
)

(defmethod cuisiner :after ((x tarte))
  (format t "Une tarte a ~s a ete cuisinee~%" (lire-garniture x))
)

(defclass tarte-tatin (tarte)
  ()
)

(defmethod cuisiner :around ((x tarte-tatin))
  (format t "Preparation d'une tarte tatin :~%")
  (call-next-method)
)


(setq plat-1 (make-instance 'plat))
(cuisiner plat-1)

(format t "~%")

(setq tarte-1 (make-instance 'tarte))
(cuisiner tarte-1)

(format t "~%")

(setq tarte-2 (make-instance 'tarte-tatin :garniture '(pomme)))
(cuisiner tarte-2)
