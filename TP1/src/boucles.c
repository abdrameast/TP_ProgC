/*
 * Exercice 1.6 - Affichage d'un triangle rectangle avec des boucles
 *
 * La taille du triangle est donnee par la variable `compteur`
 * (strictement inferieure a 10).
 *
 * Regle d'affichage pour la ligne i et la colonne j :
 *   - '*' si la colonne est la premiere (j == 1), la derniere (j == i)
 *     ou si la ligne est la derniere (i == compteur) ;
 *   - '#' sinon.
 *
 * Exemple pour compteur = 5 :
 *   *
 *   * *
 *   * # *
 *   * # # *
 *   * * * * *
 *
 * Compilation : gcc -Wall -Wextra -o boucles boucles.c
 */

#include <stdio.h>

/* Premiere version : deux boucles `for` imbriquees. */
static void triangle_for(int compteur)
{
  int i;
  int j;

  printf("--- version avec des boucles for (compteur = %d) ---\n", compteur);

  for (i = 1; i <= compteur; i++)
  {
    for (j = 1; j <= i; j++)
    {
      /* bord du triangle ou derniere ligne -> '*', interieur -> '#' */
      if (j == 1 || j == i || i == compteur)
      {
        printf("*");
      }
      else
      {
        printf("#");
      }

      /* un espace entre deux caracteres, sauf apres le dernier */
      if (j < i)
      {
        printf(" ");
      }
    }
    printf("\n");
  }
}

/* Deuxieme version : le meme resultat avec des boucles `while`,
 * un branchement conditionnel `if` et un branchement inconditionnel
 * `continue`. */
static void triangle_while(int compteur)
{
  int i = 1;

  printf("--- version avec des boucles while (compteur = %d) ---\n", compteur);

  while (i <= compteur)
  {
    int j = 1;

    while (j <= i)
    {
      /* interieur du triangle : on affiche '#' puis on passe
       * directement a la colonne suivante grace a `continue` */
      if (j != 1 && j != i && i != compteur)
      {
        printf("#");
        if (j < i)
        {
          printf(" ");
        }
        j++;
        continue;
      }

      printf("*");
      if (j < i)
      {
        printf(" ");
      }
      j++;
    }

    printf("\n");
    i++;
  }
}

int main(void)
{
  int compteur = 5; /* doit rester strictement inferieur a 10 */

  if (compteur >= 10)
  {
    printf("Erreur : compteur doit etre strictement inferieur a 10.\n");
    return 1;
  }

  triangle_for(compteur);
  printf("\n");
  triangle_while(compteur);

  /* quelques autres valeurs de test */
  printf("\n");
  triangle_for(3);
  printf("\n");
  triangle_for(7);

  return 0;
}
