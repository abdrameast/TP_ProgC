/*
 * Exercice 4.0 - Debogage avec gdb
 *
 * Ce fichier contient volontairement l'erreur decrite dans le README :
 * la condition d'arret de la boucle utilise sizeof(tableau), qui vaut
 * 400 (100 elements x 4 octets) et non 100. On ecrit donc bien au-dela
 * de la fin du tableau, ce qui provoque un "stack smashing detected".
 *
 * Compilation avec les informations de debogage :
 *   $ gcc -ggdb3 -o erreurs erreurs.c
 *   $ gdb ./erreurs
 *   (gdb) r          -> le programme s'arrete (SIGABRT)
 *   (gdb) bt         -> la pile d'appels designe main() dans erreurs.c
 *   (gdb) break erreurs.c:35
 *   (gdb) r
 *   (gdb) p compteur
 *   (gdb) p tableau[0]@5
 *   (gdb) n
 *   (gdb) continue
 *   (gdb) quit
 *
 * La correction consiste a comparer `compteur` au nombre d'elements :
 *   sizeof(tableau) / sizeof(tableau[0])
 * (voir la fonction version_corrigee() plus bas).
 */

#include <stdio.h>

int main(void)
{
  int tableau[100];
  size_t compteur;

  /* ERREUR : sizeof(tableau) vaut 400 octets, pas 100 elements. */
  for (compteur = 0; compteur < sizeof(tableau); compteur++)
  {
    tableau[compteur] = tableau[compteur] * 2;
  }

  printf("Fin du programme\n");

  return 0;
}

#if 0
/* Version corrigee : le nombre d'elements est obtenu en divisant la
 * taille totale du tableau par la taille d'un element. */
void version_corrigee(void)
{
  int tableau[100];
  size_t nb_elements = sizeof(tableau) / sizeof(tableau[0]); /* 100 */
  size_t compteur;

  for (compteur = 0; compteur < nb_elements; compteur++)
  {
    tableau[compteur] = 0;      /* initialisation avant lecture */
    tableau[compteur] = tableau[compteur] * 2;
  }
}
#endif
