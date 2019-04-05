/**
 * @file account.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief En-tête des fonctions manipulant directement la structure Account
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#define __ACCOUNT_H__
#ifndef __USER_ACCOUNT_H__
    #include "../include/user_account.h"
#endif

/**
 * @brief pointeur sur la structure account_s
 * 
 */
typedef struct account_s *Account;

//Getters
/**
 * @brief Retourne l'ID d'un compte
 * 
 * @param acc 
 * @return char* 
 */
char * get_id(Account acc);
/**
 * @brief Retourne le type d'un compte
 * 
 * @param acc 
 * @return char* 
 */
char * get_type_account(Account acc);

/**
 * @brief Retourne le compte suivant du compte
 * 
 * @param ac 
 * @return Account 
 */
Account getNextAccount(Account ac);

/**
 * @brief Affiche les informations d'un compte
 * 
 * @param a 
 */
void InfoAccount(Account a);

/**
 * @brief Retourne le nombre de compte
 * 
 * @param a 
 * @return int 
 */
int nbrAccount(Account a);
/**
 * @brief Retourne la liste des comptes sous forme de chaine de caractere
 * 
 * @param a 
 * @return char* 
 */
char *List_accountToString(Account a);

//Setters
/**
 * @brief Definir l'ID d'un compte
 * 
 * @param acc 
 * @param ID 
 */
void set_ID(Account acc, char * ID);
/**
 * @brief Definier le type d'un compte
 * 
 * @param acc 
 * @param type 
 */
void set_type_account(Account acc, char * type);

/**
 * @brief Defini un compte à partir de son ID
 * 
 * @param ID 
 * @return Account 
 */
Account setAccount(char * ID);

/**
 * @brief Créer un nouveau compte
 * 
 * @param type_account 
 * @return Account 
 */
Account createAccount(char * type_account);
/**
 * @brief Ajouter un nouveau compte à une liste de compte
 * 
 * @param a 
 * @param aAdd 
 */
void addNewAccount(Account a, Account aAdd);

//file management
/**
 * @brief Créer un identifiant de compte
 * 
 * @param type 
 * @return char* 
 */
char * createAccountID(char * type);
/**
 * @brief Generer le fichier CSV d'un compte 
 * 
 * @param ID 
 */
void createAccountCsv(char * ID);
/**
 * @brief Ajouter une nouvelle opération à un compte
 * 
 * @param a 
 * @param operation 
 * @param comment 
 * @return int 
 */
int newOperation(Account a, double operation, char * comment);
/**
 * @brief renvoi la représentation du float avec 2 decimal
 * 
 * @param d
 */
char *twoDeci(char *d);
/**
 * @brief renvoi l'historique du compte depuis la date
 * 
 * @param date de la forme "dd/mm/yyyy"
 */
char* history(Account acc, char* date);//ToDo
/**
 * @brief renvoie -1,0,1 si la premiere date est <,=,> à la deuxième
 * 
 * @param date1  de la forme "dd/mm/yyyy"
 * @param date2  de la forme "dd/mm/yyyy"
 */
int compareDate(char* date1,char* date2);