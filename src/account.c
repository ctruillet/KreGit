/**
 * @file account.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions manipulant la structure Account
 * @version 0.1
 * @date 2019-04-03
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
typedef struct account_s
{
    char ID[32];            //Identification
    char type_account[32];  //Type of account
    struct account_s *next; //Next Account
} account;

//Getters
char *get_id(Account acc)
{
    return acc->ID;
}
char *get_type_account(Account acc)
{
    return acc->type_account;
}

Account getNextAccount(Account ac)
{
    return ac->next;
}

//Setters
void set_ID(Account acc, char *ID)
{
    strcpy(acc->ID, ID);
}

void set_type_account(Account acc, char *type)
{
    strcpy(acc->type_account, type);
}

void InfoAccount(Account a)
{
    printf("--------------------------\n| Compte %s\n| \tType : %s\n| \tSuivant ? %s\n--------------------------\n", get_id(a), get_type_account(a), (getNextAccount(a) != NULL) ? "Oui" : "Non");
}

Account setAccount(char *ID)
{
    Account ac = (Account)malloc(sizeof(struct account_s));
    set_ID(ac, ID);
    char temp[32] = "\0";

    strcpy(temp, ID);
    // Get the first token
    char *type = strtok(temp, "-"); // merdier token
    set_type_account(ac, type);
    ac->next = NULL;
    return (ac);
}

void addNewAccount(Account a, Account aAdd)
{
    //InfoAccount(a);

    Account ac = a;
    while (ac->next != NULL)
    {
        //printf(">> on passe le Compte %s\n",get_id(ac));
        ac = getNextAccount(ac);
    }
    ac->next = aAdd;

    /* ToDo & BUG
    *   Ajouter l'ID à UserAccount
    */
}

int nbrAccount(Account a)
{
    if (a == NULL)
    {
        return 0;
    }
    else
    {
        int size = 0;
        Account ac = a; //to avoid modification on the pointeur
        while (ac != NULL)
        { //while we didn't reach the end of the list
            size++;
            ac = ac->next;
        }
        return size;
    }
}

char *List_accountToString(Account a)
{
    Account a2 = a; //to avoid modification on the pointeur
    char *strR = (char *)malloc(sizeof(char) * 128);
    char str[128] = "[";
    while (a2 != NULL)
    {
        strcat(str, "\\\"");
        strcat(str, a2->ID);
        strcat(str, "\\\"");
        if (a2->next != NULL)
        {
            strcat(str, ",");
        }
        a2 = a2->next;
    }
    strcat(str, "]");
    strcpy(strR, str);
    return strR;
}

//file management
char *createAccountID(char *type)
{
    char *ID = (char *)malloc(32);
    char *timeS = (char *)malloc(32);
    time_t temps;
    struct tm date;

    // Recuperation de la date et l'heure actuelle.
    time(&temps);
    date = *localtime(&temps);

    // Remplissage de la chaîne avec en date_heure
    strftime(timeS, 128, "%m%d%Y%H%M%S", &date);
    sprintf(ID, "%s-%s", type, timeS);

    return ID;
}

void createAccountCsv(char *ID)
{
    char path[48] = "data/account/";
    strcat(path, ID);
    strcat(path, ".csv");

    FILE *fileCSV = fopen(path, "a");
    if (fileCSV != NULL)
    {
        fprintf(fileCSV, "date,operation,solde,comments");
        fclose(fileCSV);
    }
}

char *twoDeci(char *d)
{
    char *entier = strtok(d, ".");
    char *decimal = strtok(NULL, ".");
    sprintf(d, "%s.%c%c", entier, decimal[0], decimal[1]);
    return d;
}

int newOperation(Account a, double operation, char *comment)
{
    /*
    *   Ouvrir le fichier CSV associé
    *   Faire l'opération
    *   Mettre a jour le solde
    */

    char lastLine[512] = "";
    char *balance;
    char *ope = (char *)malloc(32);
    double lfbal;

    char path[48] = "data/account/";
    strcat(path, a->ID);
    strcat(path, ".csv");
    //récupère la date et l'heure
    char *timeS = (char *)malloc(32);
    time_t temps;
    struct tm date;
    time(&temps);
    date = *localtime(&temps);
    strftime(timeS, 128, "%Y/%m/%d/%H/%M", &date);

    if (operation >= 0)
    {
        sprintf(ope, "+%lf", operation);
    }
    else
    {
        sprintf(ope, "%lf", operation);
    }
    ope = twoDeci(ope);
    //récupère la dernière opèration
    FILE *file = fopen(path, "r");
    if (file != NULL)
    {
        while (fgets(lastLine, sizeof lastLine, file));
    }

    //récupère le solde
    balance = strtok(lastLine, ",");
    balance = strtok(NULL, ",");
    balance = strtok(NULL, ",");
    //effectue l'opération
    sscanf(balance, "%lf", &lfbal);
    lfbal = lfbal + operation;
    sprintf(balance, "%lf", lfbal);
    balance = twoDeci(balance);
    //met à jour le solde
    file = fopen(path, "a");
    if (file != NULL)
    {
        fprintf(file, "\n%s,%s,%s,%s", timeS, ope, balance, comment);
        fclose(file);
    }

    return 0;
}

Account createAccount(char *type_account)
{
    Account acc = (Account)malloc(sizeof(Account));
    set_ID(acc, createAccountID(type_account));
    set_type_account(acc, type_account);
    acc->next = NULL;

    return acc;
}