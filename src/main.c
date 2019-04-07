/**
 * @file main.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Fichier principal
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/log.h"
#include "../include/display.h"
#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/encrypt.h"

/**
 * @brief Vide le buffer stdin
 * 
 */
#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }

#ifndef COLOR
    /**
     * @brief Change la couleur d'ecriture sur stdout
     * 
     */
    #define color(param) printf("\033[%sm",param)
#endif

/*! \mainpage Kregit
*   GitHub : https://github.com/ClementTruillet/KreGit
*/


/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu | 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

/**
 * @brief Machine a état
 * 
 */
enum{
    TITLE,              //0 - Welcome
    CONNECT,            //1 - Connect Page
    CREATE_USER,        //2 - Create a new User
    CREATE_ACCOUNT,     //3 - Create a new Account
    ADMIN,              //4 - Admin interface
    CUSTOMER,           //5 - Customer interface
    SHOW_LISTACCOUNT,   //6 - Show the list of account
    SHOW_ACCOUNT,       //7 - Show one account
    TRANSFER,           //8 - Make a transfert
    CHANGE_PWD,         //9 - Change password of one user
    INFO,               //10 - Informations
    END,                //11 - Goodbye !
    KAAMELOT = 42,       //42 - Kaamelot  
    REMOVE_ACCOUNT = 66 //66 - Remove one account  
}FSM;


int main(int argc, char *argv[]){
    //Init
    srand(time(NULL));
    char LOG[128]; 
    crea_log(LOG);
      
    // Ouverture et création du fichier .log

    int FSM = 0;
    int isConnect = 0;
    int isAdmin = 0;
    char path[64];
    User_account ua = NULL;    
    Account a = NULL;

    title();

    //Execution
    while(FSM != END){
        FSM = nav(FSM,&isConnect,&isAdmin);

        switch (FSM){
            case TITLE:                             //Welcome
                ua = deconnect(&isConnect, &isAdmin, ua);
                w_log(LOG,"Welcome page - FSM = 0");
                break;

            case CONNECT:                       
                w_log(LOG,"Connect Page - FSM = 1");
                ua = connect(ua,&isConnect,&isAdmin);
                if(isConnect == 0){
                    error("Echec de l'authentification.");
                    FSM =  0;
                }else{
                    if(isAdmin==1){
                        FSM = 4;
                    }else{
                        FSM = 5;
                    }
                    InfoUser(ua);
                }
                break;

            case CREATE_USER:                     
                w_log(LOG,"Create a new User - FSM = 2");
                ua = newUser_form(ua, &isConnect);
                addUserInList(get_name(ua),get_firstname(ua),get_u_ID(ua),get_pwd(ua));
                break;

            case CREATE_ACCOUNT:        
                ua = newAccount_form(ua);    
                w_log(LOG,"Create a new Account - FSM = 3");
                break;

            case REMOVE_ACCOUNT:
                if(isAdmin==1){
                    sprintf(path,"data/account/%s.csv",get_id(a));
                    removeAccountInList(a);
                    remove(path);
                    w_log(LOG,"Remove an Account - FSM = 66");
                }
                if(nbrAccount(getAccount(ua))!=0){
                    removeAccountInList(a);
                    a = removeAccount(getAccount(ua),a);
                    ua = create_user_account(get_u_ID(ua),is_admin(ua),get_name(ua),get_firstname(ua),get_pwd(ua),a);
                    w_log(LOG,"Remove an Account - FSM = 66");
                }
                break;
            case ADMIN:              
                a=NULL;               
                w_log(LOG,"ADMIN - FSM = 4");
                break;

            case CUSTOMER: 
                a=NULL;
                InfoUser(ua);                   
                w_log(LOG,"CUSTOMER - FSM = 5");    
                break;

            case SHOW_LISTACCOUNT:  
                if(a==NULL){
                    a=displayListAccount(ua);
                }
                //InfoAccount(a);
                w_log(LOG,"Show the list of accounts - FSM = 6");
                break;
            
            case SHOW_ACCOUNT:                  
                w_log(LOG,"Show one account - FSM = 7");
                break;
            
            case TRANSFER:
                newOperation(a);
                w_log(LOG,"Transfer - FSM = 8");
                break;

            case CHANGE_PWD:
                ua = changePwd(ua);
                w_log(LOG,"Change password - FSM = 9");
                break;

            case INFO:
                w_log(LOG,"Display Informations - FSM = 10");
                info();
                break;

            case END:
                w_log(LOG,"This is the end - FSM = 11");
                end();
                break;

            case KAAMELOT:
                w_log(LOG,"Ouais, c'est pas faux");
                kaamelott();
                break;  

            default:
                error("All your base are belong to us.");
                break;
        }
    }
    w_log(LOG,"La fonction main s'est bien executée.");

    return 0;
}