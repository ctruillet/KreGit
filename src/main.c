#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/log.h"
#include "../include/display.h"
#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/encrypt.h"


#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif
/* Paramètre  Couleur
30 Noir |31 Rouge | 32 Vert | 33 Jaune | 34 Bleu| 35 Magenta | 36 Cyan | 37 Blanc
 
"1" active la haute intensité des caractères.
*/

//FSM
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
    KAAMELOT = 42       //42 - Kaamelot    
}FSM;

/*
* Clement Truillet 
* Derniere modification : 28/03/2019
*/

int main(int argc, char *argv[]){
    //Init
    srand(time(NULL));
    char LOG[128]; 
    crea_log(LOG);
    printf("log : %s\n",LOG);
      
    // Ouverture et création du fichier .log
    FILE* logF = NULL;
    logF = fopen(LOG,"a+");
  
    //Ecriture dans log
    w_log(logF,"Création du fichier .log");

    int FSM = 0;
    int isConnect = 0;
    int isAdmin = 0;

    User_account ua;    

    title();

    //Execution
    while(FSM != END){
        FSM = nav(FSM,&isConnect,&isAdmin);

        switch (FSM){
            case TITLE:                             //Welcome
                w_log(logF,"Welcome page - FSM = 0");
                break;

            case CONNECT:                       
                w_log(logF,"Connect Page - FSM = 1");
                FSM = connect(ua,&isConnect);
                break;

            case CREATE_USER:                     
                w_log(logF,"Create a new User - FSM = 2");
                ua = newUser_form(ua, &isConnect);
                break;

            case CREATE_ACCOUNT:                  
                w_log(logF,"Create a new Account - FSM = 3");
                break;

            case ADMIN:                             
                w_log(logF,"ADMIN - FSM = 4");
                break;

            case CUSTOMER:                    
                w_log(logF,"CUSTOMER - FSM = 5");    
                break;

            case SHOW_LISTACCOUNT:                  
                w_log(logF,"Show the list of accounts - FSM = 6");
                break;
            
            case SHOW_ACCOUNT:                  
                w_log(logF,"Show one account - FSM = 7");
                break;
            
            case TRANSFER:
                w_log(logF,"Transfer - FSM = 8");
                break;

            case CHANGE_PWD:
                w_log(logF,"Change password - FSM = 9");
                break;

            case INFO:
                w_log(logF,"Display Informations - FSM = 10");
                info();
                break;

            case END:
                w_log(logF,"This is the end - FSM = 11");
                end();
                break;

            case KAAMELOT:
                w_log(logF,"Ouais, c'est pas faux");
                kaamelott();
                break;  

            default:
                error();
                break;
        }
    }

    w_log(logF,"La fonction main s'est bien executée.");

    return 0;
}