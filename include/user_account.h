/*
* Valentin Frydrychowski 
* Derniere modification : 28/02/2019
*/
#define __USER_ACCOUNT_H__

typedef  struct user_account_s *User_account;

void create_user_account(Account acc);
void delete_user_account(Account acc);
void charge_user_account(Account acc, char ID);