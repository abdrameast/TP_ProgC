/*
 * Exercice 4.5 - Calcul de la factorielle (fonction recursive)
 *
 *   0! = 1
 *   n! = n x (n-1)!
 *
 * Compilation : gcc -Wall -Wextra -o factorielle factorielle.c
 */

#include <stdio.h>

/*
 * Fonction recursive : elle s'appelle elle-meme avec un argument plus
 * petit, jusqu'au cas d'arret (num == 0).
 */
long long factorielle(int num)
{
  if (num == 0)
  {
    printf("fact(0): 1\n");
    return 1;
  }
  else
  {
    long long valeur = (long long)num * factorielle(num - 1);
    printf("fact(%d): %lld\n", num, valeur);
    return valeur;
  }
}

int main(void)
{
  /* les valeurs a tester */
  int valeurs[] = {0, 1, 5, 10, 20};
  int nb = (int)(sizeof(valeurs) / sizeof(valeurs[0]));
  int i;

  for (i = 0; i < nb; i++)
  {
    printf("--- Calcul de %d! ---\n", valeurs[i]);
    printf("Resultat : %d! = %lld\n\n", valeurs[i], factorielle(valeurs[i]));
  }

  /* Remarque : 21! depasse deja la capacite d'un long long
   * (9 223 372 036 854 775 807). */

  return 0;
}
