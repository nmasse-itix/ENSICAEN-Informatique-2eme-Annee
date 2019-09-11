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

CXX = g++
LD = g++
CFLAGS = -Wall --pedantic -ggdb
CPPFLAGS = -I./


OBJECTS = matrix.o

EXEC = checkMatrix

checkMatrix : checkMatrix.o

all : $(OBJECTS)

checkMatrix.o : %.o : %.cpp
	$(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(OBJECTS) : %.o : %.cpp %.h
	$(CXX) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(EXEC) : % : %.o $(OBJECTS)
	$(LD) $^ -o $@

clean:
	rm -f *~ *.o

distclean: clean
	rm -f $(EXEC)

.PHONY: all clean distclean

