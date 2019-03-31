/*
 * librairie log.h
 */
#define __LOG_H__

#include <stdio.h>

/*
Derniere modification : 31/03/2019
Par : Clement
*/

// Création du fichier .log 
void crea_log(char * FICHIER);

// Ecriture dans le fichier .log
int w_log(FILE * fichier, char * str);