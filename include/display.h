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

//Nav_bar
void nav(User_account ua);

//Error
void error();