/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * TP5 - Exercices 5.4, 5.5 et 5.6 : serveur
 *
 * Le serveur attend les connexions des clients. Pour chaque client, un
 * processus fils est cree (fork) et dialogue avec lui dans une boucle
 * infinie.
 *
 * Format des messages recus :
 *   "message: <texte>"                 -> exercice 5.4
 *   "calcule: <operateur> <n1> [<n2>]" -> exercices 5.5 et 5.6
 *
 * Compilation : make
 * Utilisation : ./serveur
 */

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "serveur.h"

int socketfd; // Déclaration globale de socketfd

/**
 * Cette fonction envoie un message (*data) au client (client_socket_fd)
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message à envoyer.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int renvoie_message(int client_socket_fd, char *data)
{
  int data_size = (int)write(client_socket_fd, (void *)data, strlen(data));

  if (data_size < 0)
  {
    perror("Erreur d'écriture");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

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

/**
 * Exercice 5.5 - Reception et calcul d'une operation envoyee par le
 * client.
 *
 * Le message recu a la forme "calcule: <operateur> <num1> [<num2>]".
 * Le serveur extrait l'operateur et les nombres, effectue le calcul,
 * puis renvoie "calcule: <resultat>" au client.
 *
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message reçu.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_numeros_calcule(int client_socket_fd, const char *data)
{
  char reponse[TAILLE_MESSAGE];
  const char *deux_points;
  char op = '\0';
  double num1 = 0.0;
  double num2 = 0.0;
  double resultat = 0.0;
  int lus;

  /* on se place juste apres le deux-points de "calcule:" */
  deux_points = strchr(data, ':');
  if (deux_points == NULL)
  {
    snprintf(reponse, sizeof(reponse), "erreur: message mal forme");
    return renvoie_message(client_socket_fd, reponse);
  }

  /* extraction de l'operateur et des nombres */
  lus = sscanf(deux_points + 1, " %c %lf %lf", &op, &num1, &num2);
  if (lus < 2)
  {
    snprintf(reponse, sizeof(reponse), "erreur: operation illisible");
    return renvoie_message(client_socket_fd, reponse);
  }

  /* selection de l'operation demandee */
  switch (op)
  {
  case '+':
    resultat = num1 + num2;
    break;

  case '-':
    resultat = num1 - num2;
    break;

  case '*':
    resultat = num1 * num2;
    break;

  case '/':
    if (num2 == 0.0)
    {
      snprintf(reponse, sizeof(reponse), "erreur: division par zero");
      return renvoie_message(client_socket_fd, reponse);
    }
    resultat = num1 / num2;
    break;

  case '%':
    if ((long)num2 == 0)
    {
      snprintf(reponse, sizeof(reponse), "erreur: modulo par zero");
      return renvoie_message(client_socket_fd, reponse);
    }
    resultat = (double)((long)num1 % (long)num2);
    break;

  case '~':
    /* operateur unaire : seul num1 est utilise */
    resultat = (double)(~(long)num1);
    break;

  case '&':
    resultat = (double)((long)num1 & (long)num2);
    break;

  case '|':
    resultat = (double)((long)num1 | (long)num2);
    break;

  default:
    snprintf(reponse, sizeof(reponse), "erreur: operateur inconnu '%c'", op);
    return renvoie_message(client_socket_fd, reponse);
  }

  printf("Calcul demande : %c %g %g = %g\n", op, num1, num2, resultat);

  snprintf(reponse, sizeof(reponse), "calcule: %g", resultat);

  return renvoie_message(client_socket_fd, reponse);
}

/**
 * Cette fonction lit les données envoyées par le client,
 * et renvoie un message en réponse.
 *
 * Exercice 5.4 : au lieu de renvoyer le message recu, le serveur
 * demande a son utilisateur de saisir une reponse. Si l'entree standard
 * du serveur n'est pas disponible (redirection, fin de fichier), le
 * message recu est renvoye tel quel.
 *
 * @param client_socket_fd : Le descripteur de socket du client.
 * @param data : Le message reçu.
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int recois_envoie_message(int client_socket_fd, char *data)
{
  char code[16];
  char saisie[TAILLE_MESSAGE - 16];
  char reponse[TAILLE_MESSAGE];

  printf("Message reçu: %s\n", data);

  /* extraction du code (le premier mot du message) */
  if (sscanf(data, "%15s", code) != 1)
  {
    return EXIT_SUCCESS;
  }

  /* exercices 5.5 et 5.6 : une demande de calcul */
  if (strcmp(code, "calcule:") == 0)
  {
    return recois_numeros_calcule(client_socket_fd, data);
  }

  /* exercice 5.4 : un simple message */
  if (strcmp(code, "message:") == 0)
  {
    printf("Votre reponse : ");
    fflush(stdout);

    if (fgets(saisie, sizeof(saisie), stdin) == NULL)
    {
      /* pas d'entree disponible : on renvoie le message recu */
      printf("(pas de saisie possible : le message recu est renvoye)\n");
      return renvoie_message(client_socket_fd, data);
    }

    enleve_retour_ligne(saisie);

    snprintf(reponse, sizeof(reponse), "message: %s", saisie);
    return renvoie_message(client_socket_fd, reponse);
  }

  /* code inconnu : on renvoie le message tel quel */
  return renvoie_message(client_socket_fd, data);
}

