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
#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/parson.h"


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
    Account first;         //list of account own by user
} user_account;

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

//Setters

User_account setUser(char * ID, int admin, char * name, char * firstname, char * pwd, Account a){
    User_account ua;
    ua = (User_account)malloc(sizeof(User_account)); 
    set_admin(ua, admin);
    set_firstname(ua,firstname);
    set_UID(ua,ID);
    set_name(ua,name);
    set_firstname(ua,firstname);
    set_pwd(ua,pwd);
    setAccountFirst(ua,a);

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

User_account create_user_account(int admin, char *name, char *firstname, char *pwd, Account a){
    char * U_id = createUser_ID();            //ToDo
    char path[32] = "data/user_account/";
    strcat(path,createUser_ID());
    strcat(path,".json");

    //Remplissage du json
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *jsonF = NULL;
    FILE *listUser = NULL;
    jsonF = fopen(path, "w+");
    json_object_dotset_string(root_object, "user_account.ID", U_id);
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
    listUser = fopen("data/user_account/listUser.dat","a");
    fprintf(listUser,"%s,%s,%s,%s \n",name,firstname,path,pwd);
    fclose(listUser);

    User_account uacc = setUser(U_id, admin, name, firstname, pwd, NULL);

    return uacc;
}

//charge the infos of the json into the user_account struct
User_account charge_user_account(char * file, int * isAdmin){
    //size attribution for the struct
    User_account uacc = NULL;
    uacc = (User_account)malloc(sizeof(User_account)); 
    //uacc->first=(Account)malloc(sizeof(Account));
    Account ac = (Account)malloc(sizeof(Account));

    JSON_Value *root_value;
    JSON_Object *root_object;
    char elt[32];
    JSON_Array * list;

    /* parsing json */
    root_value = json_parse_file(file);
    root_object = json_value_get_object(root_value);

    printf("%s %s %s %s %s\n", "ID", "ADMIN", "Prenom", "Nom", "Password");
        printf("%s %d %s %s %s\n",
               json_object_dotget_string(root_object, "user_account.ID"),
               (int)json_object_dotget_number(root_object, "user_account.admin"),
               json_object_dotget_string(root_object, "user_account.firstname"),
               json_object_dotget_string(root_object, "user_account.name"),
               json_object_dotget_string(root_object, "user_account.pwd"));

    //Liste des accounts
    list = json_value_get_array(json_object_dotget_value(root_object,"user_account.List_account"));
    printf("Il y a %d comptes\n",(int) json_array_get_count(list));

   for (int i = 0; i < json_array_get_count(list); i++) {
        strcpy(elt,json_array_get_string(list, i));
        printf("\t-%s-\n",elt);
        ac = setAccount(elt);
        /*
        * BUG
        *   Il semblerait que Account ne soit pas reconnu comme tel
        *   Bonne chance moi du futur
        */

        if(i==0){
            uacc = setUser((char*)json_object_dotget_string(root_object, "user_account.ID"),
               (int)json_object_dotget_number(root_object, "user_account.admin"),
               (char*)json_object_dotget_string(root_object, "user_account.firstname"),
               (char*)json_object_dotget_string(root_object, "user_account.name"),
               (char*)json_object_dotget_string(root_object, "user_account.pwd"),
               ac);
        }else{
            printf("-> Ajout du compte %d\n",i);
            addNewAccount(getAccount(uacc),ac);
            printf("<- Compte %d ajouté\n",i);
        }
    }

    /* cleanup code */
    
    /* Reste a faire
    *       Remplir la structure
    *       S'occuper de List_Account
    *       La renvoyer
    */


    json_value_free(root_value);

    return uacc;
}