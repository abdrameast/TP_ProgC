/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP5 - Exercices 5.4, 5.5 et 5.6 : client
 *
 * Format des messages echanges avec le serveur :
 *   "message: <texte>"                -> un simple message ;
 *   "calcule: <operateur> <n1> [<n2>]" -> une demande de calcul.
 *
 * Compilation : make
 * Utilisation :
 *   ./client                       -> mode interactif (5.4 et 5.5)
 *   ./client --notes ../etudiant   -> calcul sur les notes (5.6)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

#include "client.h"

#define NB_ETUDIANTS 5
#define NB_NOTES 5

/* Retire le retour a la ligne laisse par fgets. */
static void enleve_retour_ligne(char *chaine)
{
  size_t longueur = strlen(chaine);

  while (longueur > 0 && (chaine[longueur - 1] == '\n' || chaine[longueur - 1] == '\r'))
  {
    chaine[longueur - 1] = '\0';
    longueur--;
  }
}

/*
 * Reconnait une demande de calcul de la forme "calcule : + 23 45"
 * (les espaces autour du deux-points sont facultatifs).
 *
 * Renvoie le nombre d'operandes lues (1 ou 2), ou 0 si le message
 * n'est pas une demande de calcul.
 */
static int analyse_demande_calcul(const char *message, char *op,
                                  double *num1, double *num2)
{
  const char *p = message;
  int lus;

  /* le message doit commencer par le mot "calcule" */
  if (strncmp(p, "calcule", 7) != 0)
  {
    return 0;
  }
  p += 7;

  /* des espaces facultatifs, puis le deux-points */
  while (*p == ' ' || *p == '\t')
  {
    p++;
  }
  if (*p != ':')
  {
    return 0;
  }
  p++;

  /* l'operateur suivi d'un ou deux nombres */
  lus = sscanf(p, " %c %lf %lf", op, num1, num2);

  if (lus == 3)
  {
    return 2;
  }
  if (lus == 2)
  {
    *num2 = 0.0;
    return 1;
  }

  return 0;
}

/*
 * Exercice 5.5 - Envoi d'une operation de calcul au serveur.
 */
int envoie_operateur_numeros(int socketfd, char op, double num1, double num2,
                             int nb_numeros, double *resultat)
{
  char data[TAILLE_MESSAGE];
  int write_status;
  int read_status;

  memset(data, 0, sizeof(data));

  /* construction du message "calcule: <op> <num1> [<num2>]" */
  if (nb_numeros >= 2)
  {
    snprintf(data, sizeof(data), "calcule: %c %g %g", op, num1, num2);
  }
  else
  {
    snprintf(data, sizeof(data), "calcule: %c %g", op, num1);
  }

  printf("Envoi au serveur : %s\n", data);

  write_status = (int)write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'ecriture");
    return -1;
  }

  /* lecture de la reponse du serveur */
  memset(data, 0, sizeof(data));
  read_status = (int)read(socketfd, data, sizeof(data) - 1);
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }
  if (read_status == 0)
  {
    fprintf(stderr, "Le serveur a ferme la connexion.\n");
    return -1;
  }

  printf("Message recu: %s\n", data);

  /* extraction du resultat : "calcule: <resultat>" */
  if (resultat != NULL)
  {
    const char *deux_points = strchr(data, ':');

    if (deux_points == NULL || sscanf(deux_points + 1, "%lf", resultat) != 1)
    {
      fprintf(stderr, "Reponse du serveur illisible : %s\n", data);
      return -1;
    }
  }

  return 0;
}

/*
 * Exercice 5.4 - Envoi et reception d'un message.
 *
 * Si la saisie de l'utilisateur est une demande de calcul, elle est
 * transmise a envoie_operateur_numeros() (exercice 5.5).
 */
int envoie_recois_message(int socketfd)
{
  char data[TAILLE_MESSAGE];
  /* la place de l'etiquette "message: " est reservee dans data */
  char message[TAILLE_MESSAGE - 16];
  char op = '+';
  double num1 = 0.0;
  double num2 = 0.0;
  int nb_numeros;
  int write_status;
  int read_status;

  /* Demande a l'utilisateur d'entrer un message */
  printf("Votre message (max 1000 caracteres): ");
  fflush(stdout);

  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    /* fin de l'entree standard : on arrete le client */
    return -1;
  }
  enleve_retour_ligne(message);

  /* une ligne vide est ignoree */
  if (message[0] == '\0')
  {
    return 0;
  }

  /* demande de calcul ? (exercice 5.5) */
  nb_numeros = analyse_demande_calcul(message, &op, &num1, &num2);
  if (nb_numeros > 0)
  {
    return envoie_operateur_numeros(socketfd, op, num1, num2, nb_numeros, NULL);
  }

  /* sinon : un simple message */
  memset(data, 0, sizeof(data));
  snprintf(data, sizeof(data), "message: %s", message);

  write_status = (int)write(socketfd, data, strlen(data));
  if (write_status < 0)
  {
    perror("Erreur d'ecriture");
    return -1;
  }

  /* Lit la reponse du serveur */
  memset(data, 0, sizeof(data));
  read_status = (int)read(socketfd, data, sizeof(data) - 1);
  if (read_status < 0)
  {
    perror("Erreur de lecture");
    return -1;
  }
  if (read_status == 0)
  {
    fprintf(stderr, "Le serveur a ferme la connexion.\n");
    return -1;
  }

  printf("Message recu: %s\n", data);

  return 0;
}

