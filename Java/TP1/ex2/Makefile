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
# Construit l'exercice 2 du TP1 sur JNI. Construit la librairie partagee
# et le programme java.
#

#
# Version :	0.0.1
#
# Fait :	-
#
# A faire :	-
#


CC = gcc
JAVAC = javac
JAVAH = javah

CFLAGS = -Wall -I$(JAVA_HOME)/include/ -I$(JAVA_HOME)/include/linux -g
LDFLAGS = -fpic -lpam_misc
JAVACFLAGS =
JAVAHFLAGS =


all: Login.class liblogin.so

liblogin.so: login.c Login.h
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -lpam -o $@ $<

Login.class: Login.java
	$(JAVAC) $(JAVACFLAGS) $<

Login.h: Login.java
	$(JAVAH) $(JAVAHFLAGS) -o $@ Login

clean:
	rm -f login.so Login.h Login.class

.PHONY: all clean

