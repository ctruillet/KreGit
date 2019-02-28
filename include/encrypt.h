/*
 * librairie encrypt.h
 */
#define __ENCRYPT_H__

#ifndef __USER_ACCOUNT_H__
	#include "../include/users_account.h"
#endif

/*
* Clement Truillet 
* Derniere modification : 28/02/2019
*/

//Check if the password is good
int passwordIsGood(char * password, user_account ua);

//Encrypt password
char * encryptPassword(char * string);
