;;;;
;;;; decision-tree-builder.lisp               ENSICAEN              2006-02-01
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
;;; Loads an examples' database
;;;
(defun load-examples (classname filename)
  (with-open-file (fd filename :direction :input)
    (let ((attributes 
	    (read fd))
	  (examples 
	    (read fd))
	  (example-set 
	    nil))
      
      ;; Makes a new class
      (setq example-set (make-instance 'example-set 
		        :class (build-class classname attributes)))

      ;; Builds examples
      (loop for ex in examples do
	    (add-example (build-example classname ex attributes)
			 example-set))
      
      example-set)))


;;;
;;; Builds the decision tree.
;;;
(defmethod build-tree ((examples example-set))
  (build examples (remove (read-class-attribute (read-class examples))
		 	  (attribute-names (read-class examples)))))


;;;;
;;;; Hidden methods
;;;;

;;;
;;; Compute the logarithm in base 2
;;;
(defun xlog2 (x)
  (if (eql x 0)
    0
    (* x 
       (/ (log x) 
	  (log 2)))))

;;;
;;; Computes the entropy of a set of examples distributed in
;;; N1, N2 ... examples of each class.
;;;
;;; nb-total:		number of examples.
;;; l-repartition:	the distribution of the examples in each class
;;; returns: 		the entropy of the set.
;;;
(defun compute-entropy ((nb-total integer) 
			(l-repartition list))
  (cond 
    ((null l-repartition) 0)
    ((= 0 nb-total) 1)
    (t  (+ (- (xlog2 (/ (car l-repartition) 
			nb-total))) 
	   (compute-entropy nb-total 
			    (cdr l-repartition))))))

;;;
;;; Computes the entropy of a list of examples.
;;;
;;; examples:		the list of examples
;;; returns:		the entropy of the set (between 0 et 1)
;;;
(defun entropy ((examples example-set))
  (if (consp (read-examples examples))
  	(compute-entropy
	   (length (read-examples examples))
	   (repartition (read-class-attribute (read-class examples)) examples))
	0))

;;; 
;;; Cuts the examples' set on the values of the specified attribute.
;;;
;;; exemples:		the example-set
;;; attribute:		the attribute on which we cut
;;; returns:		a list of sets
;;;
(defun cut ((examples example-set) 
	    (attribute symbol))
  
  (loop for val
	in (values-of-attribute attribute
				(read-class examples))
	collect (let ((tmp 
			(make-instance 'example-set 
				       :class (read-class examples)))) 
		  
		  (loop for ex 
			in (read-examples examples)
			do (if (eq val (read-attribute attribute ex))
			     (add-example ex tmp)))
		  tmp)))



;;; 
;;; Cuts the examples' set on the values of the specified attribute, 
;;; and computes the entropy of the resulting sets.
;;;
;;; exemples:		the example-set
;;; attribute:		the attribute on which we cut
;;; returns:		a list of sets
;;;
(defun entropy-after-cut ((examples example-set)
			  (attribute symbol))
  
  (let ((repartition nil)
	(nb-examples 0))
   
        (setq nb-examples 
	      (length (read-examples examples)))
	
	(setq repartition 
	      (loop for a-set
		    in (cut examples attribute)
		    collect (repartition (read-class-attribute (read-class a-set)) 
					 a-set)))

	(loop for p 
	      in repartition
	      sum (* (/ (apply '+ p)
			nb-examples) 
		     (apply  'compute-entropy
			     (cons (apply '+ p) (list p)))))))

;;;
;;; Builds the decision tree 
;;;
(defun build ((examples example-set)
	      (l-natt list))
  (cond
    ; If the entropy is 0, then it's a leaf
    ((= 0 (entropy examples))
       (format t "<decision = ~s>~%" 
	       (read-attribute (read-class-attribute (read-class examples)) 
			       (car (read-examples examples))))
       (list (read-attribute (read-class-attribute (read-class examples))
			       (car (read-examples examples)))))
    (t 
      (let ((attMin nil) 
	    (mini 1))
	
      	(loop for cut
	      in l-natt
	      do (let ((entropy nil))
		   (setq entropy
			 (entropy-after-cut examples cut))
		   (if (> mini entropy)
		     (progn
		       (setq attMin cut)
		       (setq mini entropy)))))
	(let ((tree nil))
	    ; Attribute 
	    (format t "<attribute = ~s, entropy = ~s>~%" 
		    attMin
		    mini)
	    (setq tree
		  (cons attMin
			(loop for i 
			      in (cut examples attMin) 
			      collect (progn
					(format t "<value = ~s>~%" 
						(read-attribute attMin (car (read-examples i))))
					(list (list 'equal 
						    :val-att 
						    (string (read-attribute attMin (car (read-examples i)))))
					      (build i (remove attMin l-natt)))))))
	    tree)))))
  
;;;
;;; Saves the tree in a file.
;;;
(defun save-tree ((tree list) 
		  (file string))
  
  (with-open-file (fd file :direction :output)
    (format fd "~s" tree)))


