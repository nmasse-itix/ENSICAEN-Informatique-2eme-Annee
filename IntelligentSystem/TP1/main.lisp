;;;;
;;;; main.lisp                  ENSICAEN                       2006-02-01
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
;;; Main program
;;;

;; Load package definitions
(load "packages.lisp")

;; Load MOP stuff
(load "meta/main.lisp")

;; Load decision tree stuff
(load "tree/main.lisp")


;; Imports package
(use-package :net.homeip.nmasse.lisp.tp1.tree)



;;;
;;; Decision trees
;;;



;;
;; Example database "METEO-TP"
;;
(let ((weather-db nil)
      (weather-tree nil)
      (q1 nil)
      (q2 nil))

  (format t ">>> Example database : METEO-TP~%~%")
  (setq weather-db 
	(load-examples 'meteo-tp "examples/meteo-tp.txt"))
  (print weather-db)

  (format t ">>> Decision tree : METEO-TP~%~%")
  (setq weather-tree 
	(build-tree weather-db))
  (print weather-tree)
  (format t "~%~%>>> End of decision tree : METEO-TP~%~%")
  
  (format t ">>> Queries : METEO-TP~%~%")
  (setq q1
	'((aspect-ciel "PLUVIEUX") (venteux "VRAI")))
  (setq q2
	'((aspect-ciel "NUAGEUX")))
  
  (loop for q
	in (list q1 q2)
	do (format t ">>> The query : ~s returned : ~s~%" 
		   q
		   (decide weather-tree q)))

  (format t "~%>>> End of queries : METEO-TP~%~%"))





;;
;; Example database "CARD"
;; 
(let ((card-db nil)
      (card-tree nil))

  (format t ">>> Example database : CREDIT-CARD~%")
  (setq card-db 
	(load-examples 'credit-card "examples/carte-credit.txt"))
  (print card-db)

  (format t "~%>>> Decision tree : CREDIT-CARD~%~%")
  (setq card-tree 
	(build-tree card-db))
  (print card-tree)
  (format t "~%~%>>> End of decision tree : CREDIT-CARD~%~%"))


;;
;; Example database "BANK"
;;
(let ((bank-db nil)
      (bank-tree nil))

  (format t ">>> Example database : BANK~%")
  (setq bank-db 
	(load-examples 'bank "examples/banque.txt"))
  (print bank-db)

  (format t "~%>>> Decision tree : BANK~%~%")
  (setq bank-tree 
	(build-tree bank-db))
  (print bank-tree)
  (format t "~%~%>>> End of decision tree : BANK~%~%"))



;;;
;;; Arbre de decision "Voyage"
;;;
(let ((arbre nil)
      (client1 nil)
      (client2 nil)
      (client3 nil)
      (client4 nil)
      (client5 nil)
      (client6 nil))
  
  (setq arbre '(preference 
		 ((equal :val-att "sport") (Alpes))
		 ((equal :val-att "detente") 
		  (budget ((< :val-att 10000) (Espagne))
			  ((and (>= :val-att 10000) 
				(<= :val-att 20000)) (Antilles))
			  (( > :val-att 20000) (Seychelles))))
		 ((equal :val-att "culture") 
		  (age ((<= :val-att 30)(Mexique))
		       ((> :val-att 30) (Egypte))))))


  ; un client pour les Alpes
  (setq client1 
        '((age 25) (preference "sport")))
  
  ; un client pour l'Espagne
  (setq client2 
        '((age 35) (preference "detente") (budget 9000)))
  
  ; un client pour les Antilles
  (setq client3 
        '((age 35) (preference "detente") (budget 20000)))
  
  ; un client pour les Seychelles
  (setq client4 
        '((age 35) (preference "detente") (budget 20001)))
  
  ; un client pour le Mexique
  (setq client5 
        '((age 23) (preference "culture") (budget 9000)))
  
  ; un client pour l'Egypte
  (setq client6 
        '((age 42) (preference "culture") (budget 9000)))
  
  (loop for client
	in (list client1 client2 client3 client4 client5 client6)
	do (format t 
		   ">>> Le client dont les preferences sont : ~%~s~%>>> decide d'aller a :~%~s~%~%" 
		   client
		   (decide arbre client)))
  
  
)

