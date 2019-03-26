/*
 * librairie display.h
 */
#define __DISPLAY_H__

#ifndef __USER_ACCOUNT_H__
	#include "../include/user_account.h"
#endif

/*
* Clement Truillet 
* Derniere modification : 28/02/2019
*/

//Display title
void title();

//Say Goodbye
void end();

//Connect
int connect(User_account ua, int * isConnect);

//Deconnect
void deconnect(int * isConnect, User_account ua);

//Create a new account
User_account newAccount_form();

//Create a new user
void newUser_form(User_account ua);

//Nav_bar - Display all accounts of user with theirs types
int nav(User_account ua);

//Display Account
void displayAccount(Account a);

//Error
void error();

//Generate a random quote of Percaval (or Karadoc)
void kaamelott();