/**
 * Gestionnaire de signal pour Ctrl+C (SIGINT).
 * @param signal : Le signal capturé (doit être SIGINT pour Ctrl+C).
 */
void gestionnaire_ctrl_c(int signal)
{
  (void)signal;

  printf("\nSignal Ctrl+C capturé. Sortie du programme.\n");

  // Fermer le socket si ouvert
  if (socketfd != -1)
  {
    close(socketfd);
  }

  exit(0); // Quitter proprement le programme.
}

/**
 * Gère la communication avec un client spécifique, dans une boucle
 * infinie (exercice 5.6 : le serveur doit pouvoir traiter plusieurs
 * demandes successives du même client).
 *
 * @param client_socket_fd Le descripteur de socket du client à gérer.
 */
void gerer_client(int client_socket_fd)
{
  char data[TAILLE_MESSAGE];

  while (1)
  {
    // Réinitialisation des données
    memset(data, 0, sizeof(data));

    // Lecture des données envoyées par le client
    int data_size = (int)read(client_socket_fd, data, sizeof(data) - 1);

    if (data_size <= 0)
    {
      // Erreur de réception ou déconnexion du client
      if (data_size == 0)
      {
        // Le client a fermé la connexion proprement
        printf("Client déconnecté.\n");
      }
      else
      {
        perror("Erreur de réception");
      }

      // Fermer le socket du client et sortir de la boucle de communication
      close(client_socket_fd);
      break; // Sortir de la boucle de communication avec ce client
    }

    recois_envoie_message(client_socket_fd, data);
  }
}

/**
 * Configuration du serveur socket et attente de connexions.
 */
int main(void)
{
  int bind_status;                // Statut de la liaison
  struct sockaddr_in server_addr; // Structure pour l'adresse du serveur
  int option = 1;                 // Option pour setsockopt

  /* affichage ligne par ligne, y compris lorsque la sortie est
   * redirigee vers un fichier */
  setvbuf(stdout, NULL, _IOLBF, 0);

  // Création d'une socket
  socketfd = socket(AF_INET, SOCK_STREAM, 0);

  // Vérification si la création de la socket a réussi
  if (socketfd < 0)
  {
    perror("Impossible d'ouvrir une socket");
    return -1;
  }

  // Configuration de l'option SO_REUSEADDR pour permettre la réutilisation de l'adresse du serveur
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  // Initialisation de la structure server_addr
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);       // Port d'écoute du serveur
  server_addr.sin_addr.s_addr = INADDR_ANY; // Accepter les connexions de n'importe quelle adresse

  // Liaison de l'adresse à la socket
  bind_status = bind(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Vérification si la liaison a réussi
  if (bind_status < 0)
  {
    perror("bind");
    return (EXIT_FAILURE);
  }

  // Enregistrement de la fonction de gestion du signal Ctrl+C
  signal(SIGINT, gestionnaire_ctrl_c);

  /* Les processus fils termines sont automatiquement recuperes :
   * cela evite de laisser des processus zombies. */
  signal(SIGCHLD, SIG_IGN);

  // Mise en attente de la socket pour accepter les connexions entrantes jusqu'à une limite de 10 connexions en attente
  listen(socketfd, 10);

  printf("Serveur en attente de connexions...\n");

  struct sockaddr_in client_addr;                     // Structure pour l'adresse du client
  unsigned int client_addr_len = sizeof(client_addr); // Longueur de la structure client_addr
  int client_socket_fd;                               // Descripteur de socket du client

  // Boucle infinie
  while (1)
  {
    // Nouvelle connexion cliente
    client_socket_fd = accept(socketfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (client_socket_fd < 0)
    {
      perror("accept");
      continue; // Continuer à attendre d'autres connexions en cas d'erreur
    }

    // Créer un processus enfant pour gérer la communication avec le client
    pid_t child_pid = fork();

    if (child_pid == 0)
    {
      // Code du processus enfant
      close(socketfd); // Fermer la socket du serveur dans le processus enfant
      gerer_client(client_socket_fd);
      exit(0); // Quitter le processus enfant
    }
    else if (child_pid < 0)
    {
      perror("fork");
      close(client_socket_fd); // Fermer le socket du client en cas d'erreur
    }
    else
    {
      // Code du processus parent
      close(client_socket_fd); // Fermer le socket du client dans le processus parent
    }
  }

  // Le programme ne devrait jamais atteindre cette ligne dans la boucle infinie
  return 0;
}
