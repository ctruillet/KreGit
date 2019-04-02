/**
 * @file display.h
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief En-tête des fonctions servant d'interface avec l'utilisateur
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#define __DISPLAY_H__

#ifndef __USER_ACCOUNT_H__
	#include "../include/user_account.h"
#endif

/**
 * @brief Ecrit "KreGit" (en ascii-art)
 * 
 */
void title();

/**
 * @brief Ecrit "Goodbye" (en ascii-art)
 * 
 */
void end();

/**
 * @brief Ecrit les informations sur KreGit, la banque multimondiale MarkDeepDownLearning
 * 
 */
void info();

/**
 * @brief Lance le formulaire de connection
 * 
 * Retourne   
 * 		- 0 si echec   
 * 		- 4 si le compte est administrateur   
 * 		- 5 si le compte est un simple utilisateur   
 * 
 * @param ua 
 * @param isConnect 
 * @param isAdmin 
 * @return int 
 */
User_account connect(User_account ua, int * isConnect, int * isAdmin);

/**
 * @brief Deconnecte l'utilisateur
 * 
 * @param isConnect 
 * @param isAdmin 
 * @param ua 
 */
User_account deconnect(int * isConnect, int * isAdmin, User_account ua);

/**
 * @brief Lance le formulaire de création de compte
 * 
 * @param ua 
 */
void newAccount_form(User_account ua);

/**
 * @brief Lance le formulaire de création de nouvel utilisateur et le connecte
 * 
 * @param ua 
 * @param isConnect 
 * @return User_account 
 */
User_account newUser_form(User_account ua, int * isConnect);

/**
 * @brief Affiche tout les comptes d'un utilisateur
 * 
 * @param ua 
 * @param FSM 
 * @return int 
 */
int displayListAccount(User_account ua, int FSM);

/**
 * @brief Gere la navigation entre les pages de KreGit la nouvelle banque amélioré par réseau de neurone 4G
 * 
 * @param FSM 
 * @param isConnect 
 * @param isAdmin 
 * @return int 
 */
int nav(int FSM, int * isConnect, int * isAdmin);

/**
 * @brief Affiche un compte
 * 
 * @param a 
 */
void displayAccount(Account a);

/**
 * @brief Affiche une erreur
 * 
 */
void error();

/**
 * @brief Genere et affiche une citation de Kaamelott
 * 
 */
void kaamelott();