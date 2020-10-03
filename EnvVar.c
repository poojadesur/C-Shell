#include "functions.h"

void Setenv(char *var, char *value)
{
    int check = setenv(var,value,1);
    if(check == -1)
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        perror("setenv error:");
        exit(0);
    }
}

void Unsetenv(char *var)
{
    char*check = mallify; forn(i) check[i] = '\0';
    check = getenv(var);
    if(check == NULL)
        return;
    else
    {
        unsetenv(var); //works even if var doesnt exist
    }

    return;

    
}