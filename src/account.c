
/*
* Valentin Frydrychowski 
* Derniere modification : 28/03/2019
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/account.h"

//structure of account
typedef struct account_s
{
    char *ID;      //Identification
    char **owners; //owners list of account
    char *type_account;      //type of account
    //char *history;      //history of the account

} account;

//structure of an account list
typedef struct list_account_s
{
    Account current;   //current element of the list
    List_account next; //next element of the list
} list_account;

//getters
char *get_id(Account acc)
{
    return acc->ID;
}

char **get_owners(Account acc)
{
    return acc->owners;
}

char *get_type_account(Account acc)
{
    return acc->type_account;
}

/*float get_balance(Account acc)
{
    //TODO
}

char **get_history(Account acc, char date1, char date2)
{

    //TODO
}

//setters

void add_history(Account acc, char *operation)
{
    //TODO
}*/

void set_owners(Account acc, char **own)
{
    acc->owners[0] = own[0];
    acc->owners[1] = own[1];
}

void set_ID(Account acc, char *ID)
{
    acc->ID = ID;
}

void set_type_account(Account acc, char *type)
{
    acc->type_account = type;
}

void add_list(List_account l, Account acc)
{
    List_account l2 = malloc(sizeof(account) + sizeof(List_account));
    l2 = l;
    while (l2 != NULL){
        l2 = l2->next;
    }
    l2->current = acc;
    l2->next = NULL;
}

int Liste_accountSize(List_account l)
{
    int size = 0;
    List_account l2 = l; //to avoid modification on the pointeur
    while (l2 != NULL)
    { //while we didn't reach the end of the list
        size++;
        l2 = l2->next;
    }
    return size;
}

char *List_accountToString(List_account l){
    List_account l2 = l; //to avoid modification on the pointeur
    char * strR = (char *)malloc(sizeof(char)*128);
    char str[128] = "[";
    while(l2!=NULL){
        strcat(str,l2->current->ID);
        strcat(str,",");
        l2 = l2->next;
    }
    strcat(str,"]");
    printf("3\n");
    strcpy(strR,str);
    printf("4\n");
    return strR;
}

//file management

char *create_account_ID(){
    char *ID = (char*)malloc(32);
    time_t temps;
    struct tm date;

    // Recuperation de la date et l'heure actuelle.
    time(&temps);
    date=*localtime(&temps);

    // Remplissage de la chaîne avec en date_heure
    strftime(ID, 128, "%m%d%Y%H%M%S", &date);
    return ID;
}

void charge_account(Account acc, char ID[IDACCSIZE])
{
    set_ID(acc, ID);
    char *tab[2];
    tab[0] = "owners1";
    tab[1] = "owners2";
    set_owners(acc, tab);
    set_type_account(acc, "bidon");
}

void create_account_csv(char *ID)
{
    char fileName[2 * IDACCSIZE + 18];
    char path[] = "data/account/.csv";
    for (int i = 0; i < 2 * IDACCSIZE + 19; i++)
    {
        if (i < 13)
        {
            fileName[i] = path[i];
        }
        else if (i < 13 + IDACCSIZE)
        {
            fileName[i] = ID[i - 13];
        }
        else if (i == 13 + IDACCSIZE)
        {
            fileName[i] = '/';
        }
        else if (i < 14 + 2 * IDACCSIZE)
        {
            fileName[i] = ID[i - (14 + IDACCSIZE)];
        }
        else
        {
            fileName[i] = path[i - (2 * IDACCSIZE + 1)];
        }
    }

    FILE *csv = fopen(fileName, "r");
    if (csv != NULL)
    {
        fprintf(csv, "date;operation;balance;comments");
        fclose(csv);
    }
}

void create_account_json(char *ID, char **owners, char *type_account)
{
    char fileName[2 * IDACCSIZE + 20];
    char path[] = "data/account/.json";
    for (int i = 0; i < 2 * IDACCSIZE + 20; i++)
    {
        if (i < 13)
        {
            fileName[i] = path[i];
        }
        else if (i < 13 + IDACCSIZE)
        {
            fileName[i] = ID[i - 13];
        }
        else if (i == 13 + IDACCSIZE)
        {
            fileName[i] = '/';
        }
        else if (i < 13 + 2 * IDACCSIZE)
        {
            fileName[i] = ID[i - (14 + IDACCSIZE)];
        }
        else
        {
            fileName[i] = path[i - (2 * IDACCSIZE + 1)];
        }
    }

    FILE *json = fopen(fileName, "w+");
    if (json != NULL)
    {
        fprintf(json, "{\n\t\"account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"owners\": \"%s;%s\",\n\t\t\"type_account\": \"%s\"\n\t}\n}", ID, owners[0], owners[1], type_account);
        fclose(json);
    }
}

Account create_account(char **owners, char *type_account)
{

    Account acc = NULL;
    char *ID = create_account_ID();
    char path[12 + IDACCSIZE] = "data/account";
    strcat(path, ID);
    char commande[18 + IDACCSIZE] = "mkdir ";
    strcat(commande, path);
    system(commande);
    create_account_csv(ID);
    create_account_json(ID, owners, type_account);
    charge_account(acc, ID);
    return acc;
}

/*void charge_account(Account acc, char *ID){

}*/