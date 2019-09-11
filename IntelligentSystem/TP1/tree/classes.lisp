;;;;
;;;; classes.lisp                  ENSICAEN                  2006-02-01
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
;;;; Class definitions
;;;; 

(defclass example-set ()
  ((examples
     :type		list
     :initform		nil
     :reader		read-examples
     :writer		write-examples
     :initarg		:examples
     :documentation	"A set of examples.")
   (class
     :initform		nil
     :reader		read-class
     :initarg		:class
     :documentation	"The class metaobject of the examples."))
  (:documentation	"Represents a set of examples."))


