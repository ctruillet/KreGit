#include <stdlib.h>
#include <stdio.h>
#include "../include/user_account.h"
#include "../include/account.h"


int main(int argc, char const *argv[])
{
    char *ID = "0123456789abcdef";
 
    char fileName[2 * IDACCSIZE + 18]; 
    char path[] = "data/account/.csv"; 
    for (int i = 0; i < 2 * IDACCSIZE + 19; i++)
    {
        if (i < 13)
        {
            fileName[i] = path[i];
        }
        else if (i<13+IDACCSIZE)
        {
            fileName[i]= ID[i-13];
        }
        else if (i==13+IDACCSIZE)
        {
            fileName[i]='/';
        }
        else if (i<14+2*IDACCSIZE)
        {
            fileName[i]=ID[i-(14+IDACCSIZE)];
        }
        else
        {
            fileName[i]=path[i-(2*IDACCSIZE+1)];
        }
        printf("%s\n", fileName);
    }
    
}
