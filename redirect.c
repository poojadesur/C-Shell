#include "functions.h"

void redirec(char *line)
{
    char *line2 = mallify; forn(i) line2[i] = '\0';
    strcpy(line2,line); 
    
    char *comm = mallify;
    forn(i) comm[i] = '\0';
     
    for(int i=0;i<strlen(line2);i++)
    {
        if((line2[i] == '<') || (line2[i] == '>'))
        break;
        comm[i] = line2[i];
    }

    //parsing by space
    char *subtoken = mallify; forn(i) subtoken[i] = '\0';
    char *sptr;

    //token has no spaces 
    char *token = mallify; 
	forn(i) token[i] = '\0';

    subtoken = strtok_r(line2," \t",&sptr);
    line2 = NULL;
    
    while(subtoken != NULL)
    {
        strcat(token,subtoken);
        subtoken = strtok_r(line2," \t",&sptr);
    }

    int setback = 0;
    int len = strlen(token);
    if(token[len-1] == '&')
    {
        setback = 1;
    }

    char *re_input = mallify;
    forn(i) re_input[i] = '\0';

    char *re_output = mallify;
    forn(i) re_output[i] = '\0';

    char *re_apoutput = mallify;
    forn(i) re_apoutput[i] = '\0';

    int flag = 0;

    int ipfd = dup(STDIN_FILENO); //input fd
    int opfd = dup(STDOUT_FILENO); //outpud fd

    int i = 0;

    while(i < strlen(token))
    {
        if(token[i] == '<')
        {
            //error correction if < <
            if(i+1 < strlen(token))
            {
                if(token[i+1] == '<' || token[i+1] == '>' )
                {
                    forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
                    write(2,"Syntax error near unexpected token.\n",36);
                    flag = 1;
                    break;
                }
            }

            //error correction if last char is <
            if (i == (strlen(token) - 1))
            {
                forn(i) smiley[i] = '\0';
		        strcat(smiley,":'(");
                write(2,"Syntax error near unexpected token.\n",37);
                flag = 1;
                break; 
            }
        
            i++;
            int j = 0;
            forn(i) re_input[i] = '\0';
          
            while(token[i] != '<' && token[i] != '>' && i < strlen(token) )
            {
                re_input[j] = token[i]; j++; i++;
            }

            char* file = mallify; forn(i) file[i] = '\0';
            sprintf(file,"%s",re_input);

            close(ipfd);
            ipfd = dup(open(file,O_RDWR, 0777));
            
            if(ipfd == -1)
            {
                forn(i) smiley[i] = '\0';
		        strcat(smiley,":'(");
                perror("Error opening input file");
                flag = 1;
                break;
            }
            // printf("ipfd is %d\n",ipfd);

            continue;
        }

        else if(token[i] == '>')
        {
            //append case
            if(token[i+1] == '>')
            {
                i++;

                //error correction if < <
                if(i+1 < strlen(token))
                {
                    if(token[i+1] == '<' || token[i+1] == '>' )
                    {
                        forn(i) smiley[i] = '\0';
		                strcat(smiley,":'(");
                        write(2,"Syntax error near unexpected token.\n",37);
                        flag = 1;
                        break;
                    }
                }

                //error correction if last char is <<
                if (i == strlen(token) - 1)
                {
                    forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
                    write(2,"Syntax error near unexpected token.\n",37);
                    flag = 1;
                    break; 
                }

                i++;
                int j = 0;
                forn(i) re_apoutput[i] = '\0';
                
                while(token[i] != '<' && token[i] != '>' && i < strlen(token) )
                {
                    re_apoutput[j] = token[i]; j++; i++;
                }

                char* file = mallify; forn(i) file[i] = '\0';
                sprintf(file,"%s",re_apoutput);

                // printf(">> file is %s ",file);
                close(opfd);
                opfd = dup(open(file,O_RDWR | O_CREAT | O_APPEND, 0644));
                if(opfd == -1)
                {
                    forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
                    perror("Error opening output file");
                    flag = 1;
                    break;
                }

                // printf("opfd is %d\n",opfd);

                continue;

            }

            //rewrite case
            else
            {
                //error correction if ><
                if(i+1 < strlen(token))
                {
                    if(token[i+1] == '<')
                    {
                        forn(i) smiley[i] = '\0';
		                strcat(smiley,":'(");
                        write(2,"Syntax error near unexpected token.\n",37);
                        flag = 1;
                        break;
                    }
                }

                //error correction if last char is >
                if (i == strlen(token) - 1)
                {
                    forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
                    write(2,"syntax error near unexpected token.\n",37);
                    flag = 1;
                    break; 
                }

                i++;
                int j = 0;
                forn(i) re_output[i] = '\0';

                while(token[i] != '<' && token[i] != '>' && i < strlen(token) )
                {
                    re_output[j] = token[i]; j++; i++;
                }

                char* file = mallify; forn(i) file[i] = '\0';
                sprintf(file,"%s",re_output);

                // printf("> file is %s ",file);
                close(opfd);
                opfd = dup(open(file,O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, 0644));
                if(opfd == -1)
                {
                    forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
                    char temp[200] = " ";
                    sprintf(temp,"Program %s",file);
                    perror(temp);
                    flag = 1;
                    break;
                }

                // printf("opfd is %d\n",opfd);

                continue;

            }
        }

        else i++;

    }

    if(flag == 1) return;

    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);

    int pid = fork();

    // printf("pid is %d\n",pid);

    if(pid == -1)
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        perror("Fork Error");
        return;
    }

    if(pid == 0)
    {
        
        if( dup2(opfd,STDOUT_FILENO) < 0)
        {
            forn(i) smiley[i] = '\0';
		    strcat(smiley,":'(");
            perror("Unable to dupcliate file descriptor\n");
            exit(1);
        }
        close(opfd);
        
        if( dup2(ipfd,STDIN_FILENO) < 0)
        {
            forn(i) smiley[i] = '\0';
		    strcat(smiley,":'(");
            perror("Unable to duplicate file descriptor\n");
            exit(1);
        }
       
        close(ipfd);  //what if ipfd was originally 0? !!!!!!!!!!!!!
       
        if(setback == 1) strcat(comm," &");
        
        command(comm);

        exit(0);
    }

    if(pid != 0)
    {
        wait(NULL);
        dup2(saved_stdout,STDOUT_FILENO);
        dup2(saved_stdin,STDIN_FILENO);
        close(ipfd);
        close(opfd);
    }
  
} 