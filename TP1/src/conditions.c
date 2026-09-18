/*
 * Exercice 1.7 - Conditions et boucles avec divisibilite
 *
 * Pour les nombres de 1 a 1000 :
 *   - un nombre divisible par 11 est ignore (continue) ;
 *   - sinon, un nombre divisible par 5 ou par 7 est ajoute a `somme` ;
 *   - des que `somme` depasse 5000, la boucle est interrompue (break).
 *
 * Compilation : gcc -Wall -Wextra -o conditions conditions.c
 */

#include <stdio.h>

int main(void)
{
  int nombre;
  int somme = 0;
  int dernier = 0;   /* dernier nombre examine */
  int arrete = 0;    /* vaut 1 si la boucle a ete interrompue */

  for (nombre = 1; nombre <= 1000; nombre++)
  {
    dernier = nombre;

    /* divisible par 11 : on passe directement au nombre suivant */
    if (nombre % 11 == 0)
    {
      continue;
    }

    /* divisible par 5 ou par 7 : on l'ajoute a la somme */
    if (nombre % 5 == 0 || nombre % 7 == 0)
    {
      somme += nombre;
    }

    /* la somme depasse 5000 : on arrete immediatement la boucle */
    if (somme > 5000)
    {
      arrete = 1;
      break;
    }
  }

  if (arrete)
  {
    printf("Boucle interrompue au nombre %d (la somme a depasse 5000).\n", dernier);
  }
  else
  {
    printf("Boucle terminee normalement (jusqu'a 1000).\n");
  }

  printf("Somme finale : %d\n", somme);

  return 0;
}
