/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/
#define __USER_ACCOUNT_H__

typedef  struct user_account_s *User_account;

void create_user_account(Account acc);
char *create_user_account_name();
void delete_user_account(Account acc);
void charge_user_account(Account acc, char ID);

bool is_admin(User_account uacc);
char *get_name(User_account uacc);
char *get_firstname(User_account uacc);
char *get_pwd(User_account uacc);
char **get_account_list(User_account uacc);

bool *set_admin(User_account uacc);
char *set_name(User_account uacc);
char *set_firstname(User_account uacc);
char *set_pwd(User_account uacc);

