/*
 * TP4 - Programme principal commun aux exercices 4.1, 4.2 et 4.7
 *
 * Une seule fonction main() qui demande a l'utilisateur quel exercice
 * il souhaite executer, puis appelle la fonction d'entree correspondante :
 *
 *   4.1 -> exercice_operateur()  (operator.c)
 *   4.2 -> exercice_fichier()    (fichier.c)
 *   4.7 -> exercice_liste()      (liste.c)
 *
 * Compilation :
 *   gcc -Wall -Wextra -o main main.c operator.c fichier.c liste.c
 */

#include <stdio.h>

#include "fichier.h"
#include "liste.h"
#include "operator.h"

/* Affiche le menu des exercices disponibles. */
static void affiche_menu(void)
{
  printf("\n");
  printf("=========================================\n");
  printf("            TP4 - Menu principal         \n");
  printf("=========================================\n");
  printf("1. Exercice 4.1 - Calcul avec operateurs\n");
  printf("2. Exercice 4.2 - Gestion de fichiers\n");
  printf("3. Exercice 4.7 - Liste de couleurs\n");
  printf("0. Quitter\n");
  printf("Votre choix : ");
}

int main(void)
{
  int choix;

  while (1)
  {
    affiche_menu();

    /* scanf renvoie le nombre de valeurs lues : 1 si tout va bien */
    if (scanf("%d", &choix) != 1)
    {
      printf("\nEntree invalide ou fin de fichier. Arret.\n");
      return 1;
    }

    printf("\n");

    /* selection de l'exercice a executer */
    switch (choix)
    {
    case 1:
      exercice_operateur();
      break;

    case 2:
      exercice_fichier();
      break;

    case 3:
      exercice_liste();
      break;

    case 0:
      printf("Au revoir.\n");
      return 0;

    default:
      printf("Choix invalide : entrez 0, 1, 2 ou 3.\n");
      break;
    }
  }

  return 0;
}
