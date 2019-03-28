/*
* Valentin Frydrychowski 
* Derniere modification : 28/03/2019
*/

#include <stdbool.h>
#define __USER_ACCOUNT_H__

#include "account.h"
#define UIDSIZE 16 //size in char of an user_account id


typedef  struct user_account_s *User_account;

User_account create_user_account(bool admin, char *name, char *firstname, char *pwd, List_account list);     //create the json, fill it and return it
char *create_user_ID(char *name);         //create ID whit name and time of creation
void delete_user_account(User_account uacc);
void charge_user_account(User_account uacc, char *U_id);
void discharge_user_account(User_account uacc);

bool is_admin(User_account uacc);
char *get_u_ID(User_account uacc);
char *get_name(User_account uacc);
char *get_firstname(User_account uacc);
char *get_pwd(User_account uacc);
char **get_account_list(User_account uacc);     //return a board of account linked to the user

User_account setUser(char * ID, bool admin, char *name, char *firstname, char *pwd);
void set_admin(User_account uacc, bool admin);
void set_admin(User_account uacc, bool admin);
void set_name(User_account uacc, char *name);
void set_firstname(User_account uacc, char *firstname);
void set_pwd(User_account uacc, char *pwd);
void set_UID(User_account uacc, char *ID);

void add_Ulist(User_account uacc, Account acc);      //add an account to the user
void remoove_Ulist(User_account uacc, Account acc);      //remoove an acont to the user