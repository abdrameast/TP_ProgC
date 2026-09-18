/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP6 - Exercices 6.1, 6.2 et 6.3 : serveur
 *
 * Le serveur recoit des messages au format JSON (exercice 6.3) :
 *
 *   { "code" : "message",  "valeurs" : [ "bonjour" ] }
 *   { "code" : "couleurs", "nombre" : 10,
 *     "valeurs" : [ "#ef7812", "#2cc864", ... ] }
 *
 * Pour un message "couleurs", le serveur genere un diagramme circulaire
 * au format SVG a partir des couleurs recues, puis lance un navigateur
 * (firefox) pour l'afficher. Il repond ensuite au client, au format
 * JSON :
 *
 *   { "code" : "reponse", "valeurs" : [ "pie_chart.svg" ] }
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/*
 * Taille maximale d'un message JSON echange avec le client.
 */
#define TAILLE_MESSAGE 4096

/*
 * Nombre maximal de couleurs traitees (exercice 6.2).
 */
#define MAX_COULEURS 30

/*
 * Chemin du fichier SVG genere (defini dans serveur.c).
 */
extern const char *svg_file_path;

/* Envoie un message (*data) au client (client_socket_fd).
 * Renvoie EXIT_SUCCESS ou EXIT_FAILURE. */
int renvoie_message(int client_socket_fd, char *data);

/* Accepter la nouvelle connection d'un client et lire les données
 * envoyées par le client. En suite, le serveur envoie un message
 * en retour. Le message recu est analyse au format JSON.
 */
int recois_envoie_message(int client_socket_fd, char data[TAILLE_MESSAGE]);

#endif
