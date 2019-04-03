/**
 * @file encrypt.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions chargées du chiffrement de mot de passe
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <crypt.h>
#include "../include/user_account.h"
#include "../include/encrypt.h"
#define _XOPEN_SOURCE

/**
 * @brief Encrypte une chaine de caractere
 * 
 * @param string 
 * @return char* 
 */
char* encryptPassword(char* string){
    //printf(">>%s<<\n",crypt(string,"456b7016a916a4b178dd72b947c152b7,"));
    return (crypt(string,"456b7016a916a4b178dd72b947c152b7,"));
}

/**
 * @brief Verifie si le mot de passe est valide
 * 
 * @param password 
 * @param ua 
 * @return int 
 */
int passwordIsGood(char * password, User_account ua){
    return (strcmp(encryptPassword(password),get_pwd(ua))==0 ? 1 : 0);
}