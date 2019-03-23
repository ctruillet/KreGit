#include <stdio.h>
#include <stdlib.h>

#include "../include/log.h"
#include "../include/display.h"
#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/encrypt.h"

#define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }

//FSM
enum{
    TITLE,              //0 - Welcome
    CONNECT,            //1 - Connect Page
    ADMIN_ACCOUNT,      //2 - ADMIN - Show, create, edit and remove accounts
    ADMIN_CUSTOMER,     //3 - ADMIN - Add, edit and show customers
    ADMIN,              //4 - ADMIN - Change password
    CUSTOMER_NAV,       //5 - CUSTOMER - Display accounts (and theirs types) + link toward CUSTOMER_SETTING
    CUSTOMER_ACCOUNT,   //6 - CUSTOMER - Consult account
    CUSTOMER_SETTING,   //7 - CUSTOMER - Change password or add/remove account
    END,                //8 - Goodbye !
    KAAMELOT = 42       //9 - Kaamelot
}FSM;

/*
* Clement Truillet 
* Derniere modification : 28/02/2019
*/

int main(int argc, char *argv[]){
    //Init
    char LOG[128]; 
    crea_log(LOG);
    int FSM = 0;

    title();


    //Execution
    while(FSM != 8){
        scanf("%d",&FSM);
        CLEAR_STDIN                                 //Clear buffer
        switch (FSM){
            case TITLE:                             //Welcome
                w_log(LOG,"Welcome page - FSM = 0");
                title();
                break;
            case CONNECT:
                w_log(LOG,"Connect Page - FSM = 1");//1 - Connect
                break;
            case ADMIN_ACCOUNT:                     //2 - ADMIN - Show, create, edit and remove accounts
                w_log(LOG,"ADMIN - FSM = 2");
                break;
            case ADMIN_CUSTOMER:                    //3 - ADMIN - Add, edit and show customers
                w_log(LOG,"ADMIN - FSM = 3");
                break;
            case ADMIN:                             //4 - ADMIN - Change password
                w_log(LOG,"ADMIN - FSM = 4");
                break;
            case CUSTOMER_NAV:
                w_log(LOG,"CUSTOMER - FSM = 5");    //5 - CUSTOMER - Navigation bar
                break;
            case CUSTOMER_ACCOUNT:                  //6 - CUSTOMER - Consult account
                w_log(LOG,"CUSTOMER - FSM = 6");
                break;

            case CUSTOMER_SETTING:                  //7 - CUSTOMER - Change password or add/remove account
                w_log(LOG,"CUSTOMER - FSM = 7");
                break;
        
            case END:                               //8 - Goodbye !
                w_log(LOG,"This is the end - FSM = 8");
                end();
                break;
            case KAAMELOT:
                w_log(LOG,"Ouais, c'est pas faux");
                kaamelott();
                break;  
            default:
                break;
        }
    }


    w_log(LOG,"La fonction main s'est bien executée.");


    return 0;
}