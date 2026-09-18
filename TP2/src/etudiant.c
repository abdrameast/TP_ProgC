/*
 * Exercice 2.5 - Gestion des donnees etudiantes avec des tableaux
 *
 * Les informations de 5 etudiant.e.s sont stockees dans des tableaux
 * paralleles : noms, prenoms, adresses, notes de programmation en C et
 * notes de systeme d'exploitation.
 *
 * Les tableaux sont parcourus avec la notation pointeur *(s + i),
 * comme le suggere l'enonce.
 *
 * Compilation : gcc -Wall -Wextra -o etudiant etudiant.c
 */

#include <stdio.h>

#define NB_ETUDIANTS 5
#define TAILLE_TEXTE 64

int main(void)
{
  /* nom, prenom et adresse : des tableaux de chaines de caracteres */
  char noms[NB_ETUDIANTS][TAILLE_TEXTE] = {
      "Dupont",
      "Martin",
      "Bernard",
      "Petit",
      "Moreau"};

  char prenoms[NB_ETUDIANTS][TAILLE_TEXTE] = {
      "Marie",
      "Pierre",
      "Fatou",
      "Karim",
      "Alice"};

  char adresses[NB_ETUDIANTS][TAILLE_TEXTE] = {
      "20, Boulevard Niels Bohr, Lyon",
      "22, Boulevard Niels Bohr, Lyon",
      "5, Rue de la Republique, Lyon",
      "12, Avenue Jean Jaures, Villeurbanne",
      "3, Place Bellecour, Lyon"};

  /* les notes dans les deux modules */
  float notes_programmation[NB_ETUDIANTS] = {16.5f, 14.0f, 18.0f, 11.5f, 13.0f};
  float notes_systeme[NB_ETUDIANTS] = {12.1f, 14.1f, 15.5f, 9.0f, 17.25f};

  /* deux pointeurs pour parcourir les tableaux de notes */
  float *p_prog = notes_programmation;
  float *p_sys = notes_systeme;

  int i;

  printf("Liste des etudiant.e.s\n");
  printf("======================\n\n");

  for (i = 0; i < NB_ETUDIANTS; i++)
  {
    printf("Etudiant.e %d :\n", i + 1);
    printf("  Nom     : %s\n", noms[i]);
    printf("  Prenom  : %s\n", prenoms[i]);
    printf("  Adresse : %s\n", adresses[i]);
    /* acces aux notes avec la notation *(s + i) */
    printf("  Note Programmation en C      : %.2f\n", *(p_prog + i));
    printf("  Note Systeme d'exploitation  : %.2f\n", *(p_sys + i));
    printf("  Moyenne : %.2f\n\n", (*(p_prog + i) + *(p_sys + i)) / 2.0f);
  }

  return 0;
}
