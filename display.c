
#include "functions.h"

void display()
{
	char *username = (char*)malloc(1024*sizeof(char)); 
	forn(i) username[i] = '\0';
	char *hostname = (char*)malloc(1024*sizeof(char));
	forn(i) hostname[i] = '\0';

	gethostname(hostname,1024);
	getlogin_r(username,1024);

	char *dir = (char*)malloc(1024*sizeof(char));
	forn(i) dir[i] = '\0';
	getcwd(dir,1024);
	
	if(strcmp(dir,root_dir) == 0)
	{
		printf("\033[1;36m");
		printf("%s<%s@%s:",smiley,username,hostname);
		printf("\033[0m");
		
		printf("\033[01;33m");
		printf("~");
		printf("\033[0m");

		printf("\033[1;36m");
		printf(">");
		printf("\033[0m");

	}
	
	else if( (strncmp(dir,root_dir,(strlen(root_dir))) == 0) && ((strlen(dir)) > strlen(root_dir)) )
	{
		char *temp = (char*)malloc(1024*sizeof(char)); forn(i) temp[i] = '\0';
		
		int j = 0;
		for(int i=(strlen(root_dir)+1);i<(strlen(dir));i++)
		{
			temp[j] = dir[i];
			// printf("op: %c\n",(char)temp[j]);
			j++;
		}

		printf("\033[1;36m");
		printf("%s<%s@%s:",smiley,username,hostname);
		printf("\033[0m");

		printf("\033[01;33m");
		printf("~/%s",temp);
		printf("\033[0m");

		printf("\033[1;36m");
		printf(">");
		printf("\033[0m");

	}
	
	else
	{
		printf("\033[1;36m");
		printf("%s<%s@%s:",smiley,username,hostname);
		printf("\033[0m");

		printf("\033[01;33m");
		printf("%s",dir);
		printf("\033[0m");

		printf("\033[1;36m");
		printf(">");
		printf("\033[0m");
	}

	free(username);
	free(hostname);
	free(dir);

}

