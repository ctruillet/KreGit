/**
 * @file account.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions manipulant la structure Account
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/account.h"

/**
 * @brief Structure account_s
 * 
 * Contient    
 *      - char * ID : Identifiant du compte   
 *      - char * type_account : Type du compte (PEL, Livret A, ...)   
 *      - Account next : Pointeur vers le compte suivant   
 * 
 */
typedef struct account_s{
    char ID[32];                //Identification
    char type_account[32];      //Type of account
    Account next;               //Next Account
} account;

//Getters
char * get_id(Account acc){
    return acc->ID;
}
char * get_type_account(Account acc){
    return acc->type_account;
}

//Setters
void set_ID(Account acc, char * ID){
    strcpy(acc->ID,ID);
}

void set_type_account(Account acc, char * type){
    strcpy(acc->type_account,type);
}

Account setAccount(char * ID){
    Account ac = (Account)malloc(sizeof(Account));
    set_ID(ac,ID);
    printf("\t\tID : %s\n",ID);
    char temp[32];
    strcpy(temp,ID);
    char *type = strtok(temp,"-");
    set_type_account(ac,type);
    printf("\t\ttype : %s %s\n",type,ID);
    ac->next=NULL;
    printf("\t\tNULL : %d\n",(ac->next==NULL)?1:0);
    return ac;
}

void addNewAccount(Account a, Account aAdd){
    Account ac = a;
    printf("-> NULL : %d\n",(a->next==NULL)?1:0);
    while (ac->next != NULL){
        printf("Compte %s\n",get_id(a));
        ac = ac->next;
    }
    ac->next = aAdd;

    /* ToDo
    *   Ajouter l'ID à UserAccount
    */
}


int nbrAccount(Account a){
    int size = 0;
    Account ac = a;             //to avoid modification on the pointeur
    while (ac != NULL){         //while we didn't reach the end of the list
        size++;
        ac = ac->next;
    }
    return size;
}

char *List_accountToString(Account a){
    Account a2 = a;                                     //to avoid modification on the pointeur
    char * strR = (char *)malloc(sizeof(char)*128);
    char str[128] = "[\"";
    while(a2!=NULL){
        strcat(str,a2->ID);
        strcat(str,"\",\"");
        a2 = a2->next;
    }
    strcat(str,"\"]");
    strcpy(strR,str);
    return strR;
}

//file management
char * createAccountID(char * type){
    char *ID = (char*)malloc(32);
    char *timeS = (char*)malloc(32);
    time_t temps;
    struct tm date;

    // Recuperation de la date et l'heure actuelle.
    time(&temps);
    date=*localtime(&temps);

    // Remplissage de la chaîne avec en date_heure
    strftime(timeS, 128, "%m%d%Y%H%M%S", &date);
    sprintf(ID,"%s-%s",type,timeS);
    
    return ID;
}

void createAccountCsv(char * ID){
    char path[48] = "data/account/";
    strcat(path,ID);
    strcat(path,".csv");

    FILE * fileCSV = fopen(path, "a");
    if (fileCSV != NULL){
        fprintf(fileCSV, "date,operation,solde,comments");
        fclose(fileCSV);
    }
}

int newOperation(Account a, double operation, char * comment){
    /* ToDo
    *   Ouvrir le fichier CSV associé
    *   Faire l'opération
    *   Mettre a jour le solde
    */
    return 0;
}

Account createAccount(char * type_account){
    Account acc = (Account)malloc(sizeof(Account));
    set_ID(acc,createAccountID(type_account));
    set_type_account(acc,type_account);
    acc->next=NULL;

    return acc;
}