#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/log.h"

/*
* Clement Truillet 
* Derniere modification : 23/02/2019
*/

void crea_log(char * FICHIER){
  time_t temps;
  struct tm date;

  // Recuperation de la date et l'heure actuelle.
  time(&temps);
  date=*localtime(&temps);

  // Remplissage de la chaîne avec en date_heure
  strftime(FICHIER, 128, "../log/%m-%d-%Y_%H.%M.%S.log", &date);
  
  // Ouverture et création du fichier .log
  FILE* fichier = NULL;
  fichier = fopen(FICHIER,"w+");
  fclose(fichier);
  
  //Ecriture dans log
  w_log(FICHIER,"Création du fichier .log");

}

int w_log(char * FICHIER, char * str){
  FILE* fichier = NULL;
  char heure[128];
  time_t temps;
  struct tm date;

  // Recuperation de l'heure actuelle.
  time(&temps);
  date=*localtime(&temps);
  strftime(heure, 128, "[%H:%M:%S]", &date);

  // Ouveture du fichier
  fichier = fopen(FICHIER,"a"); 

  if (fichier != NULL) // Ecriture dans le fichier
    {
        fprintf(fichier, "%s %s\n", heure, str);
        fclose(fichier);
        return 0;
    }
    else // Si echec de l'ouverture, on affiche un message d'erreur
    {
        printf("Impossible d'ouvrir le fichier %s\n",FICHIER);
        return 1;
    }
}