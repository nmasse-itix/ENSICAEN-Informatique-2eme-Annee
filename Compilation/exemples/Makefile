#
# Makefile                      ENSICAEN                       2006
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
# Construit les exemples
#

#
# version:	05/04/2006
#
# done:         -
#
# todo: 	-
#


CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

EPC = ../epc

TARGETS = if while micropascal

all: $(TARGETS)

$(TARGETS): % : %.pas $(EPC)
	$(EPC) $< >$@.c
	$(CC) $(CFLAGS) $(LDFLAGS) $@.c -o $@

clean:
	rm -f *.c $(TARGETS)

distclean: clean
	rm -f *~


.PHONY: distclean clean all
