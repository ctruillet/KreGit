/*
* Valentin Frydrychowski 
* Clement Truillet
* Derniere modification : 01/04/2019
*/

#define __USER_ACCOUNT_H__

#include <stdbool.h>
#include "account.h"

//Structure of User Account
typedef  struct user_account_s *User_account;

//getters
int is_admin(User_account uacc);
char * get_u_ID(User_account uacc);
char * get_name(User_account uacc);
char * get_firstname(User_account uacc);
char * get_pwd(User_account uacc);
Account getAccount(User_account uacc);

//Setters
User_account setUser(char * ID, int admin, char *name, char *firstname, char *pwd, Account a);
void set_admin(User_account uacc, int admin);
void set_name(User_account uacc, char * name);
void set_firstname(User_account uacc, char *firstname);
void set_pwd(User_account uacc, char *pwd);
void set_UID(User_account uacc, char *ID);
void setAccountFirst(User_account uacc, Account acc);

//file management
char * createUser_ID();             //create ID whit the time of creation
User_account create_user_account(int admin, char *name, char *firstname, char *pwd, Account a);

//charge the infos of the json into the user_account struct
User_account charge_user_account(char * file, int * isAdmin);

/*
void delete_user_account(User_account uacc);
void remove_Ulist(User_account uacc, Account acc);      //remove an account to the user
*/
