/*
 * Exercice 4.7 - Gestion d'une liste de couleurs (implementation)
 *
 * Liste simplement chainee : chaque maillon contient une couleur et
 * l'adresse du maillon suivant. L'insertion se fait a la fin de la
 * liste pour conserver l'ordre d'ajout.
 *
 * Compilation : gcc -Wall -Wextra -c liste.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "liste.h"

/*
 * Initialisation : la liste est vide.
 */
void init_liste(struct liste_couleurs *liste)
{
  if (liste == NULL)
  {
    return;
  }

  liste->premier = NULL;
  liste->taille = 0;
}

/*
 * Insertion d'une couleur a la fin de la liste.
 */
int insertion(const struct couleur *c, struct liste_couleurs *liste)
{
  struct maillon *nouveau;

  if (c == NULL || liste == NULL)
  {
    return -1;
  }

  /* allocation dynamique du nouveau maillon */
  nouveau = (struct maillon *)malloc(sizeof(struct maillon));
  if (nouveau == NULL)
  {
    perror("Erreur : allocation dynamique de memoire");
    return -1;
  }

  nouveau->c = *c;         /* copie de la couleur */
  nouveau->suivant = NULL; /* le nouveau maillon sera le dernier */

  if (liste->premier == NULL)
  {
    /* la liste etait vide */
    liste->premier = nouveau;
  }
  else
  {
    /* on parcourt jusqu'au dernier maillon */
    struct maillon *courant = liste->premier;
    while (courant->suivant != NULL)
    {
      courant = courant->suivant;
    }
    courant->suivant = nouveau;
  }

  liste->taille++;

  return 0;
}

/*
 * Parcours : affichage de toutes les couleurs de la liste.
 */
void parcours(const struct liste_couleurs *liste)
{
  const struct maillon *courant;
  int numero = 1;

  if (liste == NULL)
  {
    return;
  }

  if (liste->premier == NULL)
  {
    printf("La liste est vide.\n");
    return;
  }

  for (courant = liste->premier; courant != NULL; courant = courant->suivant)
  {
    printf("Couleur %2d : R = %3u, V = %3u, B = %3u, A = %3u  (#%02x%02x%02x%02x)\n",
           numero,
           courant->c.rouge, courant->c.vert, courant->c.bleu, courant->c.alpha,
           courant->c.rouge, courant->c.vert, courant->c.bleu, courant->c.alpha);
    numero++;
  }

  printf("Nombre total de couleurs : %d\n", liste->taille);
}

/*
 * Liberation de la memoire allouee pour chaque maillon.
 */
void libere_liste(struct liste_couleurs *liste)
{
  struct maillon *courant;

  if (liste == NULL)
  {
    return;
  }

  courant = liste->premier;
  while (courant != NULL)
  {
    struct maillon *suivant = courant->suivant;
    free(courant);
    courant = suivant;
  }

  liste->premier = NULL;
  liste->taille = 0;
}

/*
 * Fonction d'entree de l'exercice 4.7 : construit une liste de 10
 * couleurs puis l'affiche.
 */
int exercice_liste(void)
{
  struct liste_couleurs ma_liste;
  int i;

  /* les 10 couleurs a inserer */
  struct couleur couleurs[10] = {
      {0xFF, 0x00, 0x00, 0xFF}, /* rouge */
      {0x00, 0xFF, 0x00, 0xFF}, /* vert */
      {0x00, 0x00, 0xFF, 0xFF}, /* bleu */
      {0xFF, 0xFF, 0x00, 0xFF}, /* jaune */
      {0x00, 0xFF, 0xFF, 0xFF}, /* cyan */
      {0xFF, 0x00, 0xFF, 0xFF}, /* magenta */
      {0xFF, 0xFF, 0xFF, 0xFF}, /* blanc */
      {0x00, 0x00, 0x00, 0xFF}, /* noir */
      {0x80, 0x80, 0x80, 0xFF}, /* gris */
      {0xef, 0x78, 0x12, 0x80}  /* orange semi-transparent */
  };

  init_liste(&ma_liste);

  for (i = 0; i < 10; i++)
  {
    if (insertion(&couleurs[i], &ma_liste) != 0)
    {
      libere_liste(&ma_liste);
      return -1;
    }
  }

  printf("Liste des couleurs :\n");
  parcours(&ma_liste);

  /* ne pas oublier de liberer la memoire allouee */
  libere_liste(&ma_liste);

  return 0;
}
