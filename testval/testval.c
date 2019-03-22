#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char *s="ls";
    int i = 0;
    while(s[i]!='\0'){
        i++;
    }
    
    printf("%d",i);
}
