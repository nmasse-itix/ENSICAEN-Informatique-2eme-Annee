#|
 | #(@)connexion.lsp              ENSICAEN                       2006-01-09
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
 | Initiation à la programmation avec des agents.
 |#


#|
 | version:	2006-02-07
 |
 | done:	all
 |
 | todo:	none
 |#


#|
 | Classe Connexion.
 |
 |#

(defclass Connexion ()
  ((nom 
     :accessor		nom 
     :initarg		:nom  
     :initform		nil
     :documentation 	"Le nom de la connexion"
   )
   (boitiers 
     :accessor		boitiers 
     :initarg		:boitiers 
     :initform		nil
     :documentation	"La liste des boitiers reliés à cette connexion"
   )
   (provenance 
     :accessor		provenance 
     :initarg		:provenance 
     :initform 		nil
     :documentation	"La référence du boitier qui a mis la valeur de cet objet"
   )
   (valeur 
     :accessor		valeur 
     :initarg		:valeur
     :initform		nil
     :documentation	"La valeur de cette connexion"
   )
   (gestionnaire
     :accessor		gestionnaire
     :initform		nil
     :documentation	"Le gestionnaire de l'application"
   ))
  (:documentation "Une connexion a un nom et relie des boitiers")
)

#|
 | Mets une valeur dans cette connexion, et propage la valeur aux boitiers
 | voisins.
 |#
(defmethod mettre-valeur (val demandeur (oself Connexion))
 (cond
  ((null (valeur oself))
    (setf (valeur oself) val) 
    (format t "~s: valeur modifiée~%" oself) 
    (setf (provenance oself) demandeur)
    (mapcar #'(lambda (x)
		(if (not (eql demandeur x)) 
		  (attention-une-valeur oself x)
		)
	      ) 
	    (boitiers oself)
    )
   )
  ((= val (valeur oself)) 
    (format t "~s: valeur non modifiée mais identique~%" oself)
   )
  (t 
    (format t "~s: valeurs differentes, valeur non modifiée !~%" oself)
    (il-y-a-incoherence oself (gestionnaire oself))
   )
  )
)

#|
 | Oublie la valeur de cette connexion et propage l'oubli aux boitiers voisins.
 |#
(defmethod oublier-valeur (demandeur (oself Connexion))
 (cond
   ((or (null (valeur oself)) (null (provenance oself)))
     t
    )
   ((eql demandeur (provenance oself))
     (setf (valeur oself) nil) 
     (format t "~s: valeur oubliée~%" oself)
     (mapcar #'(lambda (x)
		(if (not (eql demandeur x)) 
		  (plus-de-valeur oself x)
		)
	      ) 
	    (boitiers oself)
     )
     t
    )
   (t 
     (format t "~s: valeur non oubliée~%" oself)
     nil
    )
 )
)

#|
 | Modifie la valeur de la connexion après l'avoir oubliée.
 |#
(defmethod modifier-valeur (val demandeur (oself Connexion))
  (if (oublier-valeur demandeur oself)
      (mettre-valeur val demandeur oself)
  )
)



#|
 | Classe Boitier
 |#

(defclass Boitier ()
  ((borne1 
     :accessor		borne1
     :initarg		:borne1
     :initform		nil
     :documentation	"La borne première borne d'entrée"
   )
   (borne2 
     :accessor		borne2
     :initarg		:borne2
     :initform		nil
     :documentation	"La seconde borne d'entrée"
   )
   (borneS 
     :accessor		borneS
     :initarg		:borneS
     :initform		nil
     :documentation	"La borne de sortie"
   ))
  (:documentation "Un boitier a deux connexions d'entrée et une de sortie")
)

#|
 | Surcharge de la méthode initialize-instance, le mot clé after
 | indique que la surcharge s'execute après la méthode de base,
 | prédéfinie et toujours executée après make-instance (Sorte de
 | constructeur automatique). Le oself est un nom choisi pour
 | référencer l'objet en cours, correspond au self de Smalltalk
 |#
