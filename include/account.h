/*
* Valentin Frydrychowski 
* Derniere modification : 28/02/2019
*/
#define __ACCOUNT_H__

typedef struct account_s *Account;
typedef list_account_s *List_account;

void create_json();
void create_account(Account acc);
void delete_account(Account acc);
void charge_account(Account acc, char ID);
void discharge_account(Account acc);

char get_id(Account acc);
char* get_owners(Account acc);
char get_type_account(Account acc);


char withdraw(Account acc, float ammount);
char deposit(Account acc, float ammount);   
