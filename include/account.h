/*
* Valentin Frydrychowski 
* Derniere modification : 07/03/2019
*/
#define __ACCOUNT_H__
#ifndef __USER_ACCOUNT_H__
    #include "user_account.h"
#endif

typedef struct account_s *Account;
typedef struct list_account_s *List_account;

Account create_account(char **owners, char *type_account); /* Create a directory with .json and history.csv in it, fill the .json */
void create_account_json(char name);      //create a .json with generic account structure
char *create_account_ID();        //create an ID whith the date of creation
void delete_account(Account acc);
void charge_account(Account acc, char ID);  //decrypte the account an charge it in the struct
void discharge_account(Account acc);        //save the .json and .csv, crypt it and free pointeur

void add_list(List_account l, Account acc);      //add this account to the list
void remoove_list(List_account l, Account acc);     //remoove this account to the list
char *List_accountToString();       //convert List_account format to String format

char *get_id(Account acc);
char **get_owners(Account acc);     //return a table of strings
char *get_type_account(Account acc);
float get_balance(Account acc);
char **get_history(Account acc, char date1, char date2); //get the history ofthe account between two dates

void add_history(Account acc, char *operation);     //add an operation to the history
void set_owners(Account acc, char **own);
void set_ID(Account acc, char *ID);
void set_type_account(Account acc, char *type);

char withdraw(Account acc, float ammount);      //make a whithdraw in the account
char deposit(Account acc, float ammount);       //make a deposit in the account
