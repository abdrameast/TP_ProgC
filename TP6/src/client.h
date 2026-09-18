/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP6 - Exercices 6.1, 6.2 et 6.3 : client
 *
 * Le client analyse une image BMP, en extrait les N couleurs les plus
 * frequentes (N est saisi par l'utilisateur, exercice 6.2) et les envoie
 * au serveur sous la forme d'un message JSON (exercice 6.3) :
 *
 *   {
 *     "code"    : "couleurs",
 *     "nombre"  : 10,
 *     "valeurs" : [ "#ef7812", "#2cc864", ... ]
 *   }
 *
 * Un simple message prend la forme :
 *
 *   { "code" : "message", "valeurs" : [ "bonjour" ] }
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/*
 * Taille maximale d'un message JSON echange avec le serveur.
 */
#define TAILLE_MESSAGE 4096

/*
 * Nombre maximal de couleurs pouvant etre demandees (exercice 6.2).
 */
#define MAX_COULEURS 30

/*
 * Fonction d'envoi et de reception de messages (format JSON).
 * Il faut un argument : l'identifiant de la socket.
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd);

/*
 * Analyse l'image BMP `pathname`, extrait les `nb_couleurs` couleurs
 * les plus frequentes et les envoie au serveur au format JSON.
 *
 * @param socketfd     l'identifiant de la socket ;
 * @param pathname     le chemin de l'image BMP ;
 * @param nb_couleurs  le nombre de couleurs demande (1 a MAX_COULEURS).
 *
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
int envoie_couleurs(int socketfd, char *pathname, int nb_couleurs);

#endif
