
/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/account.h"

//structure of account
typedef struct account_s
{
    char *ID;           //Identification 
    char *owners[2];     //owners list of account 
    char *type_account; //type of account
    char *history;      //history of the account

} account;

//structure of an account list
typedef struct list_account_s
{
    Account current; //current element of the list
    List_account next;   //next element of the list
} list_account;

//getters
char *get_id(Account acc){
    return acc->ID;
}

char **get_owners(Account acc){
    return acc->owners;
}

char *get_type_account(Account acc){
    return acc->type_account;
}

float get_balance(Account acc){
    //TODO
}

char **get_history(Account acc, char date1, char date2){

    //TODO  
}

//setters

void add_history(Account acc, char *operation){
    //TODO
}

void set_owners(Account acc, char **own){
    acc->owners[0]=own[0];
    acc->owners[1]=own[1];
}

void set_ID(Account acc, char *ID){
    acc->ID=ID;
}

void set_type_account(Account acc, char *type){
    acc->type_account = type;
}

void add_list(List_account l, Account acc){
    while (l != NULL){
        l=l->next;
    }
    List_account l2;
    l2->current = acc;
    l2->next = NULL;
    l=l2;
}