/*
 * Exercice 5.6 - Lecture d'une note dans un fichier.
 * Renvoie 0 en cas de succes, -1 en cas d'erreur.
 */
static int lire_note(const char *chemin, double *note)
{
  FILE *fichier = fopen(chemin, "r");

  if (fichier == NULL)
  {
    perror(chemin);
    return -1;
  }

  if (fscanf(fichier, "%lf", note) != 1)
  {
    fprintf(stderr, "Note illisible dans %s\n", chemin);
    fclose(fichier);
    return -1;
  }

  fclose(fichier);

  return 0;
}

/*
 * Exercice 5.6 - Calculs sur les notes des etudiants.
 *
 * Le client lit lui-meme les fichiers : le serveur ne connait que des
 * operations arithmetiques simples.
 *
 * Pour chaque etudiant :
 *   "+ note1 note2", "+ somme note3", ... puis "/ somme 5"
 * Puis, pour la classe : la somme des moyennes divisee par 5.
 */
int calcule_notes_etudiants(int socketfd, const char *dossier)
{
  double moyennes[NB_ETUDIANTS];
  double somme_classe = 0.0;
  double moyenne_classe = 0.0;
  int etudiant;

  for (etudiant = 1; etudiant <= NB_ETUDIANTS; etudiant++)
  {
    double notes[NB_NOTES];
    double somme = 0.0;
    double moyenne = 0.0;
    int note;

    printf("\n=== Etudiant %d ===\n", etudiant);

    /* lecture des notes de l'etudiant */
    for (note = 1; note <= NB_NOTES; note++)
    {
      char chemin[512];

      snprintf(chemin, sizeof(chemin), "%s/%d/note%d.txt", dossier, etudiant, note);
      if (lire_note(chemin, &notes[note - 1]) != 0)
      {
        return -1;
      }
      printf("note%d = %g\n", note, notes[note - 1]);
    }

    /* somme des notes, calculee par le serveur deux nombres a la fois */
    if (envoie_operateur_numeros(socketfd, '+', notes[0], notes[1], 2, &somme) != 0)
    {
      return -1;
    }
    for (note = 2; note < NB_NOTES; note++)
    {
      if (envoie_operateur_numeros(socketfd, '+', somme, notes[note], 2, &somme) != 0)
      {
        return -1;
      }
    }

    /* moyenne de l'etudiant : la somme divisee par le nombre de notes */
    if (envoie_operateur_numeros(socketfd, '/', somme, (double)NB_NOTES, 2, &moyenne) != 0)
    {
      return -1;
    }

    printf("Somme des notes de l'etudiant %d   : %g\n", etudiant, somme);
    printf("Moyenne des notes de l'etudiant %d : %g\n", etudiant, moyenne);

    moyennes[etudiant - 1] = moyenne;
  }

  /* moyenne de la classe : somme des moyennes divisee par le nombre
   * d'etudiants, la encore calculee par le serveur */
  if (envoie_operateur_numeros(socketfd, '+', moyennes[0], moyennes[1], 2,
                               &somme_classe) != 0)
  {
    return -1;
  }
  for (etudiant = 2; etudiant < NB_ETUDIANTS; etudiant++)
  {
    if (envoie_operateur_numeros(socketfd, '+', somme_classe, moyennes[etudiant], 2,
                                 &somme_classe) != 0)
    {
      return -1;
    }
  }

  if (envoie_operateur_numeros(socketfd, '/', somme_classe, (double)NB_ETUDIANTS, 2,
                               &moyenne_classe) != 0)
  {
    return -1;
  }

  printf("\n=== Classe ===\n");
  printf("Moyenne de la classe : %g\n", moyenne_classe);

  return 0;
}

int main(int argc, char *argv[])
{
  int socketfd;
  struct sockaddr_in server_addr;
  int connect_status;

  /* affichage ligne par ligne, y compris lorsque la sortie est
   * redirigee vers un fichier */
  setvbuf(stdout, NULL, _IOLBF, 0);

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // demande de connection au serveur
  connect_status = connect(socketfd, (struct sockaddr *)&server_addr,
                           sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  if (argc >= 2 && strcmp(argv[1], "--notes") == 0)
  {
    /* exercice 5.6 : calculs sur les notes des etudiants */
    const char *dossier = (argc >= 3) ? argv[2] : "../etudiant";

    calcule_notes_etudiants(socketfd, dossier);
  }
  else
  {
    /* exercices 5.4 et 5.5 : mode interactif */
    printf("Tapez un message, ou une demande de calcul, par exemple :\n");
    printf("  calcule : + 23 45\n");
    printf("(Ctrl+D pour quitter)\n\n");

    while (envoie_recois_message(socketfd) == 0)
    {
      /* on continue tant que l'echange se passe bien */
    }
  }

  close(socketfd);

  return EXIT_SUCCESS;
}
