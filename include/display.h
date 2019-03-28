/*
 * librairie display.h
 */
#define __DISPLAY_H__

#ifndef __USER_ACCOUNT_H__
	#include "../include/user_account.h"
#endif

/*
* Clement Truillet 
* Derniere modification : 26/03/2019
*/

//Display title
void title();

//Say Goodbye
void end();

//Informations
void info();

//Connect
int connect(User_account ua, int * isConnect);

//Deconnect
void deconnect(int * isConnect, User_account ua);

//Create a new account
void newAccount_form(User_account ua);

//Create a new user
User_account newUser_form(User_account ua, int * isConnect);

//Nav_bar - Display all accounts of user with theirs types
int displayListAccount(User_account ua, int FSM);

//Nav bar
int nav(int FSM, int * isConnect, int * isAdmin);

//Display Account
void displayAccount(Account a);

//Error
void error();

//Generate a random quote of Percaval (or Karadoc)
void kaamelott();