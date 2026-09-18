/*
 * Exercice 4.2 - Gestion de fichiers (declarations)
 */

#ifndef __FICHIER_H__
#define __FICHIER_H__

/* Affiche a l'ecran le contenu du fichier `nom_de_fichier`.
 * Renvoie 0 en cas de succes, -1 si le fichier ne peut pas etre ouvert. */
int lire_fichier(const char *nom_de_fichier);

/* Ajoute `message` a la fin du fichier `nom_de_fichier` (le fichier est
 * cree s'il n'existe pas). Un retour a la ligne est ajoute si le message
 * n'en contient pas deja un.
 * Renvoie 0 en cas de succes, -1 en cas d'erreur. */
int ecrire_dans_fichier(const char *nom_de_fichier, const char *message);

/* Fonction d'entree de l'exercice 4.2, appelee depuis main.c. */
int exercice_fichier(void);

#endif
