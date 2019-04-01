/*
* Valentin Frydrychowski 
* Clement Truillet
* Derniere modification : 01/04/2019
*/
#define __ACCOUNT_H__
#ifndef __USER_ACCOUNT_H__
    #include "user_account.h"
#endif

typedef struct account_s *Account;

//Getters
char * get_id(Account acc);
char * get_type_account(Account acc);
int nbrAccount(Account a);
char *List_accountToString(Account a);

//Setters
void set_ID(Account acc, char * ID);
void set_type_account(Account acc, char * type);
Account createAccount(char * type_account);
void addNewAccount(Account a, Account aAdd);

//file management
char * createAccountID(char * type);
void createAccountCsv(char * ID);
int newOperation(Account a, double operation, char * comment);