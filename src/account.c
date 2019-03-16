
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
    char *owners[2];    //owners list of account
    char *type_account; //type of account
    char *history;      //history of the account

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

float get_balance(Account acc)
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
}

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
    while (l != NULL)
    {
        l = l->next;
    }
    List_account l2;
    l2->current = acc;
    l2->next = NULL;
    l = l2;
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

char *List_accountToString(List_account l)
{
    List_account l2 = l; //to avoid modification on the pointeur
    int size = Liste_accountSize(l);
    int stringSize = (IDACCSIZE + 1) * size + 3;
    char str[stringSize];
    str[0] = '[';
    for (int i = 1; i < stringSize - 2; i = i + IDACCSIZE)
    {
        str[i] = ' '; //insert a space between each accounts
        i++;
        for (int j = 0; j < IDACCSIZE; j++)
        {
            str[i + j] = l2->current->ID[j]; // insert the ID account
        }
        l2 = l2->next;
    }
    str[i + 1] = ' ';
    str[i + 2] = ']';
    return str;
}

//file management

void create_account_json(char *ID, char **owners, char *type_account)
{
    char fileName[2 * IDACCSIZE + 19]; 
    char path[] = "data/account/.json"; 
    for (int i = 0; i < 13; i++)
        if (i < 13)
        {
            fileName[i] = path[i];
        }
        else if (i<13+IDACCSIZE)
        {
            fileName[i]= ID[i-13];
        }
        else if (i==13+IDACCSIZE)
        {
            fileName[i]='/'
        }
        else if (i<13+2*IDACCSIZE)
        {
            fileName[i]=ID[i-(14+IDACCSIZE)]
        }
        else
        {
            fileName[i]=path[i-(2*IDACCSIZE+1)]
        }
        
        FILE *json = fopen(filename, "w+");
        fprintf("{\n\t\"account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"owners\": \"%s;%s\",\n\t\t\"type_account\": \"%s\"\n\t}\n}",ID,owners[0],owners[1],type_account);
        fclose(json);
    }
}
