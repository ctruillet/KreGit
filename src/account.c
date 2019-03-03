
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

} account;

//structure of an account list
typedef struct list_account_s
{
    account current; //current element of the list
    list_account *next;   //next element of the list
} list_account;
