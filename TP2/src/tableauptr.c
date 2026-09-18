/*
 * Exercice 2.9 - Manipulation de tableaux avec des pointeurs
 *
 * Deux tableaux (entiers et flottants) sont remplis avec des valeurs
 * aleatoires, puis chaque valeur dont l'indice est divisible par 2 est
 * multipliee par 3.
 *
 * Contrainte : les tableaux sont parcourus *sans* notation indicielle
 * (pas de tableau[i]), uniquement avec des pointeurs.
 *
 * Compilation : gcc -Wall -Wextra -o tableauptr tableauptr.c
 */

#include <stdio.h>
#include <stdlib.h> /* rand, srand */
#include <time.h>   /* time */

#define TAILLE 11

/* Affiche un tableau d'entiers en le parcourant avec un pointeur. */
static void affiche_entiers(const int *debut, int taille)
{
  const int *p;

  for (p = debut; p < debut + taille; p++)
  {
    printf("%d", *p);
    if (p < debut + taille - 1)
    {
      printf(", ");
    }
  }
  printf("\n");
}

/* Affiche un tableau de flottants en le parcourant avec un pointeur. */
static void affiche_flottants(const float *debut, int taille)
{
  const float *p;

  for (p = debut; p < debut + taille; p++)
  {
    printf("%.2f", *p);
    if (p < debut + taille - 1)
    {
      printf(", ");
    }
  }
  printf("\n");
}

int main(void)
{
  int entiers[TAILLE];
  float flottants[TAILLE];

  int *pe;
  float *pf;
  int indice;

  /* initialisation du generateur de nombres aleatoires */
  srand((unsigned int)time(NULL));

  /* remplissage des deux tableaux avec des pointeurs */
  for (pe = entiers, pf = flottants; pe < entiers + TAILLE; pe++, pf++)
  {
    *pe = rand() % 200;                    /* entier entre 0 et 199 */
    *pf = (float)(rand() % 1000) / 100.0f; /* flottant entre 0 et 9.99 */
  }

  printf("Tableau d'entiers (avant la multiplication par 3) :\n");
  affiche_entiers(entiers, TAILLE);
  printf("\nTableau de nombres a virgule flottante (avant la multiplication par 3) :\n");
  affiche_flottants(flottants, TAILLE);

  /* multiplication par 3 des valeurs dont l'indice est divisible par 2 */
  indice = 0;
  for (pe = entiers, pf = flottants; pe < entiers + TAILLE; pe++, pf++, indice++)
  {
    if (indice % 2 == 0)
    {
      *pe = *pe * 3;
      *pf = *pf * 3.0f;
    }
  }

  printf("\nTableau d'entiers (apres la multiplication par 3) :\n");
  affiche_entiers(entiers, TAILLE);
  printf("\nTableau de nombres a virgule flottante (apres la multiplication par 3) :\n");
  affiche_flottants(flottants, TAILLE);

  return 0;
}
