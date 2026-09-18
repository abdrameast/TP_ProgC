/*
 * TP5 - Exercices 5.1, 5.2 et 5.3 : lecture d'un repertoire
 *
 * Trois facons de lister le contenu d'un repertoire :
 *   - lire_dossier           : le repertoire seul (5.1) ;
 *   - lire_dossier_recursif  : le repertoire et ses sous-repertoires,
 *                              par recursivite (5.2) ;
 *   - lire_dossier_iteratif  : le meme resultat, sans recursivite,
 *                              a l'aide d'une pile explicite (5.3).
 */

#ifndef __REPERTOIRE_H__
#define __REPERTOIRE_H__

/* Exercice 5.1 : affiche les fichiers et repertoires contenus dans
 * `nom_repertoire`.
 * Renvoie 0 en cas de succes, -1 si le repertoire ne peut pas etre
 * ouvert. */
int lire_dossier(const char *nom_repertoire);

/* Exercice 5.2 : affiche recursivement les fichiers, repertoires et
 * sous-repertoires de `nom_repertoire`.
 * Renvoie 0 en cas de succes, -1 en cas d'erreur. */
int lire_dossier_recursif(const char *nom_repertoire);

/* Exercice 5.3 : meme resultat que lire_dossier_recursif, mais avec une
 * approche iterative (boucle + pile de repertoires a traiter).
 * Renvoie 0 en cas de succes, -1 en cas d'erreur. */
int lire_dossier_iteratif(const char *nom_repertoire);

#endif
