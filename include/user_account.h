/*
* Valentin Frydrychowski 
* Derniere modification : 03/03/2019
*/
#define __USER_ACCOUNT_H__

typedef  struct user_account_s *User_account;

User_account create_user_account(bool admin, char *name, char *firstname, char *pwd, list_account list);     //create the json, fill it and return it
char *create_user_ID(char *name);     //create ID whit name and time of creation
void create_user_json(char *ID);      //create a .json with generic user structure
void delete_user_account(Account uacc);
void charge_user_account(Account uacc, char ID);

bool is_admin(User_account uacc);
char *get_u_ID(User_account uacc);
char *get_name(User_account uacc);
char *get_firstname(User_account uacc);
char *get_pwd(User_account uacc);
char **get_account_list(User_account uacc);     //return a board of accont link to the user

bool *set_admin(User_account uacc);
char *set_name(User_account uacc);
char *set_firstname(User_account uacc);
char *set_pwd(User_account uacc);

void add_Ulist(User_account uacc, Account acc);      //add an account to the user
void remoove_Ulist(User_account uacc, Account acc);      //remoove an acont to the user