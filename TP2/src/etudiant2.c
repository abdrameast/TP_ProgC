/*
 * Exercice 2.6 - Gestion des donnees d'etudiant.e.s avec des structures
 *
 * Les memes informations que dans l'exercice 2.5, mais regroupees dans
 * une structure `etudiant`. Les chaines sont initialisees avec strcpy.
 *
 * Compilation : gcc -Wall -Wextra -o etudiant2 etudiant2.c
 */

#include <stdio.h>
#include <string.h> /* pour strcpy */

#define NB_ETUDIANTS 5
#define TAILLE_TEXTE 64

/* Structure qui regroupe toutes les informations d'un.e etudiant.e. */
struct etudiant
{
  char nom[TAILLE_TEXTE];
  char prenom[TAILLE_TEXTE];
  char adresse[TAILLE_TEXTE];
  float note1; /* Programmation en C */
  float note2; /* Systeme d'exploitation */
};

int main(void)
{
  /* un tableau de 5 structures */
  struct etudiant etudiants[NB_ETUDIANTS];
  int i;

  /* initialisation des chaines avec strcpy et des notes par affectation */
  strcpy(etudiants[0].nom, "Dupont");
  strcpy(etudiants[0].prenom, "Marie");
  strcpy(etudiants[0].adresse, "20, Boulevard Niels Bohr, Lyon");
  etudiants[0].note1 = 16.5f;
  etudiants[0].note2 = 12.1f;

  strcpy(etudiants[1].nom, "Martin");
  strcpy(etudiants[1].prenom, "Pierre");
  strcpy(etudiants[1].adresse, "22, Boulevard Niels Bohr, Lyon");
  etudiants[1].note1 = 14.0f;
  etudiants[1].note2 = 14.1f;

  strcpy(etudiants[2].nom, "Bernard");
  strcpy(etudiants[2].prenom, "Fatou");
  strcpy(etudiants[2].adresse, "5, Rue de la Republique, Lyon");
  etudiants[2].note1 = 18.0f;
  etudiants[2].note2 = 15.5f;

  strcpy(etudiants[3].nom, "Petit");
  strcpy(etudiants[3].prenom, "Karim");
  strcpy(etudiants[3].adresse, "12, Avenue Jean Jaures, Villeurbanne");
  etudiants[3].note1 = 11.5f;
  etudiants[3].note2 = 9.0f;

  strcpy(etudiants[4].nom, "Moreau");
  strcpy(etudiants[4].prenom, "Alice");
  strcpy(etudiants[4].adresse, "3, Place Bellecour, Lyon");
  etudiants[4].note1 = 13.0f;
  etudiants[4].note2 = 17.25f;

  /* affichage de toutes les structures */
  for (i = 0; i < NB_ETUDIANTS; i++)
  {
    printf("Etudiant.e %d :\n", i + 1);
    printf("Nom : %s\n", etudiants[i].nom);
    printf("Prenom : %s\n", etudiants[i].prenom);
    printf("Adresse : %s\n", etudiants[i].adresse);
    printf("Note 1 : %.2f\n", etudiants[i].note1);
    printf("Note 2 : %.2f\n", etudiants[i].note2);
    printf("\n");
  }

  return 0;
}
