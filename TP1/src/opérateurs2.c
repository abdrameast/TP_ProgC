/*
 * Exercice 1.5 (suite) - Operateurs d'affectation composee,
 *                        d'incrementation et de decalage
 *
 * Deuxieme version de opérateurs.c : on repart des memes valeurs
 * (a = 16, b = 3) mais on utilise cette fois les operateurs d'affectation
 * composee (+=, -=, *=, /=, %=, &=, |=, ^=, <<=, >>=), les operateurs
 * d'incrementation et de decrementation (++, --) ainsi que les
 * operateurs logiques (&&, ||, !).
 *
 * Compilation : gcc -Wall -Wextra -o operateurs2 opérateurs2.c
 */

#include <stdio.h>

int main(void)
{
  int a = 16;
  int b = 3;
  int resultat;
  int valeur;

  printf("Valeurs de depart : a = %d, b = %d\n", a, b);
  printf("==========================================\n\n");

  /* --- operateurs d'affectation composee --- */
  printf("Operateurs d'affectation composee\n");
  printf("---------------------------------\n");

  resultat = a;
  resultat += b; /* equivalent a : resultat = resultat + b */
  printf("resultat = %d; resultat += %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat -= b;
  printf("resultat = %d; resultat -= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat *= b;
  printf("resultat = %d; resultat *= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat /= b;
  printf("resultat = %d; resultat /= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat %= b;
  printf("resultat = %d; resultat %%= %d -> %d\n", a, b, resultat);

  /* --- affectations composees sur les bits --- */
  printf("\nOperateurs de bits\n");
  printf("------------------\n");

  resultat = a;
  resultat &= b; /* ET bit a bit */
  printf("resultat = %d; resultat &= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat |= b; /* OU bit a bit */
  printf("resultat = %d; resultat |= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat ^= b; /* OU exclusif bit a bit */
  printf("resultat = %d; resultat ^= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat <<= b; /* decalage a gauche : multiplication par 2^b */
  printf("resultat = %d; resultat <<= %d -> %d\n", a, b, resultat);

  resultat = a;
  resultat >>= b; /* decalage a droite : division entiere par 2^b */
  printf("resultat = %d; resultat >>= %d -> %d\n", a, b, resultat);

  /* --- incrementation et decrementation --- */
  printf("\nIncrementation et decrementation\n");
  printf("--------------------------------\n");

  /* Attention : la valeur renvoyee et la variable modifiee doivent
   * etre affichees par deux instructions distinctes. Utiliser
   * resultat++ et resultat dans un meme printf donnerait un resultat
   * indefini, l'ordre d'evaluation des arguments n'etant pas garanti. */

  resultat = a;
  /* post-incrementation : la valeur est utilisee *avant* l'increment */
  valeur = resultat++;
  printf("resultat = %d; resultat++ vaut %d, puis resultat vaut %d\n",
         a, valeur, resultat);

  resultat = a;
  /* pre-incrementation : l'increment a lieu *avant* l'utilisation */
  valeur = ++resultat;
  printf("resultat = %d; ++resultat vaut %d, et resultat vaut %d\n",
         a, valeur, resultat);

  resultat = a;
  valeur = resultat--;
  printf("resultat = %d; resultat-- vaut %d, puis resultat vaut %d\n",
         a, valeur, resultat);

  resultat = a;
  valeur = --resultat;
  printf("resultat = %d; --resultat vaut %d, et resultat vaut %d\n",
         a, valeur, resultat);

  /* --- operateurs logiques --- */
  printf("\nOperateurs logiques\n");
  printf("-------------------\n");

  printf("(a > b) && (b > 0) : %d\n", (a > b) && (b > 0));
  printf("(a < b) || (b > 0) : %d\n", (a < b) || (b > 0));
  printf("!(a == b)          : %d\n", !(a == b));

  return 0;
}
