/*
 * librairie log.h
 */
#define __LOG_H__


/*
Derniere modification : 2018-12-02 17:44:02
Par : Clement
*/

// Création du fichier .log 
void crea_log(char * FICHIER);

// Ecriture dans le fichier .log
int w_log(FILE * fichier, char * str);