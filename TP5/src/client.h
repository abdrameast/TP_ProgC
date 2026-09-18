/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP5 - Exercices 5.4, 5.5 et 5.6 : client
 */

#ifndef __CLIENT_H__
#define __CLIENT_H__

/*
 * port d'ordinateur pour envoyer et recevoir des messages
 */
#define PORT 8089

/*
 * Taille maximale d'un message echange avec le serveur.
 */
#define TAILLE_MESSAGE 1024

/*
 * Exercice 5.4 - Fonction d'envoi et de reception de messages.
 * Il faut un argument : l'identifiant de la socket.
 * Si l'utilisateur saisit une demande de la forme "calcule : + 23 45",
 * la demande est transmise a envoie_operateur_numeros().
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd);

/*
 * Exercice 5.5 - Envoie une operation de calcul au serveur.
 *
 * @param socketfd    l'identifiant de la socket ;
 * @param op          l'operateur (+, -, *, /, %) ;
 * @param num1        le premier nombre ;
 * @param num2        le second nombre (ignore si nb_numeros vaut 1) ;
 * @param nb_numeros  1 ou 2 selon le nombre d'operandes ;
 * @param resultat    recoit le resultat renvoye par le serveur
 *                    (peut valoir NULL si le resultat n'est pas utilise).
 *
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
int envoie_operateur_numeros(int socketfd, char op, double num1, double num2,
                             int nb_numeros, double *resultat);

/*
 * Exercice 5.6 - Lit les notes des etudiants dans `dossier` (un
 * sous-repertoire par etudiant, un fichier noteN.txt par note) et
 * demande au serveur de calculer la somme et la moyenne des notes de
 * chaque etudiant, puis la moyenne de la classe.
 *
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
int calcule_notes_etudiants(int socketfd, const char *dossier);

#endif
