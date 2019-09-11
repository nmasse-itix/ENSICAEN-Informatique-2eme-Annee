(load 'packages.lsp)
(load 'se.lsp)

(in-package :tp6)
(load-attributes-from-file "bateaux_dico.lsp" )
(load-regles-from-file "bateaux_regles.lsp" )
(load-faits-from-file "bateaux_faits.lsp" )

(format t "~%~%~%~%")

(moteur-inference)
