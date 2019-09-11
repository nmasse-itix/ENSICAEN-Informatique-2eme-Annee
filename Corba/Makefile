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

IDLJ = idlj
IDLJFLAGS = -fall
JAVACFLAGS = -Xlint
JAVA_CLASS = Bank/BankServer.class Bank/BankClient.class Bank/AccountImpl.class Bank/BankImpl.class

all: common client server

server: Bank/BankServer.class
client: Bank/BankClient.class

common: BankManagement Bank/AccountImpl.class Bank/BankImpl.class

$(JAVA_CLASS) : %.class : %.java
	$(JAVAC) $(JAVACFLAGS) $<

BankManagement: BankManagement.idl
	$(IDLJ) $(IDLJFLAGS) $<
	test -d $@ || exit 1
	touch $@

clean:
	rm -rf BankManagement
	rm -f Bank/*.class

