;;;;
;;;; packages.lisp                  ENSICAEN                       2006-02-01
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


;;;
;;; Packages definitions
;;;

(defpackage :net.homeip.nmasse.lisp.tp1.meta
  (:use :common-lisp)
  (:export :build-class
	   :build-example
	   :read-attribute
	   :generic-example
	   :values-of-attribute
	   :write-class-attribute
	   :read-class-attribute
	   :attribute-names))

(defpackage :net.homeip.nmasse.lisp.tp1.tree
  (:use :common-lisp 
	:net.homeip.nmasse.lisp.tp1.meta)
  (:export :load-examples
	   :build-tree
	   :decide))

