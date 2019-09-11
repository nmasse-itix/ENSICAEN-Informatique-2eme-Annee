#!/bin/bash
#
# print.sh                ENSICAEN                       2005
#
# MASSE Nicolas (2005-Groupe3-LIMIN) <nicolas27.masse@laposte.net>
# LIMIN Thomas (2005-Groupe3-MASSE) <thomas.limin@laposte.net>
#
# ENSICAEN
# 6 Boulevard Marechal Juin
# F-14050 Caen Cedex
#
# Ce fichier est l'oeuvre d'eleves de l'ENSI de Caen. Il ne peut etre
# reproduit, utilise ou modifie sans l'avis express de ses auteurs.
#

#
# Genere un fichier PDF des fichiers source d'un projet.
# 
# Parametres : 
#  $1		=> Nom du projet
#  $2..n	=> Fichiers a traiter
#
# Si aucun fichier a traiter n'est specifie, tous les fichiers texte du
# repertoire et des sous-repertoires sont traites.
#

# Version :	0.9
#
# Fait :	-
#
# A faire :	Conversion UTF-8 conditionnelle
#

# Dossier temporaire
TMPDIR="/tmp/print.$$"

# Dossier de destination
DESTDIR="$PWD"

# Fonction a executer lorsque le shell se termine
function on_exit () {
	if [ $? -gt 0 ]; then
		echo "Error !"
	fi
	
	rm -rf "$TMPDIR"
}

# Execute la fonction de nettoyage lorsque le shell se termine
trap on_exit EXIT

# Termine le shell en cas d'erreur
set -e

# Construction de la liste des fichiers
if [ $# -eq 0 ]; then
	echo "Usage: $0 <ProjectName> [files]"
	exit
elif [ $# -eq 1 ]; then
	name="$1"
	filelist=$(find . ! -name "*~" ! -path "*/.svn*" -print0 \
			|xargs -r -0 file -i \
			|awk -F ':' '$2 ~ /text\// {print $1}' \
			|cut -d / -f 2-)
else
	name="$1"
	shift
	
	filelist=$(for arg; do echo "$arg"; done)
fi

# La liste ne doit pas etre vide
test "$filelist"

# Copie des fichiers a imprimer
mkdir -p "$TMPDIR/src"
(echo "$filelist" ; echo "$TMPDIR/src") |xargs -e\n cp --parent
cd "$TMPDIR/src"

# On recode tous les fichiers en latin1
# TODO : S'assurer qu'ils sont en utf-8 (avec file)
echo "$filelist" |while read file; do recode utf8..latin1 "$file"; done

# Creation du fichier postscript avec A2PS
echo "$filelist" |xargs -e\n a2ps --encoding=latin1 --media=a4 -2 \
	--file-align=fill --pretty-print --output="../$name.ps" --quiet \
	--line-numbers=5 --toc --chars-per-line=100 \
	--header="$name - LIMIN Thomas & MASSE nicolas, 2A INFO, groupe A, TP 3"

# Conversion du fichier PS en PDF
cd .. ; ps2pdf14 -sPAPERSIZE=a4 "$name.ps"

# Copie du fichier PDF dans le repertoire de destination
cp "$name.pdf" "$DESTDIR"
cp "$name.ps" "$DESTDIR"

