#include "functions.h"

int Dir(char *file_name)
{
	struct stat st;

	if(stat(file_name,&st) < 0) return -1;
	
	if(S_ISDIR(st.st_mode)) return 1;

	if(S_ISREG(st.st_mode)) return 1;
	
	else return 0;
}

void command(char *rline)
{
	char *line = (char*)malloc(1024*sizeof(char)); forn(i) line[i] = '\0';
	char *line2 = (char*)malloc(1024*sizeof(char)); forn(i) line2[i] = '\0';

	char *sptr;
	char *sptr2;

	strcpy(line,rline);

	if(strcmp(line,"clear") == 0)
	{
		printf("\e[1;1H\e[2J");
		return;
	}

	//parsing the command by ';' 

	for(int q=1; ;q++)
	{
		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok_r(line,";", &sptr); 
		line = NULL;

		if(token == NULL)
			break;

		char permtoken[1024] = "";
		strcpy(permtoken,token);
		
		line2 = token;
		int back = 0;

		for(int j=0;  ;j++)
		{
			char *subtoken = (char*)malloc(1024*sizeof(char));
			for(int i=0;i<1024;i++) subtoken[i] = '\0';

			subtoken = strtok_r(line2," \t", &sptr2);
			line2 = NULL;
	
			//piping
			if(subtoken == NULL)
				break;	

			int pip = 0;

			for(int i=0;i<1024;i++)
			{
				if((permtoken[i] == '|'))
				{
					piping(permtoken);
					pip = 1;
					break;
				}
			}

			if(pip == 1)
				break;            

			//redirection
			int redirection = 0;
			for(int i=0;i<1024;i++)
			{
				if((permtoken[i] == '<'))
				{
					redirec(permtoken);
					redirection = 1;
					break;
				}
				if((permtoken[i]=='>'))
				{
					redirec(permtoken);
					redirection = 1;
					break;
				}
				
			}

			if(redirection == 1)
				break;           

			if(strcmp(subtoken,"pwd") == 0)
			{
				ExecutePwd();
				break;
			}
			
			if(strcmp(subtoken,"cd") == 0)
			{	
				char *var = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) var[i] = '\0';
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t", &sptr2);
					if(subtoken == NULL) break;
					strcat(var,subtoken);
					strcat(var," ");
				
				}	
				ExecuteCd(var);
				free(var);
				break;
			}

			if(strcmp(subtoken,"echo") == 0)  
			{
				char *var = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) var[i] = '\0';
			
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t", &sptr2);
					if(subtoken == NULL) break;
					{
						strcat(var,subtoken);
						strcat(var," ");
					}
				}
				ExecuteEcho(var);
				free(var);
				printf("\n");
				break;
			}

			if(strcmp(subtoken,"ls") == 0)  
			{
				int l = 0;
				int a = 0;
				int al=0;
				
				char *var = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) var[i] = '\0';
				var[0] = ' ';
				// printf("at the start var is %s\n",var);
				int dir = 0;
				int notfile = 0;
				// printf("subtoken is: %s\n",subtoken);
				while(subtoken != NULL)
				{
					//check if subtoken is valid
					//checking for flags
					{
						if(Dir(subtoken) == 1) //|| subtoken == '~'
						{
							// printf("its a dir or file is provided (not ls) \n");
							dir = 1;
						}
						else if(subtoken[0] == '~')
						{
							dir = 1;
							char *var3 =  (char*)malloc(1024*sizeof(char));
							for(int i=0;i<1024;i++) var3[i] = '\0';
			
							int j=0;
							for(int i=1;i<strlen(subtoken);i++)
							{
								var3[j] = subtoken[i]; j++;
							}

							// printf("var3 is %s\n",var3);
							char *temp = (char*)malloc(1024*sizeof(char));
							for(int i=0;i<1024;i++) temp[i] = '\0';

							sprintf(temp,"%s%s",root_dir,var3);
							// printf("temp is %s\n",temp);

							if(Dir(temp) != 1)
								notfile = 1;

							free(temp);
							free(var3);

						}
						else if(strcasecmp(subtoken,"-l") == 0)
							l = 1;
						else if(strcasecmp(subtoken,"-a") == 0)
							a = 1;
						else if(strcasecmp(subtoken,"-al") == 0)
							al = 1;
						else if(strcasecmp(subtoken,"-la") == 0)
							al = 1;
						
						else if(strcmp(subtoken,"ls") != 0)
						{
							if(Dir(subtoken) != 1)
								notfile = 1;
						}
							
					}

					strcat(var,subtoken);
					strcat(var," ");
					// printf("var is: %s\n",var);
					subtoken = strtok_r(line2," \t",&sptr2);
			
				}

				//if no specific directory or file was mentioned
				if(dir == 0)
				{
					strcat(var,".");
					strcat(var," ");
				}
				// printf("concat string is %s\n",var);
	
				if(notfile == 0) ExecuteLs(var,l,a,al);
				else printf("ls: No such file or directory\n");
				free(var);
				// free(subtoken);
				break;				
			}

			if(strcmp(subtoken,"pinfo") == 0)
			{
				long int var = -1;

				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(subtoken != NULL)
						sscanf(subtoken,"%ld",&var);
				}

				pinfo(var);
				break;
			}

			if(strcmp(subtoken,"nightswatch") == 0)
			{
				char *var = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) var[i] = '\0';

				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(subtoken == NULL) break;
					strcat(var,subtoken);
					strcat(var," ");
				}

				nightswatch(var);
				free(var);
				break;
			}

			if(strcmp(subtoken,"setenv") == 0)
			{
				char *var = mallify; forn(i) var[i] = '\0';
				char *value = mallify; forn(i) value[i] = '\0';
				int argcount = 1;
				
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(subtoken == NULL) break;
					argcount++;
					if(argcount == 2) strcpy(var,subtoken);
					if(argcount == 3) strcpy(value,subtoken);
				}
				if(argcount == 1 || argcount > 3)
				{
					printf("Invalid number of arguments.\n");
					forn(i) smiley[i] = '\0';
					strcat(smiley,":'(");
					return;
				}

				Setenv(var,value);
				break;
			}

			if(strcmp(subtoken,"unsetenv") == 0)
			{
				char *var = mallify; forn(i) var[i] = '\0';
				int argcount = 1;
				
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(subtoken == NULL) break;
					argcount++;
					if(argcount == 2) strcpy(var,subtoken);
				}
				if(argcount == 1 || argcount > 2)
				{
					printf("Invalid number of arguments.\n");
					forn(i) smiley[i] = '\0';
					strcat(smiley,":'(");
					return;
				}

				Unsetenv(var);
				break;
			}

			if(strcmp(subtoken,"quit") == 0)
			{
				exit(0);
			}

			if(strcmp(subtoken,"jobs") == 0)
			{
				Jobs();
				break;
			}

			if(strcmp(subtoken,"kjob") == 0)
			{
				int jn; int sig;
				int c = 0;
				while(subtoken != NULL)
				{	
					subtoken = strtok_r(line2," \t",&sptr2);
					if(c == 0) jn = atoi(subtoken);
					if(c == 1) sig = atoi(subtoken);
					if(c == 3)
					{
						write(2,"Incorrect number of arguments.\n",32);
						forn(i) smiley[i] = '\0';
						strcat(smiley,":'(");
						return;
					}	
					c++;
				}
				kjob(jn,sig);
				break;
			}

			if(strcmp(subtoken,"fg") == 0)
			{
				int jn;
				int c = 0;
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(c == 0) jn = atoi(subtoken);
					if(c == 2) 
					{
						write(2,"Incorrect number of arguments.\n",32);
						forn(i) smiley[i] = '\0';
						strcat(smiley,":'(");
						return;
					}
					c++;
				}
				
				fg(jn);
				break;
			}

			if(strcmp(subtoken,"bg") == 0)
			{
				int jn;
				int c = 0;
				while(subtoken != NULL)
				{
					subtoken = strtok_r(line2," \t",&sptr2);
					if(c == 0) jn = atoi(subtoken);
					if(c == 2) 
					{
						write(2,"Incorrect number of arguments.\n",32);
						forn(i) smiley[i] = '\0';
						strcat(smiley,":'(");
						return;
					}
					c++;
				}
				
				bg(jn);
				break;
			}

			if(strcmp(subtoken,"overkill")==0)
			{
				overkill();
				break;
			}

			//commands executed with execvp
			char* arg[50]; 
			int num_tok = 0; //last val of arg can be set as NULL
			char*command = mallify; forn(i) command[i] = '\0'; //saved bg process without &

			//recognizing bg or fg and saving values in arg array
			while(subtoken != NULL)
			{
				if(strcmp(subtoken,"&") == 0) 
					back = 1;
				
				else 
				{
					arg[num_tok] = subtoken;
					strcat(command,arg[num_tok]);
					strcat(command," ");
					num_tok++;
				}
				subtoken = strtok_r(line2," \t",&sptr2);
			}

			arg[num_tok] = NULL;
		
			int forkreturn = fork();

			if(forkreturn == -1)
			{
				perror("forkerror");
				forn(i) smiley[i] = '\0';
				strcat(smiley,":'(");
				exit(EXIT_FAILURE);
			}

			if(forkreturn == 0)
			{
				if(back == 0)
				{
					if(execvp(arg[0],arg) == -1)
					{
						perror("Error in child fg proccess");
						exit(EXIT_FAILURE);
					}
				}

				else if(back == 1)
				{
					setpgid(0,0);
					if(execvp(arg[0],arg) == -1)
					{
						perror("Error in child bg process");
						exit(EXIT_FAILURE);
					}
				}
			}

			if(forkreturn != 0)
			{
				// printf("parent process id is %d\n",getpid());
				int status;
				if(back == 0) 
				{
					waitpid(forkreturn,&status,WUNTRACED);

					if(status != 0)
					{
						forn(i) smiley[i] = '\0';
						strcat(smiley,":'(");
					}
					
					if(WIFSTOPPED(status) == 1)
					{
						forn(i) smiley[i] = '\0';
						strcat(smiley,":'(");
						insert(forkreturn,command);
					}
				}
				else if(back == 1)
				{
					// printf("forkreturn is %d\n",forkreturn);
					insert(forkreturn,command);
				}
			}

			break;
		}
	}

	return;

}


