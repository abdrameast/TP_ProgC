/*
 * Exercice 4.7 - Gestion d'une liste de couleurs (declarations)
 *
 * Une liste simplement chainee de couleurs RGB(A).
 */

#ifndef __LISTE_H__
#define __LISTE_H__

#include <stdint.h>

/* Une couleur : rouge, vert, bleu et alpha, chacun sur un octet. */
struct couleur
{
  uint8_t rouge;
  uint8_t vert;
  uint8_t bleu;
  uint8_t alpha;
};

/* Un maillon de la liste chainee : une couleur et l'adresse du
 * maillon suivant (NULL pour le dernier). */
struct maillon
{
  struct couleur c;
  struct maillon *suivant;
};

/* La liste elle-meme : l'adresse du premier maillon et le nombre
 * d'elements. */
struct liste_couleurs
{
  struct maillon *premier;
  int taille;
};

/* Initialise une liste vide. */
void init_liste(struct liste_couleurs *liste);

/* Insere une couleur dans la liste (a la fin).
 * Renvoie 0 en cas de succes, -1 si l'allocation echoue. */
int insertion(const struct couleur *c, struct liste_couleurs *liste);

/* Affiche toutes les couleurs de la liste. */
void parcours(const struct liste_couleurs *liste);

/* Libere toute la memoire occupee par la liste. */
void libere_liste(struct liste_couleurs *liste);

/* Fonction d'entree de l'exercice 4.7, appelee depuis main.c. */
int exercice_liste(void);

#endif
