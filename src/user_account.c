/*
* Valentin Frydrychowski 
* Derniere modification : 27/03/2019
*/

//finir chargement list account
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "../include/user_account.h"
#include "../include/account.h"
#include "../include/parson.h"

#define NAMESIZE 32
#define FNAMESIZE 32

//structure from a user account
typedef struct user_account_s
{
    char u_ID[32];         //ID of .json file
    int admin;             //account with admin rights
    char name[32];         //name of user
    char firstname[32];    //first name of user
    char pwd[32];          //password link to the account
    Account first;         //list of account own by user
} user_account;

//getters
bool is_admin(User_account uacc)
{
    return (uacc->admin?1:0);
}

char *get_u_ID(User_account uacc)
{
    return uacc->u_ID;
}

char *get_name(User_account uacc)
{
    return uacc->name;
}

char *get_firstname(User_account uacc)
{
    return uacc->firstname;
}

char *get_pwd(User_account uacc)
{
    return uacc->pwd;
}

/*char **get_account_list(User_account uacc)
{
    //TODO toString
}*/

//Setters

User_account setUser(char * ID, int admin, char *name, char *firstname, char *pwd){
    User_account ua;
    ua = (User_account)malloc(sizeof(User_account)); 
    set_admin(ua, admin);
    set_firstname(ua,firstname);
    set_UID(ua,ID);
    set_name(ua,name);
    set_firstname(ua,firstname);
    set_pwd(ua,pwd);

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
/*
void add_Ulist(User_account uacc, Account acc)
{
    add_list(uacc->list, acc);
}*/

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
    json_object_set_number(root_object, "user_account.admin", (double)admin);
    json_object_dotset_string(root_object, "user_account.firstname", firstname);
    json_object_dotset_string(root_object, "user_account.name", name);
    json_object_dotset_string(root_object, "user_account.pwd", pwd);
    json_object_dotset_string(root_object, "user_account.List_account",List_accountToString(a));
    serialized_string = json_serialize_to_string_pretty(root_value);

    fprintf(jsonF,"%s",serialized_string);
    fclose(jsonF);
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);

    //Ajout du compte dans la liste des users
    listUser = fopen("data/user_account/listUser.dat","a");
    fprintf(listUser,"%s %s %s %s \n",name,firstname,path,pwd);
    fclose(listUser);


    User_account uacc = setUser(U_id, admin, name, firstname, pwd);

    return uacc;
}

//charge the infos of the json into the user_account struct
User_account charge_user_account(char * file){
    //size attribution for the struct
    User_account uacc = NULL;
    uacc = (User_account)malloc(sizeof(User_account)); 
    uacc->first=(Account)malloc(sizeof(Account));

    JSON_Value *root_value;
    JSON_Object *root_object;
    JSON_Array *list;

    /* parsing json */
    root_value = json_parse_file(file);

    root_object = json_value_get_object(root_value);
    list = json_object_dotget_array(root_object, "user_account.List_account");
    printf("%s %s %s %s %s %s\n", "ID", "ADMIN", "Prenom", "Nom", "Password", "Liste");
        printf("%s %d %s %s %s %s\n",
               json_object_dotget_string(root_object, "user_account.ID"),
               (int)json_object_dotget_number(root_object, "user_account.admin"),
               json_object_dotget_string(root_object, "user_account.firstname"),
               json_object_dotget_string(root_object, "user_account.name"),
               json_object_dotget_string(root_object, "user_account.pwd"),
               json_object_dotget_string(root_object, "user_account.List_account"));
    
    /*uacc = setUser(json_object_dotget_string(root_object, "user_account.ID"),
               (int)json_object_dotget_number(root_object, "user_account.admin"),
               json_object_dotget_string(root_object, "user_account.firstname"),
               json_object_dotget_string(root_object, "user_account.name"),
               json_object_dotget_string(root_object, "user_account.pwd"));
    */
    /* cleanup code */


    
    /* Reste a faire
    *       Remplir la structure
    *       S'occuper de List_Account
    *       La renvoyer
    */


    json_value_free(root_value);


    /*
    int t;
    char ID_F[32];
    char firstname_F[32];
    char name_F[32];
    char pwd_F[32];
    //filling all infos needed
    char *list = NULL;*/

    /*FILE *json = fopen(file, "r");
    if (json != NULL){
        fscanf(json, "{\n\t\"user_account\": {\n\t\t\"ID\": \"%s\",\n\t\t\"admin\": \"%d\",\n\t\t\"firstname\": \"%s\",\n\t\t\"name\": \"%s\",\n\t\t\"pwd\": \"%s\",\n\t\t\"List_account\": \"[%s]\"\n\t}\n}", ID_F, &t, firstname_F, name_F, pwd_F, list);
        printf("\nID : -%s-\n",ID_F);
        printf("isAdmin : -%d-\n",t);
        printf("Firstname : -%s-\n",firstname_F);
        printf("Name : -%s-\n",name_F);
        printf("Password : -%s-\n",pwd_F);
    }
    fclose(json);
    printf("%s\n",list);*/
    /*
    int strSize = 0;

    //Filling the List of accounts
    while (list[strSize] != '\0')
    {
        strSize++;
    }
    for (int i = 1; (strSize - 1) / i >= 1; i++)
    {
        char id[IDACCSIZE];
        for (int y = 0; y < IDACCSIZE; y++)
        {
            id[y] = list[(IDACCSIZE + 1)*(i - 1) + y];
        }
        Account acc = NULL;
        charge_account(acc, id);
        add_list(uacc->list, acc);
    }
    */
    return uacc;
}