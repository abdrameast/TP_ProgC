/*
 * Exercice 2.1 - Calcul de la puissance
 *
 * Calcule a^b sans utiliser la fonction pow() de <math.h> et sans
 * demander les valeurs a l'utilisateur.
 *
 * Compilation : gcc -Wall -Wextra -o puissance puissance.c
 */

#include <stdio.h>

int main(void)
{
  int a = 2;         /* la base */
  int b = 3;         /* l'exposant */
  long long resultat = 1; /* le resultat : a^b */
  int i;

  /* on multiplie `resultat` par `a` exactement `b` fois.
   * Si b vaut 0, la boucle ne s'execute pas et le resultat reste 1. */
  for (i = 0; i < b; i++)
  {
    resultat = resultat * a;
  }

  printf("%d ^ %d = %lld\n", a, b, resultat);

  /* Quelques autres tests, cette fois avec une boucle while. */
  {
    int bases[] = {2, 3, 5, 10, 7};
    int exposants[] = {10, 4, 3, 6, 0};
    int nb = (int)(sizeof(bases) / sizeof(bases[0]));

    for (i = 0; i < nb; i++)
    {
      long long r = 1;
      int compteur = exposants[i];

      while (compteur > 0)
      {
        r = r * bases[i];
        compteur--;
      }

      printf("%d ^ %d = %lld\n", bases[i], exposants[i], r);
    }
  }

  return 0;
}
