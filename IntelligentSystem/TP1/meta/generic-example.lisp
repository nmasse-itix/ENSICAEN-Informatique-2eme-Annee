;;;;
;;;; generic-example.lisp              ENSICAEN                       2006-02-01
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
;;;; Exported methods
;;;;


;;;
;;; Constructs a new class which represents a specific example.
;;; 
(defmethod build-class (name attributes)
  (let ((class nil))
    
    (setq class 
	  (clos:ensure-class name
		     ':direct-superclasses '(generic-example)
		     ':direct-slots (mapcar #'build-slot-definition 
					    attributes)
		     ':metaclass 'generic-example-class))
    
    ;; Sets the attributes list
    (write-attribute-names attributes class)
    
    ;; Sets the class attribute
    (write-class-attribute (car (last attributes)) class)
    class))

;;;
;;; Constructs a new example.
;;; 
(defmethod build-example (classname example attributes)
  (apply 'make-instance 
	 (cons classname (mapcan 
		         #'(lambda (att val) 
			           (list 
				     (intern (format nil "ATTRIBUTE-~s" att) 
					     "KEYWORD") 
				     val)) 
			 attributes 
			 example))))

;;;
;;; Returns the value of the requested attribute.
;;; 
(defmethod read-attribute ((name symbol)
			   (oself generic-example))
  
  (loop for slot in (clos:class-direct-slots (class-of oself)) 
	if (eql (clos:slot-definition-name slot) name)
	return (apply (car (clos:slot-definition-readers slot))
		      (list oself))))

;;; 
;;; Returns a set of the values of the requested attribute.
;;; 
(defmethod values-of-attribute ((name symbol)
			        (class generic-example-class))
  (second 
    (assoc name (read-attributes class))))



;;;;
;;;; Intern methods 
;;;;


;;; 
;;; This method is part of a reflex, it keeps up to date a set of all the 
;;; values of each attribute. 
;;;
;;; attribute: the attribute name
;;; value: the value of this attribute
;;; class: the class meta-object of this example
;;; 
;;; returns: nothing interesting
;;; 
(defmethod new-example ((attribute symbol) 
			value 
			(class generic-example-class))
  
  (let* ((attributes 
	   (read-attributes class)) 
	 (values 
	   (second (assoc attribute attributes))))

    (if values
      (if (not (member value values))
	(setf (second (assoc attribute attributes)) (cons value values)))
      (write-attributes (cons 
			  (cons attribute 
				(list (list value))) 
			  attributes)
			class))))

;;;
;;; This method is called when a new value is affected to a slot
;;;
(defmethod (setf clos:slot-value-using-class) :around
           (newvalue (class generic-example-class) object slot)
	   
  ;; reflex
  (new-example (clos:slot-definition-name slot) newvalue class)
  (call-next-method))


;;; 
;;; Establishes the class used to represent the slots 
;;; of a "generic-example-class" class.
;;; 
(defmethod clos:direct-slot-definition-class :around 
           ((instance generic-example-class) &rest other-args)
	   
  ;; a generic-example-direct-slot-definition is used for direct-slots
  (find-class 'generic-example-direct-slot-definition))
  
;;;
;;; Builds a slot definition using its name.
;;;
(defmethod build-slot-definition (name)
  (list 
    ':name name
    ':type 'symbol
    ;; Upper chars are important
    ':readers (list 
		(make-symbol (format nil "READ-ATTRIBUTE-~s" name)))
    ':initargs (list 
		(intern (format nil "ATTRIBUTE-~s" name) "KEYWORD"))))

;;;
;;; Prints a generic-example on a stream.
;;;
(defmethod print-object :around ((oself generic-example) fd)
  (format fd "[Example ~s: " (class-name (class-of oself)))
  (loop for slot in (clos:class-direct-slots (class-of oself)) do
	(format fd "~s " 
		(apply (car (clos:slot-definition-readers slot)) 
	        (list oself))))
  (format fd "]"))

