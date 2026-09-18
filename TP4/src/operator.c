/*
 * Exercice 4.1 - Calcul avec operateurs (implementation)
 *
 * Compilation : gcc -Wall -Wextra -c operator.c
 */

#include <stdio.h>

#include "operator.h"

/* num1 + num2 */
int somme(int num1, int num2)
{
  return num1 + num2;
}

/* num1 - num2 */
int difference(int num1, int num2)
{
  return num1 - num2;
}

/* num1 * num2 */
int produit(int num1, int num2)
{
  return num1 * num2;
}

/* num1 / num2 : l'appelant doit s'assurer que num2 n'est pas nul */
int quotient(int num1, int num2)
{
  if (num2 == 0)
  {
    return 0;
  }
  return num1 / num2;
}

/* num1 % num2 : l'appelant doit s'assurer que num2 n'est pas nul */
int modulo(int num1, int num2)
{
  if (num2 == 0)
  {
    return 0;
  }
  return num1 % num2;
}

/* ET bit a bit */
int et(int num1, int num2)
{
  return num1 & num2;
}

/* OU bit a bit */
int ou(int num1, int num2)
{
  return num1 | num2;
}

/* NON bit a bit : operateur unaire, num2 n'est pas utilise */
int negation(int num1, int num2)
{
  (void)num2; /* parametre volontairement inutilise */
  return ~num1;
}

/*
 * Selection de l'operation avec une structure switch.
 */
int calcule(int num1, int num2, char op, int *resultat)
{
  if (resultat == NULL)
  {
    return -1;
  }

  switch (op)
  {
  case '+':
    *resultat = somme(num1, num2);
    break;

  case '-':
    *resultat = difference(num1, num2);
    break;

  case '*':
    *resultat = produit(num1, num2);
    break;

  case '/':
    if (num2 == 0)
    {
      fprintf(stderr, "Erreur : division par zero.\n");
      return -1;
    }
    *resultat = quotient(num1, num2);
    break;

  case '%':
    if (num2 == 0)
    {
      fprintf(stderr, "Erreur : modulo par zero.\n");
      return -1;
    }
    *resultat = modulo(num1, num2);
    break;

  case '&':
    *resultat = et(num1, num2);
    break;

  case '|':
    *resultat = ou(num1, num2);
    break;

  case '~':
    *resultat = negation(num1, num2);
    break;

  default:
    fprintf(stderr, "Erreur : operateur inconnu '%c'.\n", op);
    return -1;
  }

  return 0;
}

/*
 * Fonction d'entree de l'exercice 4.1 : demande les deux nombres et
 * l'operateur a l'utilisateur, puis affiche le resultat.
 */
int exercice_operateur(void)
{
  int num1;
  int num2;
  char op;
  int resultat;

  printf("Entrez num1 : ");
  if (scanf("%d", &num1) != 1)
  {
    fprintf(stderr, "Erreur de saisie pour num1.\n");
    return -1;
  }

  printf("Entrez num2 : ");
  if (scanf("%d", &num2) != 1)
  {
    fprintf(stderr, "Erreur de saisie pour num2.\n");
    return -1;
  }

  /* l'espace avant %c ignore les espaces et retours a la ligne restants */
  printf("Entrez l'operateur (+, -, *, /, %%, &, |, ~) : ");
  if (scanf(" %c", &op) != 1)
  {
    fprintf(stderr, "Erreur de saisie pour l'operateur.\n");
    return -1;
  }

  if (calcule(num1, num2, op, &resultat) != 0)
  {
    return -1;
  }

  printf("Resultat : %d\n", resultat);

  return 0;
}
