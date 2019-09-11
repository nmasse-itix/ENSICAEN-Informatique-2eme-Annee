#
# Makefile                      ENSICAEN                       2005
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
# Description du makefile
#

#
# Version :	1.0.0
#
# Fait :	Detail de ce qui a ete fait.
#
# A faire :	Detail de ce qui n'a pas ete fait.
#

CXX = g++
LD = g++
CFLAGS = -Wall --pedantic
CPPFLAGS = -I./


OBJECTS = ex2.o ex3.o porte.o

EXEC = ex2 ex3

all : $(EXEC) porte

ex1.o : %.o : %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

ex1.o : ex1.h

$(OBJECTS) : %.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(EXEC) : % : %.o ex1.o
	$(LD) ex1.o $< -o $@

porte : porte.o
	$(LD) ex1.o $< -o $@

clean:
	rm -f ex1 ex2 ex3 porte *~ *.o

.PHONY: all clean