(defmethod initialize-instance :after ((oself Boitier) &rest args)
  (declare (ignore args))
  
  ; Raccorde les bornes au boitier
  (setf (boitiers (borne1 oself)) (cons oself (boitiers (borne1 oself))))
  (setf (boitiers (borne2 oself)) (cons oself (boitiers (borne2 oself))))
  (setf (boitiers (borneS oself)) (cons oself (boitiers (borneS oself))))
)

#|
 | Méthode appelée par les connexions lorsqu'elles ont reçu une valeur.
 |#

(defmethod attention-une-valeur (cnx (oself Boitier))
  (format t "~s: attention une valeur !~%" oself )
)

#|
 | Méthode appelée par les connexions lorsqu'elles ont perdu leur valeur.
 |#
(defmethod plus-de-valeur (cnx (oself Boitier))
  (format t "~s: attention plus de valeur !~%" oself)
  (oublier-valeur oself (borne1 oself))
  (oublier-valeur oself (borne2 oself))
  (oublier-valeur oself (borneS oself))
  (attention-une-valeur oself oself)
)


#|
 | Définition de la classe Add(itionneur), qui hérite de Boitier
 |#
(defclass Add (Boitier)
  ()
)

(defmethod attention-une-valeur :after (cnx (oself Add))
  (cond
    ((and (not (null (valeur (borne1 oself)))) (not (null (valeur (borne2 oself)))))
  	(format t "~s: addition: je connais borne1 et borne2 ~%" oself)
	(mettre-valeur (+ (valeur (borne1 oself)) (valeur (borne2 oself))) oself (borneS oself))
    )
    ((and (not (null (valeur (borne1 oself)))) (not (null (valeur (borneS oself)))))
  	(format t "~s: addition: je connais borne1 et borneS ~%" oself)
	(mettre-valeur (- (valeur (borneS oself)) (valeur (borne1 oself))) oself (borne2 oself))
    )
    ((and (not (null (valeur (borne2 oself)))) (not (null (valeur (borneS oself)))))
  	(format t "~s: addition: je connais borne2 et borneS ~%" oself)
	(mettre-valeur (- (valeur (borneS oself)) (valeur (borne2 oself))) oself (borne1 oself))
    )
  )
)



#|
 | Définition de la classe Mul(iplieur), qui hérite de Boitier
 |#
(defclass Mul (Boitier)
  ()
)

(defmethod attention-une-valeur :after (cnx (oself Mul))
  (cond 
    ((and (not (null (valeur (borne1 oself)))) (not (null (valeur (borne2 oself)))))
  	(format t "~s: multiplication: je connais borne1 et borne2 ~%" oself)
	(mettre-valeur (* (valeur (borne1 oself)) (valeur (borne2 oself))) oself (borneS oself))
    )
    ((and (not (null (valeur (borne1 oself)))) (not (null (valeur (borneS oself)))))
  	(format t "~s: multiplication: je connais borneS et borne1 ~%" oself)
	(mettre-valeur (/ (valeur (borneS oself)) (valeur (borne1 oself))) oself (borne2 oself))
    )
    ((and (not (null (valeur (borne2 oself)))) (not (null (valeur (borneS oself)))))
  	(format t "~s: multiplication: je connais borneS et borne2 ~%" oself)
	(mettre-valeur (/ (valeur (borneS oself)) (valeur (borne2 oself))) oself (borne1 oself))
    )
  )
)



#|
 | Classe Gestionnaire
 |#

(defclass Gestionnaire ()
  ((historique 
     :accessor		historique 
     :initform		nil
     :documentation	"La liste des valeurs de toutes les connexions"
   )
   (incoherence
     :accessor		incoherence
     :initform		nil
     :documentation	"Permet de savoir s'il y a eu incohérence lors du calcul"
   ))
  (:documentation "Un gestionnaire gère les opérations de d'annulation")
)

#|
 | Ajoute la connexion à ce gestionnaire, afin qu'il gère les incohérences 
 | de la connexion.
 |#
