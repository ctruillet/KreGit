/**
 * @file display.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions servant d'interface avec l'utilisateur
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

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
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

/*
* Clement Truillet 
* Derniere modification : 31/03/2019
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
    printf("  ____                 _ ____               _       \n");
    printf(" / ___| ___   ___   __| | __ ) _   _  ___  | |      \n");
    printf("| |  _ / _ \\ / _ \\ / _` |  _ \\| | | |/ _ \\ | |  \n");
    printf("| |_| | (_) | (_) | (_| | |_) | |_| |  __/ |_|      \n");
    printf(" \\____|\\___/ \\___/ \\__,_|____/ \\__, |\\___| (_)\n");
    printf("                               |___/                \n");
    printf("\n");
}

//Connect
User_account connect(User_account ua, int * isConnect, int * isAdmin){
    ua = (User_account)malloc(sizeof(User_account));
    char name[16];
    char firstname[16];
    char pwd[16];
    int isEquals=0; //0 - Cherche encore / 1 - Recherche / 2 - Trouvé !  

    printf("\nNom : ");
    scanf("%s",name);
    CLEAR_STDIN
    printf("Prénom : ");
    scanf("%s",firstname);
    CLEAR_STDIN
    printf("Mot de passe : ");
    scanf("%s",pwd);
    CLEAR_STDIN
    
    //Read file listUser.dat
    FILE* fichier = NULL;
    char chaine[128] = "";
    char * nameF;
    char * firstnameF;
    char * pwdF;
    char * jsonF;
    fichier = fopen("data/user_account/listUser.dat", "r");
    if (fichier != NULL){
        while ((isEquals!=2) && (fgets(chaine, 128, fichier) != NULL)){   
            isEquals=0;
            nameF = strtok(chaine, ",");
            if(strcmp(name,nameF)==0){
                isEquals=1;
            }

            for(int i=0; ((i<=2) && (isEquals!=0)); i++){
                switch(i){
                    case 0:
                        firstnameF=strtok(NULL, ",");
                        if(strcmp(firstname,firstnameF)!=0){
                            isEquals=0;
                        }
                        break;
                    case 2:
                        pwdF = strtok(NULL, " ");
                        if(strcmp(encryptPassword(pwd),pwdF)==0){
                            isEquals=2;
                        }else{
                            isEquals=0;
                        }
                        break;
                    case 1:
                        jsonF = strtok(NULL, ",");
                        isEquals=2;

                        break;
                }            
            }
        }
    }else{
        printf("Impossible d'ouvrir le fichier\n");
    }
    fclose(fichier);

    if(isEquals==2){
      //printf("\n\nName : -%s-\nFisrtname : -%s-\nPassword : -%s-\nJSON : -%s-\n",nameF, firstnameF, pwdF, jsonF);
      (*isConnect)=1;
      ua = charge_user_account(jsonF, isAdmin);
      return ua;
    }else{
      return ua;
    }
    /*Demande user_name
    * Demande pwd
    * Verification pwd
    *   passwordIsGood()
    * Charger la structure
    * Return 4 si le compte est admin
    * return 5 si le compte existe
    * return 0 sinon
    */
}

