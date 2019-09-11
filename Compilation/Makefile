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
# Construit le programme EPC
#

#
# version:	05/04/2006
#
# done:         -
#
# todo: 	-
#


CC = gcc
CFLAGS = -Wall -ggdb 
LDFLAGS = 

LEX = lex

# Le -v génère un fichier "parser.output" contenant des informations utiles.
YACC = yacc
YACCFLAGS = -v

TARGETS = debug epc epc-debug

all: $(TARGETS) exemples

exemples:
	$(MAKE) -C $@

epc: lex.yy.o parser.tab.o main_parser.o generator.o
	$(CC) -o $@ $(LDFLAGS) $^

epc-debug: lex-debug.yy.o parser.tab.o main_parser.o generator.o
	$(CC) -o $@ $(LDFLAGS) $^

debug: lex.yy.o debug.o parser.tab.o generator.o
	$(CC) -o $@ $(LDFLAGS) $^

lex.yy.o: parser.tab.h

lex-debug.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -DDEBUG -c -o $@ $<

lex.yy.c: scanner.l
	$(LEX) $<

parser.tab.c: parser.y
	$(YACC) $(YACCFLAGS) -d -b parser $<

parser.tab.h: parser.y
	$(YACC) $(YACCFLAGS) -d -b parser $<

clean:
	rm -f lex.yy.c parser.tab.c parser.tab.h parser.output *.o $(TARGETS)
	make -C exemples $@

distclean: clean
	rm -f *~
	make -C exemples $@


.PHONY: distclean clean all exemples
