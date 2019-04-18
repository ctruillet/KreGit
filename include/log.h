/**
 * @file log.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief En-tête des fonctions chargées de generer et ecrire dans un fichier .log
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __LOG_H__

#include <stdio.h>

/**
 * @brief Crée un fichier log 
 * 
 * @param FICHIER 
 */
void crea_log(char * FICHIER);

/**
 * @brief Ecrit dans le fichier log
 * 
 * @param fichier 
 * @param str 
 * @return int 
 */
int w_log(char * FICHIER, char * str);


