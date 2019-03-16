/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/user_account.h"
#include "../include/account.h"

//structure from a user account
typedef struct user_account_s
{
    char *u_ID;        //ID of .json file
    bool admin;        //account with admin rights
    char *name;        //name of user
    char *firstname;   //first name of user
    char *pwd;         //password link to the account
    List_account list; //list of account own by user
} user_account;

//getters
bool is_admin(User_account uacc)
{
    return uacc->admin;
}

char *get_u_ID(User_account uacc)
{
    return uacc->u_ID;
}

char *get_name(User_account uacc)
{
    return uacc->name;
}

char *get_firstname(User_account uacc)
{
    return uacc->firstname;
}

char *get_pwd(User_account uacc)
{
    return uacc->pwd;
}

char **get_account_list(User_account uacc)
{
    //TODO toString
}

//Setters

void set_admin(User_account uacc, bool admin)
{
    uacc->admin = admin;
}

void set_name(User_account uacc, char *name)
{
    uacc->name = name;
}

void set_firstname(User_account uacc, char *firstname)
{
    uacc->firstname = firstname;
}

void set_pwd(User_account uacc, char *pwd)
{
    uacc->pwd = pwd;
}

void add_Ulist(User_account uacc, Account acc)
{
    add_list(uacc->list, acc);
}

//file management

User_account create_user_account(bool admin, char *name, char *firstname, char *pwd, List_account list)
{
    char *U_id = create_user_ID(name);
    char *fileName[UIDSIZE + 23];
    char *path="data/user_account/.json"
    for(int i = 0; i < UIDSIZE + 23; i++)
    {
        if (i<18)
        {
            fileName[i]=path[i];
        }
        else if (i<18+UIDSIZE)
        {
            filename[i]=U_id[i-18];
        }
        else
        {
            fileName[i]=path[i-UIDSIZE];
        }
        
    }
    
    //creation and opening of json
    FILE *json = fopen(filename, "w+");
    //filing of json with the json structure
    fprintf(json, "{\n\t\"user_account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"admin\": \"%s\",\n\t\t\"firstname\": \"%s\",\n\t\t\"name\": \"%s\",\n\t\t\"pwd\": \"%s\",\n\t\t\"List_account\": \"%s\"\n\t}\n}", U_id, admin, firstname, name, pwd, List_accountToString(list));
    fclose(json);
    User_account uacc = NULL;
    charge_user_account(uacc, U_id);
    return uacc;
}