#include <stdio.h>
#include <stdlib.h>
#include "../include/user_account.h"

/*
* Clement Truillet 
* Derniere modification : 24/02/2019
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
    printf("\nGoodbye!\n");
}

//Connect
int connect(user_account ua){
    /*Demande user_name
    *   Charger la structure
    * Demande pwd
    * Verification pwd
    *   passwordIsGood()
    */
    return 0;
}

//Display an error
void error(){
    /*Affiche une erreur
    * ? Incremente le compteur d'erreur -> bloquer l'accès au compte
    */
}