(defmethod ajouter-au-gestionnaire (cnx (oself Gestionnaire)) 
  (setf (historique oself) 
	(cons 
	     (list cnx (valeur cnx) (provenance cnx))
	     (historique oself)
	)
  )
  (setf (gestionnaire cnx) oself)
)

#|
 | Sauvegarde l'état de toutes les connexions. Méthode à appeler avant toute 
 | modification de valeur par l'utilisateur.
 |#
(defmethod sauvegarde-gestionnaire ((oself Gestionnaire))
  (setf (historique oself)
    (loop for x in (historique oself) collect (list (car x) (valeur (car x)) (provenance (car x))))
  )
)

#|
 | Restauration des anciennes valeurs des connexions.
 |#
(defmethod restauration-gestionnaire ((oself Gestionnaire))
    (loop for x in (historique oself) do 
	  (setf (valeur (car x)) (cadr x)) 
	  (setf (provenance (car x)) (caddr x)) 
    )
    (setf (incoherence oself) nil)
)

#|
 | Méthode appelée par les connexions pour signaler une incohérence.
 |#
(defmethod il-y-a-incoherence (cnx (oself Gestionnaire))
  (setf (incoherence oself) t)
  (format t "~s: INCOHERENCE DETECTEE !~%" cnx)
)

#|
 | Teste le flag d'incohérence.
 |#
(defmethod y-a-t-il-incoherence ((oself Gestionnaire))
  (incoherence oself)
)

#|
 | Créer les instances de Connexion
 |#
(setq a (make-instance 'Connexion :nom "a"))
(setq b (make-instance 'Connexion :nom "b"))
(setq c (make-instance 'Connexion :nom "c"))
(setq d (make-instance 'Connexion :nom "d"))
(setq e (make-instance 'Connexion :nom "e"))
(setq f (make-instance 'Connexion :nom "f"))
(setq g (make-instance 'Connexion :nom "g"))
(setq h (make-instance 'Connexion :nom "h"))
(setq i (make-instance 'Connexion :nom "i"))
(setq j (make-instance 'Connexion :nom "j"))


#|
 | Créer les instances de Boitier
 |#
(setq mul1 (make-instance 'Mul :borne1 a :borne2 b :borneS c))
(setq mul2 (make-instance 'Mul :borne1 c :borne2 e :borneS d))
(setq mul3 (make-instance 'Mul :borne1 f :borne2 j :borneS h))
(setq add1 (make-instance 'Add :borne1 e :borne2 f :borneS g))
(setq add2 (make-instance 'Add :borne1 d :borne2 h :borneS i))

#|
 | Créer le gestionnaire.
 |# 
(setq gest (make-instance 'Gestionnaire))

#|
 | Fonction utilitaire.
 |# 
(defun affichage ()
	(format t 
		"ETAT DES CNX: a = ~s, b = ~s, c = ~s, d = ~s, e = ~s, f = ~s, g = ~s, h = ~s, i = ~s, j = ~s~%" 
		(valeur a) (valeur b) (valeur c) (valeur d) (valeur e) 
		(valeur f) (valeur g) (valeur h) (valeur i) (valeur j)
	)
)

; Ajout des connexions au gestionnaire
(ajouter-au-gestionnaire a gest)
(ajouter-au-gestionnaire b gest)
(ajouter-au-gestionnaire c gest)
(ajouter-au-gestionnaire d gest)
(ajouter-au-gestionnaire e gest)
(ajouter-au-gestionnaire f gest)
(ajouter-au-gestionnaire g gest)
(ajouter-au-gestionnaire h gest)
(ajouter-au-gestionnaire i gest)
(ajouter-au-gestionnaire j gest)

#|
 | Début du test présent dans l'énoncé du TP.
 |#

(mettre-valeur 2 'utilisateur a)
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur 3 'utilisateur b)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur 3 'utilisateur i)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur 1 'utilisateur j)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur 1 'utilisateur g)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur 1 'utilisateur f)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

(sauvegarde-gestionnaire gest)
(mettre-valeur (/ 3 5) 'utilisateur f)
(if (y-a-t-il-incoherence gest) (restauration-gestionnaire gest))
(affichage)

