#include "functions.h"

void piping(char *line)
{
    // what about || and ||| 

    char *delim = "|";

    char *commands[150]; //set to null?

    int i = 0;
    char *sptr;

    char *token = mallify; forn(i) token[i] = '\0';
    
    token = strtok_r(line,delim,&sptr);
    line = NULL;
 
    commands[i] = token;

    for(int j=0; ;j++)
    {
        token = strtok_r(line,delim,&sptr);
        if(token == NULL) break;
        ++i;
        commands[i] = token;
    }

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    int fd[2];

    // int out = 1;
    // int in = 0;


    for(int k=0;k<=i;k++)
    {
        if( pipe(fd) < 0)
        {
             perror("Pipe Error");
             forn(i) smiley[i] = '\0';
		    strcat(smiley,":'(");
        }
        
        int pid = fork();
        if(pid < 0)
        {
            perror("Fork error");
            forn(i) smiley[i] = '\0';
		    strcat(smiley,":'(");
        }

        if(pid == 0)
        {
            close(fd[0]);
            
            if(k == i) dup2(saved_stdout,1); 
            else dup2(fd[1],1);

            //dup2(in,0);

            command(commands[k]);
            close(fd[1]);

            exit(0);
        }
        
        else if(pid > 0)
        {  
            close(fd[1]);
            wait(NULL); 
            
            //in = fd[0];

            dup2(fd[0],0);
            close(fd[0]);
        }
    }

    if( dup2(saved_stdout,1) < 0)
    {
         perror("dup2 error");
         forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
    }
    if (dup2(saved_stdin,0) < 0) 
    {   
        perror("dup2 error stdin");
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
    }

    return;

}