#include <stdio.h>
#include <stdlib.h>
#include "../include/user_account.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif


/*
* Clement Truillet 
* Derniere modification : 21/03/2019
*/

//Display title
void title(){
    printf("\n");
    printf("========================================================================================================================\n");
    printf("                                CC  CC    $$$$$    €€€€€€    ££££    !!   VVVVVVVVVV                               corp.\n");
    printf("                                CC CC    $$   $$   €€       ££   £            VV                                        \n");
    printf("                                CCCC     $$   $$   €€       ££       !!       VV                                        \n");
    printf("                                CCCC     $$$$$$    €€€€     ££       !!       VV                                        \n");
    printf("                                CC CC    $$  $$    €€       ££  ££   !!       VV                                        \n");
    printf("                                CC  CC   $$   $$   €€       ££   £   !!       VV                                        \n");
    printf("                                CC   CC  $$   $$   €€€€€€   £££££    !!       VV                                        \n");
    printf("========================================================================================================================\n");
    printf("\n");
}

//Say Goodbye
void end(){
    printf("\n");
    printf("  ____                 _ ____               _ \n");
    printf(" / ___| ___   ___   __| | __ ) _   _  ___  | |\n");
    printf("| |  _ / _ \\ / _ \\ / _` |  _ \\| | | |/ _ \\ | |\n");
    printf("| |_| | (_) | (_) | (_| | |_) | |_| |  __/ |_|\n");
    printf(" \\____|\\___/ \\___/ \\__,_|____/ \\__, |\\___| (_)\n");
    printf("                               |___/          \n");
    printf("\n");
}

//Connect
int connect(User_account ua, int * isConnect){
    /*Demande user_name
    *   Charger la structure
    * Demande pwd
    * Verification pwd
    *   passwordIsGood()
    */
    return 0;
}

//Deconnect
void deconnect(int * isConnect){
    *isConnect = 0;
}

//Create a new account
void newAccount_form(User_account ua){
    /*
    * Demande Type de Compte (Livret A, PEL, compte joint, ...)
    * Demande confirmtation par mot de passe
    * 
    */
}

//Create a new user
User_account newUser_form(){
    /*
    * Demande Nom/Prenom
    * Demande Password
    * Demande confirmation Password
    */
}

//Nav_bar - Display all accounts of user with theirs types
int nav(User_account ua){
    /*
    * Affichage des comptes avec leurs types + Solde
    * Bouton "Nouvelle Opération" 
    */
    return 0;
}

//Display Account
void displayAccount(Account a){
    /*
    * Demande date à partir de laquelle afficher le compte
    * Affichage
    */

}

//Display an error
void error(){
    printf("ERREUR 410\n
    \n
    Nos serveurs DNS stockés sur la Lune ne sont actuellement pas en phase avec nos 15 satelites ultraperformants.\n
    Nos équipes entrainées par deep-IP-learning sont en train de resoudre ce probleme.n");
}

//Generate a random quote of Percaval (or Karadoc)
void kaamelott(){
    system("cat data/quotes.txt | head -n `expr $[($RANDOM % (15)) +2] \* 2` | tail -n 2");
}