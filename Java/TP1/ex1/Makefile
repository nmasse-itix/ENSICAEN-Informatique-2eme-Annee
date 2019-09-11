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

CC = gcc
LD = gcc
CFLAGS = -Wall -fpic
CPPFLAGS = -I/opt/jdk1.5.0_01/include/ -I/opt/jdk1.5.0_01/include/linux


all : JavaVersC.class libJavaVersC.so


JavaVersC.class : %.class : %.java
	javac $<

JavaVersC.o : %.o : %.c %.h
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $<

libJavaVersC.so : JavaVersC.o
	$(LD) -shared $^ -o $@

clean:
	rm -f *.o *.so *.class

distclean: clean
	rm -f *~

.PHONY: all clean distclean

