/*
 * Exercice 3.5 - Recherche dichotomique dans un tableau trie
 *
 * La recherche dichotomique compare la valeur cherchee a l'element du
 * milieu du tableau : si elle est plus petite, on continue dans la
 * moitie gauche, sinon dans la moitie droite. La zone de recherche est
 * ainsi divisee par deux a chaque etape (complexite O(log n)).
 *
 * Reference : https://fr.wikipedia.org/wiki/Recherche_dichotomique
 *
 * Compilation : gcc -Wall -Wextra -o recherche_dichotomique recherche_dichotomique.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 100

/* Recherche dichotomique dans un tableau *trie par ordre croissant*.
 * Renvoie l'indice de `valeur`, ou -1 si elle est absente. */
static int recherche_dichotomique(const int *tableau, int taille, int valeur)
{
  int debut = 0;
  int fin = taille - 1;

  while (debut <= fin)
  {
    /* indice du milieu, calcule de maniere a eviter tout debordement */
    int milieu = debut + (fin - debut) / 2;

    if (tableau[milieu] == valeur)
    {
      return milieu; /* trouve */
    }
    else if (tableau[milieu] < valeur)
    {
      debut = milieu + 1; /* on cherche dans la moitie droite */
    }
    else
    {
      fin = milieu - 1; /* on cherche dans la moitie gauche */
    }
  }

  return -1; /* absent */
}

int main(void)
{
  int tableau[TAILLE];
  int i;
  int recherche;
  int position;
  int valeur = -2;

  srand((unsigned int)time(NULL));

  /* construction directe d'un tableau deja trie par ordre croissant :
   * on ajoute a chaque etape un increment aleatoire */
  for (i = 0; i < TAILLE; i++)
  {
    tableau[i] = valeur;
    valeur += (rand() % 5) + 1;
  }

  printf("Tableau trie :\n");
  for (i = 0; i < TAILLE; i++)
  {
    printf("%5d", tableau[i]);
    if ((i + 1) % 10 == 0)
    {
      printf("\n");
    }
  }

  printf("\nEntrez l'entier que vous souhaitez chercher : ");
  if (scanf("%d", &recherche) != 1)
  {
    printf("\nEntree invalide.\n");
    return 1;
  }

  position = recherche_dichotomique(tableau, TAILLE, recherche);

  if (position >= 0)
  {
    printf("\nResultat : entier present (a la position %d)\n", position);
  }
  else
  {
    printf("\nResultat : entier absent\n");
  }

  return 0;
}
