# TP4 - construction des differents programmes
#
#   make            : compile tous les programmes
#   make main       : menu des exercices 4.1, 4.2 et 4.7
#   make calcule    : calculatrice en ligne de commande (4.4)
#   make clean      : supprime les fichiers generes

CC = gcc
CFLAGS = -Wall -Wextra -ggdb3

PROGRAMMES = main calcule etudiant_bd factorielle chercherfichier

all: $(PROGRAMMES)

# Exercices 4.1, 4.2 et 4.7 : un seul programme avec un menu
main: main.o operator.o fichier.o liste.o
	$(CC) -o $@ $^

# Exercice 4.3 : base de donnees etudiante
etudiant_bd: etudiant_bd.o fichier.o
	$(CC) -o $@ $^

# Exercice 4.4 : calculatrice en ligne de commande
calcule: calcule.o operator.o
	$(CC) -o $@ $^

# Exercice 4.5 : factorielle recursive
factorielle: factorielle.o
	$(CC) -o $@ $^

# Exercice 4.6 : recherche d'une phrase dans un fichier
chercherfichier: chercherfichier.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(PROGRAMMES)

.PHONY: all clean
