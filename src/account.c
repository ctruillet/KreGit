/**
 * @file account.c
 * @author Clement Truillet (clement.truillet@univ-tlse3.fr)
 * @brief Ensemble des fonctions manipulant la structure Account
 * @version 0.1
 * @date 2019-04-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/account.h"

/**
 * @brief Structure account_s
 * 
 * Contient    
 *      - char * ID : Identifiant du compte   
 *      - char * type_account : Type du compte (PEL, Livret A, ...)   
 *      - Account next : Pointeur vers le compte suivant   
 * 
 */
typedef struct account_s{
	char ID[64];                //Identification
	char type_account[32];      //Type of account
	struct account_s* next;     //Next Account
} account ;

//Getters
char * get_id(Account acc){
	return acc->ID;
}
char * get_type_account(Account acc){
	return acc->type_account;
}

Account getNextAccount(Account ac){
	return ac->next;
}

//Setters
void set_ID(Account acc, char * ID){
	strcpy(acc->ID,ID);
}

void set_type_account(Account acc, char * type){
	strcpy(acc->type_account,type);
}

void InfoAccount(Account a){
	printf("--------------------------\n| Compte %s\n| \tType : %s\n| \tSuivant ? %s\n--------------------------\n",get_id(a),get_type_account(a),(getNextAccount(a)!=NULL)?"Oui":"Non");
}

Account setAccount(char * ID){
	Account ac = (Account) malloc(sizeof(struct account_s));
	set_ID(ac,ID);
	char temp[32]= "\0";

	strcpy(temp,ID);
	// Get the first token
	char *type = strtok(temp,"-"); // merdier token
	set_type_account(ac,type);
	ac->next=NULL;
	return (ac);
}

Account addNewAccount(Account a, Account aAdd){
	if(a==NULL){
		a=aAdd;
	}else{
		Account ac = a;
		while (ac->next != NULL){
			//printf(">> on passe le Compte %s\n",get_id(ac));
			ac = getNextAccount(ac);
		}
		ac->next = aAdd;
	}
	return a;
}


int nbrAccount(Account a){
	if(a == NULL){
		return 0;
	}else{
		int size = 0;
		Account ac = a;             //to avoid modification on the pointeur
		while (ac != NULL){         //while we didn't reach the end of the list
			size++;
			ac = ac->next;
		}
		return size;
	}
}

char *List_accountToString(Account a){
	Account a2 = a;                                     //to avoid modification on the pointeur
	char * strR = (char *)malloc(sizeof(char)*128);
	char str[128] = "[";
	while(a2!=NULL){
		strcat(str,"\"");
		strcat(str,a2->ID);
		strcat(str,"\"");
		if(a2->next != NULL){
			strcat(str,",");
		}
		a2 = a2->next;
	}
	strcat(str,"]");
	strcpy(strR,str);
	return strR;
}

//file management
char * createAccountID(char * type){
	char *ID = (char*)malloc(32);
	char *timeS = (char*)malloc(32);
	time_t temps;
	struct tm date;

	// Recuperation de la date et l'heure actuelle.
	time(&temps);
	date=*localtime(&temps);

	// Remplissage de la chaÃ®ne avec en date_heure
	strftime(timeS, 128, "%m%d%Y%H%M%S", &date);
	sprintf(ID,"%s-%s",type,timeS);
	
	return ID;
}

void createAccountCsv(char * ID){
	char path[64];
	sprintf(path,"data/account/%s.csv",ID);
	//récupère la date et l'heure
    char *timeS = (char *)malloc(32);
    time_t temps;
    struct tm date;
    time(&temps);
    date = *localtime(&temps);
    strftime(timeS, 128, "[%Y-%m-%d|%H:%M]", &date);


	FILE * fileCSV = fopen(path, "a");
	if (fileCSV != NULL){
		fprintf(fileCSV, "date,operation,solde,comments\n%s,0,0, ",timeS);
		fclose(fileCSV);
	}
}

int newOperation(Account a, double operation, char * comment){
	/* ToDo
	*   Ouvrir le fichier CSV associÃ©
	*   Faire l'opÃ©ration
	*   Mettre a jour le solde
	*/
	return 0;
}

Account createAccount(char * ID, char * type_account){
	Account acc = (Account)malloc(sizeof(struct account_s));
	set_ID(acc,ID);
	set_type_account(acc,type_account);
	acc->next=NULL;

	return acc;
} 