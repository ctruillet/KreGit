/*
* Valentin Frydrychowski 
* Derniere modification : 28/03/2019
*/

//finir chargement list account
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/user_account.h"
#include "../include/account.h"

#define NAMESIZE 32
#define FNAMESIZE 32

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

/*char **get_account_list(User_account uacc)
{
    //TODO toString
}*/

//Setters

User_account setUser(char * ID, bool admin, char *name, char *firstname, char *pwd){
    User_account ua;
    ua = (User_account)malloc(sizeof(bool) + (NAMESIZE + UIDSIZE + FNAMESIZE) * sizeof(char) + sizeof(List_account));
    set_admin(ua, admin);
    set_firstname(ua,firstname);
    set_UID(ua,ID);
    set_name(ua,name);
    set_firstname(ua,firstname);
    set_pwd(ua,pwd);
 
    return ua;
}

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

void set_UID(User_account uacc, char *ID){
    uacc->u_ID = ID;
}

void add_Ulist(User_account uacc, Account acc)
{
    add_list(uacc->list, acc);
}

//file management

User_account create_user_account(bool admin, char *name, char *firstname, char *pwd, List_account list)
{
    char *U_id = create_account_ID(); //to replace by create_user_ID(name);
    char fileName[UIDSIZE + 23];
    char *path = "data/user_account/";
    strcat(path,U_id);
    strcat(path,".json");

    //creation and opening of json
    FILE *json = fopen(fileName, "w+");
    //filing of json with the json structure
    if (json != NULL)
    {
        fprintf(json, "{\n\t\"user_account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"admin\": \"%d\",\n\t\t\"firstname\": \"%s\",\n\t\t\"name\": \"%s\",\n\t\t\"pwd\": \"%s\",\n\t\t\"List_account\": \"%s\"\n\t}\n}", U_id, admin, firstname, name, pwd, List_accountToString(list));
        fclose(json);
    }
    User_account uacc = NULL;
    charge_user_account(uacc, U_id);
    return uacc;
}

//charge the infos of the json into the user_account struct
void charge_user_account(User_account uacc, char *U_id)
{

    //size attribution for the struct
    uacc = malloc(sizeof(bool) + (NAMESIZE + UIDSIZE + FNAMESIZE) * sizeof(char) + sizeof(List_account));

    char fileName[UIDSIZE + 23];
    char *path = "data/user_account/";
    strcat(path,U_id);
    strcat(path,".json");

    //filling all infos needed
    char *list;
    FILE *json = fopen(fileName, "r");
    if (json != NULL)
    {
        fscanf(json, "{\n\t\"user_account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"admin\": \"%d\",\n\t\t\"firstname\": \"%s\",\n\t\t\"name\": \"%s\",\n\t\t\"pwd\": \"%s\",\n\t\t\"List_account\": \"[ %s]\"\n\t}\n}", uacc->u_ID, &(uacc->admin), uacc->firstname, uacc->name, uacc->pwd, list);
        fclose(json);
        uacc->list = NULL;
    }
    //else assert
    int strSize = 0;

    //Filling the List of accounts
    while (list[strSize] != '\0')
    {
        strSize++;
    }
    for (int i = 1; (strSize - 1) / i >= 1; i++)
    {
        char id[IDACCSIZE];
        for (int y = 0; y < IDACCSIZE; y++)
        {
            id[y] = list[(IDACCSIZE + 1)*(i - 1) + y];
        }
        Account acc = NULL;
        charge_account(acc, id);
        add_list(uacc->list, acc);
    }
}