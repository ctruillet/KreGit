/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/user_account.h"
#include "../include/account.h"


//structure from a user account
typedef struct user_account_s{
    bool admin;     //account with admin rights
    char *name;     //name of user
    char *firstname;        //first name of user
    char *pwd;      //password link to the account
    list_account list; //list of account own by user
} user_account;

