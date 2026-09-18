# TP6 - construction du client et du serveur
#
#   make        : compile le client et le serveur
#   make clean  : supprime les fichiers generes
#
# cJSON (cJSON.c / cJSON.h) est la bibliotheque JSON utilisee pour
# l'exercice 6.3 (https://github.com/DaveGamble/cJSON, licence MIT).

CC ?= gcc
CFLAGS = -Wall -Werror -Wextra -ggdb3

COBJS ?= client.o bmp.o couleur.o cJSON.o
SOBJS ?= serveur.o cJSON.o

.SUFFIXES: .c .o

SERVER = serveur
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(SOBJS)
	$(CC) -o $(SERVER) $(SOBJS) -lm

$(CLIENT): $(COBJS)
	$(CC) -o $(CLIENT) $(COBJS)

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o $(SERVER) $(CLIENT) pie_chart.svg

.PHONY: all clean
