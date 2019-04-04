/**
 * @file log.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions chargées de generer et ecrire dans un fichier .log
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/log.h"

void crea_log(char * FICHIER){
  time_t temps;
  struct tm date;

  // Recuperation de la date et l'heure actuelle.
  time(&temps);
  date=*localtime(&temps);

  // Remplissage de la chaîne avec en date_heure
  strftime(FICHIER, 128, "log/%m-%d-%Y_%H.%M.%S.log", &date);
}

int w_log(FILE * fichier, char * str){  
  char heure[128];
  time_t temps;
  struct tm date;

  // Recuperation de l'heure actuelle.
  time(&temps);
  date=*localtime(&temps);
  strftime(heure, 128, "[%H:%M:%S]", &date);

  // Ouveture du fichier

  if (fichier != NULL){ // Ecriture dans le fichier
        fprintf(fichier, "%s %s\n", heure, str);
        return 0;
    }else{ // Si echec de l'ouverture, on affiche un message d'erreur
        printf("Impossible d'ouvrir le fichier log\n");
        return 1;
    }
}