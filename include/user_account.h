/**
 * @file user_account.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief En-tête des fonctions manipulant directement la structure User_Account
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __USER_ACCOUNT_H__

#include <stdbool.h>
#include "../include/account.h"

/**
 * @brief Pointeur sur la structure user_account_s
 * 
 */
typedef struct user_account_s *User_account;

//getters
/**
 * @brief Recupere la variable isAdmin d'un utilisateur (1 si Vrai, 0 sinon)
 * 
 * @param uacc 
 * @return int 
 */
int is_admin(User_account uacc);
/**
 * @brief Retourne l'identifiant d'un utilisateur
 * 
 * @param uacc 
 * @return char* 
 */
char * get_u_ID(User_account uacc);
/**
 * @brief Retourne le nom d'un utilisateur
 * 
 * @param uacc 
 * @return char* 
 */
char * get_name(User_account uacc);
/**
 * @brief Retourne le prenom d'un utilisateur
 * 
 * @param uacc 
 * @return char* 
 */
char * get_firstname(User_account uacc);
/**
 * @brief Retourne le mot de passe (chiffré) d'un utilisateur
 * 
 * @param uacc 
 * @return char* 
 */
char * get_pwd(User_account uacc);
/**
 * @brief Retourne le premier compte d'un utilisateur (début de la liste)
 * 
 * @param uacc 
 * @return Account 
 */
Account getAccount(User_account uacc);

void InfoUser(User_account ua);


//Setters
/**
 * @brief Defini un Utilisateur
 * 
 * @param ID 
 * @param admin 
 * @param name 
 * @param firstname 
 * @param pwd 
 * @param a 
 * @return User_account 
 */
User_account setUser(char * ID, int admin, char *name, char *firstname, char *pwd);
/**
 * @brief Defini la variable isAdmin d'un utilisateur
 * 
 * @param uacc 
 * @param admin 
 */
void set_admin(User_account uacc, int admin);
/**
 * @brief Defini le nom d'un utilisateur
 * 
 * @param uacc 
 * @param name 
 */
void set_name(User_account uacc, char * name);
/**
 * @brief Defini le prenom d'un utilisateur
 * 
 * @param uacc 
 * @param firstname 
 */
void set_firstname(User_account uacc, char *firstname);
/**
 * @brief Defini le mot de passe d'un utilisateur
 * 
 * @param uacc 
 * @param pwd 
 */
void set_pwd(User_account uacc, char *pwd);
/**
 * @brief Defini l'identifiant d'un utilisateur
 * 
 * @param uacc 
 * @param ID 
 */
void set_UID(User_account uacc, char *ID);
/**
 * @brief Defini le premier compte d'un utilisateur (début de la liste)
 * 
 * @param uacc 
 * @param acc 
 */
void setAccountFirst(User_account uacc, Account acc);

/**
 * @brief Modifie le mot de passe
 * 
 * @param ua 
 */
User_account changePwd(User_account ua);

//file management
/**
 * @brief Crée un identifiant d'utilisateur unique
 * 
 * @return char* 
 */
char * createUser_ID(); 
/**
 * @brief Crée un utilisateur 
 * 
 * Crée un nouveau fichier .json nommé "ID.json" (dossier data/user_account) et le remplit avec les parametres.
 * Renvoit une nouvelle structure User_Account remplie avec les parametres
 * 
 * @param admin 
 * @param name 
 * @param firstname 
 * @param pwd 
 * @param a 
 * @return User_account 
 */
User_account create_user_account(char * ID, int admin, char *name, char *firstname, char *pwd, Account a);

/**
 * @brief Recuperer les informations de l'utilisateur dans le fichier json associé
 * 
 * @param file 
 * @param isAdmin 
 * @return User_account 
 */
User_account charge_user_account(char * file, int * isAdmin);

/*
void delete_user_account(User_account uacc);
void remove_Ulist(User_account uacc, Account acc);      //remove an account to the user
*/
