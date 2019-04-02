/**
 * @file user_account.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions manipulant la structure User_Account
 * @version 0.1
 * @date 2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/account.h"
#include "../include/user_account.h"
#include "../include/encrypt.h"
#include "../include/parson.h"

#ifndef CLEAR_STDIN
    #define CLEAR_STDIN { int c; while((c = getchar()) != '\n' && c != EOF); }
#endif

#ifndef COLOR
    #define color(param) printf("\033[%sm",param)
#endif

/**
 * @brief Structure user_account
 * 
 * Contient    
 *      - char * u_ID : Identifiant du fichier json associé au compte   
 *      - int admin : 1 si le compte est admin, 0 sinon   
 *      - char * name : Nom de l'utilisateur   
 *      - char * firstname : Prenom de l'utilisateur   
 *      - char * pwd : Mot de passe (chiffré) de l'utilisateur   
 *      - Account first : Pointeur vers le premier compte de l'utilisateur (début de la liste)   
 * 
 */
typedef struct user_account_s{
    char u_ID[32];         //ID of .json file
    int admin;             //account with admin rights
    char name[32];         //name of user
    char firstname[32];    //first name of user
    char pwd[32];          //password link to the account
    struct account_s* first;         //list of account own by user
} user_account ;

//getters
int is_admin(User_account uacc){
    return (uacc->admin);
}
/**
 * @param User_account 
 * @return ID de l'Utilisateur
 */
char * get_u_ID(User_account uacc){
    return (uacc->u_ID);
}

char * get_name(User_account uacc){
    return (uacc->name);
}

char * get_firstname(User_account uacc){
    return (uacc->firstname);
}

char * get_pwd(User_account uacc){
    return (uacc->pwd);
}

Account getAccount(User_account uacc){
    return (uacc->first);
}

void InfoUser(User_account ua){
    printf("--------------------------\n| Utilisateur %s\n| \tNom : %s\n| \tPrenom : %s\n| \tPassword : %s\n| \tAdmin ? %s\n--------------------------\n",
    get_u_ID(ua),
    get_name(ua),
    get_firstname(ua),
    get_pwd(ua),
    (is_admin(ua)==1?"Oui":"Non"));
    /*printf("--------------------------\n| Utilisateur %s\n| \tNom : %s\n| \tPrenom : %s\n| \tPassword : %s\n| \tAdmin ? %s\n| \tNombre de compte :  %d\n--------------------------\n",
    get_u_ID(ua),
    get_name(ua),
    get_firstname(ua),
    get_pwd(ua),
    (is_admin(ua)==1?"Oui":"Non"),
    nbrAccount((Account)getAccount(ua)));*/
}

//Setters

User_account setUser(char * ID, int admin, char * name, char * firstname, char * pwd){
    //printf("- - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    User_account ua = NULL;
    //printf("- - - - - > avant malloc NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    ua = (User_account)malloc(sizeof(User_account)); 
    //printf("- - - - - > après malloc NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_admin(ua, admin);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_firstname(ua,firstname);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_UID(ua,ID);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_name(ua,name);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_firstname(ua,firstname);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    set_pwd(ua,pwd);
    //printf("- - - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);
    /*setAccountFirst(ua,a);
    printf("- - - - > NULL : %d\n",(getNextAccount(a)==NULL)?1:0);*/

    return ua;
}

void set_admin(User_account uacc, int admin){
    uacc->admin = admin;
}

void set_name(User_account uacc, char * name){
    strcpy(uacc->name,name);
}

void set_firstname(User_account uacc, char *firstname){
    strcpy(uacc->firstname,firstname);
}

void set_pwd(User_account uacc, char *pwd){
    sprintf(uacc->pwd,"%32s",pwd);
}

void set_UID(User_account uacc, char *ID){
    strcpy(uacc->u_ID,ID);
}

void setAccountFirst(User_account uacc, Account ac){
    printf("--->%s %s \n",get_id(ac),get_type_account(ac));
    ((uacc->first)=ac);
    printf("--->%s %s \n",get_id(uacc->first),get_type_account(ac));
    
}

User_account changePwd(User_account ua){
    int isPasswordGood = 0;
    char newpwd[32];
    char newpawdConfirm[32];

    while(isPasswordGood<=0 && isPasswordGood!=-3){ //Check if password is good
        printf("Nouveau mot de passe : ");
        scanf("%s",newpwd);
        CLEAR_STDIN
        printf("Confirmez le mot de passe : ");
        scanf("%s",newpawdConfirm);
        CLEAR_STDIN
        if(strcmp(newpwd,newpawdConfirm)==0)
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
            printf("\nEchec\n");
            color("0");
            return ua;
        }
            
    }

    InfoUser(ua);

    printf("--------------------------\n");
    printf("| Utilisateur %s\n",get_u_ID(ua));
    printf("| \tNom : %s\n",get_name(ua));
    printf("| \tPrenom : %s\n",get_firstname(ua));
    printf("| \tPassword : %s\n",encryptPassword(newpwd));
    printf("| \tAdmin ? %s\n",(is_admin(ua)==1?"Oui":"Non"));
    printf("--------------------------\n");
    
    
    
    
    

    //ua = create_user_account(is_admin(ua),get_name(ua),get_firstname(ua),encryptPassword(newpwd),getAccount(ua));
    //ua = create_user_account(is_admin(ua),get_name(ua),get_firstname(ua),encryptPassword(newpwd),NULL);
    InfoUser(ua);

    /*ToDo
    *   Modifier le listUser.dat
    */
   return ua;
}

