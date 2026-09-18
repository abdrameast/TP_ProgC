/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP5 - Exercices 5.4, 5.5 et 5.6 : serveur
 */

#ifndef __SERVER_H__
#define __SERVER_H__

#define PORT 8089

/*
 * Taille maximale d'un message echange avec le client.
 */
#define TAILLE_MESSAGE 1024

/* Envoie un message (*data) au client (client_socket_fd).
 * Renvoie EXIT_SUCCESS ou EXIT_FAILURE. */
int renvoie_message(int client_socket_fd, char *data);

/* Accepter la nouvelle connection d'un client et lire les donnees
 * envoyees par le client. En suite, le serveur envoie un message
 * en retour.
 *
 * Exercice 5.4 : lorsque le message recu commence par "message:", le
 * serveur demande a l'utilisateur de saisir une reponse et l'envoie au
 * client (au lieu de renvoyer le message recu).
 *
 * Exercice 5.5 : lorsque le message recu commence par "calcule:", la
 * demande est transmise a recois_numeros_calcule().
 */
int recois_envoie_message(int client_socket_fd, char *data);

/* Exercice 5.5 - Extrait l'operateur et les nombres du message recu,
 * effectue le calcul et renvoie le resultat au client sous la forme
 * "calcule: <resultat>".
 * Renvoie EXIT_SUCCESS ou EXIT_FAILURE. */
int recois_numeros_calcule(int client_socket_fd, const char *data);

#endif
