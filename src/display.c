#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/encrypt.h"
#include "../include/display.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif
/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu| 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

/*
* Clement Truillet 
* Derniere modification : 26/03/2019
*/

//Display title
void title(){
    color("33;1");
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
    color("0");
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
void deconnect(int * isConnect, User_account ua){
    (*isConnect) = 0;
    free(ua);
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
User_account newUser_form(User_account ua, int * isConnect){
    char name[16];
    char firstname[16];
    char pwd[16];
    char confirm_pwd[16];
    int isPasswordGood = 0;
    color("32");
    printf("Bienvenue sur l'interace de création de compte");
    color("0");
    printf("\nNom : ");
    scanf("%s",name);
    CLEAR_STDIN
    printf("Prénom : ");
    scanf("%s",firstname);
    CLEAR_STDIN
    while(isPasswordGood<=0 && isPasswordGood != -3){ //Check if password is good
        
        printf("Mot de passe : ");
        scanf("%s",pwd);
        CLEAR_STDIN
        printf("Confirmez le mot de passe : ");
        scanf("%s",confirm_pwd);
        CLEAR_STDIN
        if(strcmp(pwd,confirm_pwd)==0)
            isPasswordGood=1;            
        if(isPasswordGood<=0){
            color("31");
            printf("\n/!\\ Mots de passe non identiques /!\\\n");
            color("0");
            if(2+isPasswordGood>0)
              printf("Il vous reste %d essais \n",2+isPasswordGood);
            isPasswordGood--;
        }

        if(isPasswordGood==-3){
            color("31");
            printf("\nEchec de la création de compte\n");
            color("0");
            return NULL;
        }
            
      }
      printf("\nNous vous souhaitons la bienvenue !\n");
    List_account l;
    l=(List_account)malloc(sizeof(List_account));
    ua=create_user_account(false, name, firstname, encryptPassword(pwd), l);

   return ua;
}

//Nav_bar - Display all accounts of user with theirs types
int displayListAccount(User_account ua, int FSM){
    /*
    * Affichage des comptes avec leurs types + Solde
    * Bouton "Nouvelle Opération" 
    */
    return 0;
}

//Nav bar
int nav(int FSM, int * isConnect){
    switch (FSM){
        case 0:
            if(isConnect){

            }else{
                printf("Se connecter    - 1\n");
                printf("Creer un Compte - 8\n");
                printf("Quitter KreGit  - 9\n");
            }
            break;
    
        default:
            break;
    }
    
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
    color("31");
    printf("ERREUR 410\n\n");
    printf("Nos serveurs DNS stockés sur la Lune ne sont actuellement pas en phase avec nos 15 satelites ultraperformants.\n");
    printf("Nos équipes entrainées par deep-IP-learning sont en train de resoudre ce probleme.n");
    color("0");
}

//Generate a random quote of Percaval (or Karadoc)
void kaamelott(){
    color("35");
    char command[64]="cat data/quotes.txt | head -n ";
    int n = (((rand() % 15) +2 ) * 2);
    char n_s[12];
    sprintf(n_s,"%d",n);
    strcat(command,n_s);
    strcat(command," | tail -n 2");
    system(command);
    color("0");
}
