;;;;
;;;; example-set.lisp                  ENSICAEN                  2006-02-01
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

;;;
;;; Adds an example to this example-set.
;;; 
(defmethod add-example ((example generic-example)
			(oself example-set))
  
  (write-examples 
    (cons example (read-examples oself))
    oself))

;;;
;;; Prints an example-set on the specified stream.
;;;
(defmethod print-object :around ((oself example-set)
				 fd)
  (loop for ex in (read-examples oself) do
        (format fd "~s~%" ex)))

;;;
;;; Computes the repartition of the examples after
;;; a cut on the specified attribute
;;;
(defmethod repartition ((attribute symbol)
			(oself example-set))
  (loop for value
	in (values-of-attribute attribute 
				(read-class oself))
	collect (loop for ex
		      in (read-examples oself)
		      count (eql (read-attribute attribute ex)
				 value))))

