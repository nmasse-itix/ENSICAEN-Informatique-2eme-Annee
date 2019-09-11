;;;;
;;;; classes.lisp                  ENSICAEN                       2006-02-01
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
;;;; Package definition
;;;;

(in-package :net.homeip.nmasse.lisp.tp1.meta)


;;;; 
;;;; Classes definition
;;;; 


;;;
;;; This slot meta-object implements a reflex in order to keep a set of 
;;; all the values of this slot
;;;
(defclass generic-example-direct-slot-definition 
          (clos:standard-direct-slot-definition)
  ()
  (:documentation "This slot meta-object implements a reflex in order to 
		  keep a set of all the values of this slot")
)

;;;
;;; This is a class metaobject, it allows reflexes when creating and 
;;; initializing the slots of its objects.
;;;
(defclass generic-example-class (standard-class) 
  ((attributes
    :reader		read-attributes
    :writer		write-attributes
    :initform		nil
    :documentation	"A map of attribute's names with a set 
    			of their values")
   (class-attribute
     :reader		read-class-attribute
     :writer		write-class-attribute
     :initform		nil
     :documentation	"The name of the attribute which holds the decision.")
   (att-names
     :reader		attribute-names
     :writer		write-attribute-names
     :initform		nil
     :documentation	"The list of all the attribute names."))
  (:documentation "This is a metaclass object."))

;;;
;;; Base class of all examples, its purpose is mainly type checking.
;;;
(defclass generic-example ()
  ()
  (:documentation ""))