//file management

char * createUser_ID(){
    char *ID = (char*)malloc(32);
    time_t temps;
    struct tm date;

    // Recuperation de la date et l'heure actuelle.
    time(&temps);
    date=*localtime(&temps);

    // Remplissage de la chaîne avec en date_heure
    strftime(ID, 128, "%m%d%Y%H%M%S", &date);
    return ID;
}

User_account create_user_account(char * uID, int admin, char *name, char *firstname, char *pwd, Account a){
    printf("Création de compte\n");
    char path[32] = "data/user_account/";
    strcat(path,uID);
    strcat(path,".json");

    //Remplissage du json
    printf("Formatage des données\n");
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *jsonF = NULL;
    FILE *listUser = NULL;

    json_object_dotset_string(root_object, "user_account.ID", uID);
    json_object_dotset_number(root_object, "user_account.admin", (double)admin);
    json_object_dotset_string(root_object, "user_account.firstname", firstname);
    json_object_dotset_string(root_object, "user_account.name", name);
    json_object_dotset_string(root_object, "user_account.pwd", pwd);
    //json_object_dotset_value(root_object, "user_account.List_account",json_parse_string(List_accountToString(a)));
    json_object_dotset_value(root_object, "user_account.List_account",json_parse_string("[\"LivretA-852148\",\"PEL-784585\",\"LivretA-055867\"]"));
    
    serialized_string = json_serialize_to_string_pretty(root_value);

    fprintf(jsonF,"%s",serialized_string);
    fclose(jsonF);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);

    //Ajout du compte dans la liste des users
    printf("Ecriture des données\n");
    listUser = fopen("data/user_account/listUser.dat","a");
    fprintf(listUser,"%s,%s,%s,%s \n",name,firstname,path,pwd);
    fclose(listUser);

    User_account uacc = setUser(uID, admin, name, firstname, pwd);

    return uacc;
}

//charge the infos of the json into the user_account struct
User_account charge_user_account(char * file, int * isAdmin){
    //size attribution for the struct
    Account ac; //= (Account)malloc(sizeof(Account));
    Account first; //= (Account)malloc(sizeof(Account));
    User_account uacc = NULL;
    uacc = (User_account)malloc(sizeof(User_account)); 
    //uacc->first=(Account)malloc(sizeof(Account));
    

    JSON_Value *root_value;
    JSON_Object *root_object;
    char elt[32];
    JSON_Array * list;

    /* parsing json */
    root_value = json_parse_file(file);
    root_object = json_value_get_object(root_value);

    /*printf("%s %s %s %s %s\n", "ID", "ADMIN", "Prenom", "Nom", "Password");
        printf("%s %d %s %s %s\n",
               json_object_dotget_string(root_object, "user_account.ID"),
               (int)json_object_dotget_number(root_object, "user_account.admin"),
               json_object_dotget_string(root_object, "user_account.firstname"),
               json_object_dotget_string(root_object, "user_account.name"),
               json_object_dotget_string(root_object, "user_account.pwd"));*/

    //Liste des accounts
    list = json_value_get_array(json_object_dotget_value(root_object,"user_account.List_account"));
    printf("Il y a %d comptes\n",(int) json_array_get_count(list));

   for (int i = 0; i < json_array_get_count(list); i++) {
        strcpy(elt,json_array_get_string(list, i));        
        /*
        * BUG
        *   Il semblerait que Account ne soit pas reconnu comme tel
        *   Bonne chance moi du futur
        *       -> Faire un constrcuteur par copie sur setAccoutFirst ?
        *       --> faire setUser sans Account dans les param ?
        *       -> refaire setUser avec UserAccount dans les params ?
        */
       
       
        // Comptes
        if(i==0){
            first = setAccount(elt);
            InfoAccount(first);
        }
        else{
            ac = setAccount(elt);
            
            printf("-> Ajout du compte %d\n",i);
            InfoAccount(ac);
            //addNewAccount(first,ac);
            printf("<- Compte %d ajouté\n",i);
        }
    }

    // User
    uacc = setUser((char*)json_object_dotget_string(root_object, "user_account.ID"), //Visiblement ac merde ici
            (int)json_object_dotget_number(root_object, "user_account.admin"),
            (char*)json_object_dotget_string(root_object, "user_account.firstname"),
            (char*)json_object_dotget_string(root_object, "user_account.name"),
            (char*)json_object_dotget_string(root_object, "user_account.pwd"));
    InfoUser(uacc);


    /* cleanup code */
    
    /* Reste a faire
    *       Remplir la structure
    *       S'occuper de List_Account
    *       La renvoyer
    */


    //json_value_free(root_value);

    return uacc;
}