//Deconnect
User_account deconnect(int * isConnect, int * isAdmin, User_account ua){
    (*isConnect) = 0;
    (*isAdmin) = 0;
    free(ua);
    return ua;
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
    printf("Bienvenue sur l'interface de création de compte");
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

    ua=create_user_account(createUser_ID(), 0, name, firstname, encryptPassword(pwd), NULL);
    printf("\nNous vous souhaitons la bienvenue !\n\n");
    (*isConnect)=1;
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
int nav(int FSM, int * isConnect, int * isAdmin){
    int i;

    switch (FSM){
        case 0: //Welcome
            printf("\n1\\Se connecter\t");
            printf("\t2\\Creer un Compte\t");
            printf("\t3\\Informations\t");
            printf("\t4\\Quitter KreGit\n");

            scanf("%d",&i);
            CLEAR_STDIN 

            switch(i){
                case 1:
                    return 1;
                    break;
                case 2:
                    return 2;
                    break;
                case 3:
                    return 10;
                    break;
                case 4:
                    return 11;
                    break;
                case 42:
                    return 42;
                default:
                    return(0);         
            }

            break;
        case 1:
            break;
        case 2:
            return 5;
            break;
        case 3:
            return 5;
            break;
        case 4: //ADMIN
            printf("\n1\\Se Deconnecter\t");
            printf("\t2\\Changer le mot de passe\t");
            printf("\t3\\Consulter les comptes\t");
            printf("\t4\\Quitter KreGit\n");

            scanf("%d",&i);
            CLEAR_STDIN 
            if(i==1 || i==2 || i==3 || i==4){
                switch(i){
                    case 1:
                        return 0;
                        break;
                    case 2:
                        return 8;
                        break;
                    case 3:
                        return 6;
                        break;
                    case 4:
                        return 11;
                        break;
                }
            }else{
                return 4;
            }
            break;
        case 5: //CUSTOMER
            printf("\n1\\Se Deconnecter\t");
            printf("\t2\\Changer le mot de passe\t");
            printf("\t3\\Consulter mes comptes\t");
            printf("\t4\\Ajouter un compte\t");
            printf("\t5\\Quitter KreGit\n");

            scanf("%d",&i);
            CLEAR_STDIN 
            if(i==1 || i==2 || i==3 || i==4 || i==5){
                switch(i){
                    case 1:
                        return 0;
                        break;
                    case 2:
                        return 9;
                        break;
                    case 3:
                        return 6;
                        break;
                    case 4:
                        return 3;
                        break;
                    case 5:
                        return 11;
                        break;
                }
            }else{
                return 5;
            }
            break;
        case 6: //ACCOUNT
            printf("\n1\\Revenir au menu\t");
            printf("\t2\\Nouvelle opération\t");
            printf("\t3\\Quitter KreGit\n");

            scanf("%d",&i);
            CLEAR_STDIN 
            if(i==1 || i==2 || i==3){
                switch(i){
                    case 1:
                        return 5;
                        break;
                    case 2:
                        return 8;
                        break;
                    case 3:
                        return 11;
                        break;
                }
            }else{
                return 5;
            }
            break;
        case 7:
            return (5-(*isAdmin)); //Return 4 (ADMIN) if you are admin 
            break;
        case 8:
            return 7;
            break;
        case 9:
            return (5-(*isAdmin));
            break;
        case 10:
            return 0;
            break;
        case 11:
            return 11;
            break;
        case 42:
            return 0;
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
    printf("[ERREUR 410]\n\n");
    printf("Nos serveurs DNS stockés sur la Lune ne sont actuellement pas en phase avec nos 15 satelites ultraperformants.\n");
    printf("Nos équipes entrainées par deep-IP-learning sont en train de resoudre ce probleme.");
    color("0");
}

//Informations
void info(){
    printf("Kregit a été réalisé par ");
    color("35");
    printf("Valentin Frydrychowski");
    color("0");
    printf(" et ");
    color("36");
    printf("Clément Truillet");
    color("0");
    printf(" dans le cadre d\'un projet de ");
    color("34");
    printf("Structure de Données");
    color("0");
    printf(".\n");
    printf("\n\tGitHub : https://github.com/ClementTruillet/KreGit\n");
    printf("                                                                                      - Université Paul Sabatier - 2019\n");
}

//Generate a random quote of Percaval (or Karadoc)
void kaamelott(){
    color("35");
    char command[64]="cat data/quotes.txt | head -n ";
    int n = (((rand() % 16) +2 ) * 2);
    char n_s[12];
    sprintf(n_s,"%d",n);
    strcat(command,n_s);
    strcat(command," | tail -n 2");
    system(command);
    color("0");
}
