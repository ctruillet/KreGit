/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/
#define __ACCOUNT_H__

typedef struct account_s *Account;
typedef struct list_account_s *List_account;

void create_json();
void create_account(Account acc);
void delete_account(Account acc);
void charge_account(Account acc, char ID);
void discharge_account(Account acc);

void add_list(Account acc);
void remoove_list(Account acc);


char *get_id(Account acc);
char **get_owners(Account acc);
char *get_type_account(Account acc);
float get_balance(Account acc);
char *get_history(Account acc, char date1, char date2);

void add_history(Account acc, char *operation);
char **set_owners(Account acc);
char *set_ID(Account acc);
char *set_type_account();

char withdraw(Account acc, float ammount);
char deposit(Account acc, float ammount);   
