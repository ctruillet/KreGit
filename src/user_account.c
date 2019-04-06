/**
 * @file user_account.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions manipulant la structure User_Account
 * @version 0.1
 * @date 2019-04-03
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
    char u_ID[64];         //ID of .json file
    int admin;             //account with admin rights
    char name[32];         //name of user
    char firstname[32];    //first name of user
    char pwd[64];          //password link to the account
    struct account_s* first;         //list of account own by user
} user_account ;

//getters
int is_admin(User_account uacc){
    return (uacc->admin);
}

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
    if(is_admin(ua)==1){
        printf("--------------------------\n| ADMINISTRATEUR %s\n| \tNom : %s\n| \tPrenom : %s\n--------------------------\n",
        get_u_ID(ua),
        get_name(ua),
        get_firstname(ua));

    }else{
        printf("--------------------------\n| Utilisateur %s\n| \tNom : %s\n| \tPrenom : %s\n| \tNombre de compte :  %d\n--------------------------\n",
        get_u_ID(ua),
        get_name(ua),
        get_firstname(ua),
        nbrAccount((Account)getAccount(ua)));
    }
    
}

//Setters

User_account setUser(char * ID, int admin, char * name, char * firstname, char * pwd){
    User_account ua = NULL;
    ua = (User_account)malloc(sizeof(struct user_account_s)); 
    set_admin(ua, admin);
    set_firstname(ua,firstname);
    set_UID(ua,ID);
    set_name(ua,name);
    set_firstname(ua,firstname);
    set_pwd(ua,pwd);
    setAccountFirst(ua,NULL);

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
    strcpy(uacc->pwd,pwd);
}

void set_UID(User_account uacc, char *ID){
    strcpy(uacc->u_ID,ID);
}

void setAccountFirst(User_account uacc, Account ac){
    ((uacc->first)=ac);
    
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
    
    // Remove the user's line in ListUser.dat
    FILE * fileIN;
    FILE * fileOUT;
    char line[128] = "";
    char lineF[128] = "";

    char name[32];
    char firstname[32];
    char pwd[64];
    char json[64] = "data/user_account/";

    strcpy(name,get_name(ua));
    strcpy(firstname,get_firstname(ua));
    strcpy(pwd,get_pwd(ua));
    sprintf(json,"data/user_account/%s.json",get_u_ID(ua));

    //printf(">>\n\t%s\n\t%s\n\t%s\n\t%s\n<<\n",name,firstname,pwd,json);

    char * nameF;
    char * firstnameF;
    char * pwdF;
    char * jsonF;

    int isEquals = 1;

    fileIN = fopen("data/user_account/listUser.dat","r");
    fileOUT = fopen("data/user_account/listUserOUT.dat","w");

    if(fileIN != NULL){
        while (fgets(line, 128, fileIN) != NULL){
            strcpy(lineF,line);
            for(int i=0; ((i<4) && isEquals == 1);i++){
                switch(i){
                    case 0:
                        nameF = strtok(line, ",");
                        if(strcmp(name, nameF) != 0){
                            isEquals = 0;
                        }
                        break;
                    case 1:
                        firstnameF=strtok(NULL, ",");
                        if(strcmp(firstname, firstnameF) != 0){
                            isEquals = 0;
                        }
                        break;
                    case 2:
                        jsonF = strtok(NULL, ",");
                        if(strcmp(json, jsonF) != 0){
                            isEquals = 0;
                        }
                        break;
                    case 3:
                        pwdF = strtok(NULL, " ");
                        if(strcmp(pwd, pwdF) != 0){
                            isEquals = 0;
                        }
                        break;
                }
                
            }
            if(isEquals == 0){
                fprintf(fileOUT,"%s",lineF);
            }
            isEquals=1;
        }

    }else{
        fprintf(stderr,"Impossible d'ouvrir le fichier");
    }
    fclose(fileIN);
    fclose(fileOUT);

    remove("data/user_account/listUser.dat");
    rename("data/user_account/listUserOUT.dat","data/user_account/listUser.dat");

    ua = create_user_account(get_u_ID(ua),is_admin(ua),get_name(ua),get_firstname(ua),encryptPassword(newpwd),getAccount(ua));
    addUserInList(get_name(ua),get_firstname(ua),get_u_ID(ua),encryptPassword(newpwd));
    InfoUser(ua);

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
    printf(">> COMPTES : %s\n",List_accountToString(a));

    char path[64];
    sprintf(path,"data/user_account/%s.json",uID);

    //Remplissage du json

    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    char *serialized_string = NULL;
    FILE *jsonF = NULL;

    jsonF = fopen(path, "w+"); //Open json File

    json_object_dotset_string(root_object, "user_account.ID", uID);
    json_object_dotset_number(root_object, "user_account.admin", (double)admin);
    json_object_dotset_string(root_object, "user_account.firstname", firstname);
    json_object_dotset_string(root_object, "user_account.name", name);
    json_object_dotset_string(root_object, "user_account.pwd", pwd);
    json_object_dotset_value(root_object, "user_account.List_account",json_parse_string(List_accountToString(a)));
    //json_object_dotset_value(root_object, "user_account.List_account",json_parse_string("[\"LivretA-852148\",\"PEL-784585\",\"LivretA-055867\",\"LivretA-04032019221223\"]"));
    
    serialized_string = json_serialize_to_string_pretty(root_value);
    fprintf(jsonF,"%s",serialized_string);
    fclose(jsonF);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);

    //Ajout du compte dans la liste des users

    

    User_account uacc = setUser(uID, admin, name, firstname, pwd);
    setAccountFirst(uacc,a);

    return uacc;
}

void addUserInList(char * name, char * firstname, char * ID, char * pwd){
    FILE *listUser = NULL;
    char path[64]= "";
    sprintf(path,"data/user_account/%s.json",ID);
    listUser = fopen("data/user_account/listUser.dat","a");
    fprintf(listUser,"%s,%s,%s,%s \n",name,firstname,path,pwd);
    fclose(listUser);
}

//charge the infos of the json into the user_account struct
User_account charge_user_account(char * file, int * isAdmin){
    //size attribution for the struct
    Account ac = NULL;
    Account first = NULL;
    User_account uacc = NULL;
    uacc = (User_account)malloc(sizeof(struct user_account_s)); 
    //uacc->first=(Account)malloc(sizeof(Account));
    

    JSON_Value *root_value;
    JSON_Object *root_object;
    char elt[32];
    JSON_Array * list;

    /* parsing json */
    root_value = json_parse_file(file);
    root_object = json_value_get_object(root_value);

    // User
    uacc = setUser((char*)json_object_dotget_string(root_object, "user_account.ID"), //Visiblement ac merde ici
            (int)json_object_dotget_number(root_object, "user_account.admin"),
            (char*)json_object_dotget_string(root_object, "user_account.name"),
            (char*)json_object_dotget_string(root_object, "user_account.firstname"),
            (char*)json_object_dotget_string(root_object, "user_account.pwd"));

    //Liste des accounts
    list = json_value_get_array(json_object_dotget_value(root_object,"user_account.List_account"));
  
   for (int i = 0; i < json_array_get_count(list); i++) {
        strcpy(elt,json_array_get_string(list, i));    
        // Comptes
        if(i==0){
            first = setAccount(elt);
        }
        else{
            ac = setAccount(elt);        
            addNewAccount(first,ac);
        }
    }

    

    if(first!=NULL){
        setAccountFirst(uacc,first);
    }
    if(is_admin(uacc)==1){
        (*isAdmin)=1;
    }

    json_value_free(root_value);

    return uacc;
}

void remove_Ulist(User_account uacc, Account acc)
{
    Account first =  getAccount(uacc);
    if(first!=NULL && first==acc)
    {
        setAccountFirst(uacc, NULL);
    }
    else if (first != NULL)
    {
        while(getNextAccount(first)!=acc)
        {
            first=getNextAccount(first);
        }
        setNextAccount(first, getNextAccount(acc));
    }
}

void deleteAcc(User_account uacc, Account acc)
{
    remove_Ulist(uacc, acc);
    supprFichAcc(acc);
    free(acc);
}