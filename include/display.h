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
int connect(User_account ua);

//Deconnect
void deconnect();

//Create a new account
void newAccount_form();

//Create a new user
void newUser_form();

//Nav_bar - Display all accounts of user with theirs types
int nav(User_account ua);

//Display Account
void displayAccount(Account a);

//Error
void error();