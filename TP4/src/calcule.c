/*
 * Exercice 4.4 - Calculatrice en ligne de commande
 *
 * Les fonctions de calcul sont celles de operator.c.
 * L'operateur et les deux nombres sont lus sur la ligne de commande.
 *
 * Compilation : gcc -Wall -Wextra -o calcule calcule.c operator.c
 *
 * Utilisation :
 *   $ ./calcule + 10 5
 *   Resultat : 15
 *   $ ./calcule '*' 7 8
 *   Resultat : 56
 *   $ ./calcule '~' 16
 *   Resultat : -17
 *
 * Attention : les caracteres *, |, &, ~ sont interpretes par le shell,
 * il faut donc les proteger par des apostrophes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "operator.h"

/* Affiche la maniere d'utiliser le programme. */
static void usage(const char *nom_du_programme)
{
  fprintf(stderr, "Utilisation : %s <operateur> <num1> [num2]\n", nom_du_programme);
  fprintf(stderr, "  operateurs : + - '*' / '%%' '&' '|' '~'\n");
  fprintf(stderr, "  '~' est unaire : un seul nombre suffit.\n");
  fprintf(stderr, "Exemples :\n");
  fprintf(stderr, "  %s + 10 5\n", nom_du_programme);
  fprintf(stderr, "  %s '*' 7 8\n", nom_du_programme);
}

int main(int argc, char *argv[])
{
  char op;
  int num1;
  int num2 = 0;
  int resultat;

  /* il faut au minimum : le nom du programme, un operateur et un nombre */
  if (argc < 3)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  /* l'operateur doit tenir sur un seul caractere */
  if (strlen(argv[1]) != 1)
  {
    fprintf(stderr, "Erreur : operateur invalide '%s'.\n", argv[1]);
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  op = argv[1][0];

  /* conversion des arguments en entiers */
  num1 = atoi(argv[2]);

  if (op == '~')
  {
    /* operateur unaire : le deuxieme nombre est facultatif */
    if (argc > 3)
    {
      fprintf(stderr, "Avertissement : '~' est unaire, '%s' est ignore.\n", argv[3]);
    }
  }
  else
  {
    if (argc < 4)
    {
      fprintf(stderr, "Erreur : l'operateur '%c' attend deux nombres.\n", op);
      usage(argv[0]);
      return EXIT_FAILURE;
    }
    num2 = atoi(argv[3]);
  }

  /* calcule() contient la structure switch qui selectionne l'operation */
  if (calcule(num1, num2, op, &resultat) != 0)
  {
    return EXIT_FAILURE;
  }

  printf("Resultat : %d\n", resultat);

  return EXIT_SUCCESS;
}
