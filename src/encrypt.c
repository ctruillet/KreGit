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
#include "../include/user_account.h"
#include "../include/encrypt.h"

/**
 * @brief Encrypte une chaine de caractere
 * 
 * @param string 
 * @return char* 
 */
char * encryptPassword(char * string){
    FILE *fp;
    char path[1035];
    char * password = NULL; //for the encrypt password
    password = (char *)malloc(33*sizeof(char));
    char * result;
    char chaine[128] = "echo "; 
    char end_chaine[128] = " | openssl md5 | cut -d\" \" -f2"; 
    //Create the command
    strcat(chaine,string); 
    strcat(chaine,end_chaine); 
    //Execute
    fp = popen(chaine, "r");
    //Reclaim the encrypted password
    fgets(path, sizeof(path)-1, fp);
    pclose(fp);
    //To remove the character '\n'
    
    sprintf(password,"%32s",path);
    result = strtok(password,"\n");
    //OK IT'S FINISH !
    return (result);
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