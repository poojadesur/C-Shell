#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include <unistd.h>

#include "functions.h"

void ExecuteCd(char *token2)
{
	char *token = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) token[i] = '\0';
	
	for(int i=0;i<strlen(token2)-1;i++)
		token[i] = token2[i];
	
	forn(i) cdreqprev[i] = '\0';
	forn(i) cdreqprevpath[i] = '\0';

	strcat(cdreqprev,cdprev);
	strcat(cdreqprevpath,cdprevpath);

	forn(i) cdprevpath[i] = '\0';
 	forn(i) cdprev[i] = '\0';

	if(strcmp(token,"~") == 0)
	{
		char *temp = mallify; forn(i) temp[i] = '\0';
		getcwd(temp,1023);
		strcat(cdprevpath,temp);

		int er = chdir(root_dir);

		if(er != 0)
		{
			perror("Program");
			forn(i) smiley[i] = '\0';
			strcat(smiley,":'(");
		}
		return;
	}

	if(strcmp(token,"-") == 0)
	{
		char *temp = mallify; forn(i) temp[i] = '\0';
		getcwd(temp,1023);
		strcat(cdprevpath,temp);

		printf("%s\n",cdreqprevpath);
		int er = chdir(cdreqprevpath);
		if(er != 0)
		{	
			perror("cd -");
			forn(i) smiley[i] = '\0';
			strcat(smiley,":'(");
		}
		
		return;
	}

	if(token[0] == '~')
	{
		char *temp = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) temp[i] = '\0';
		
		char *temp2 = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) temp2[i] = '\0';
		
		// printf("before %s\n",token);
		for(int i=1;i<(strlen(token));i++)
			temp[i-1] = token[i];
	
	
		sprintf(temp2,"%s%s",root_dir,temp);
		// printf("temp2 is %s/n",temp2);

		char *temp1 = mallify; forn(i) temp1[i] = '\0';
		getcwd(temp1,1023);
		strcat(cdprevpath,temp1);
		
		int er = chdir(temp2);
		
		if(er != 0) 
		{
			perror("Program");
			forn(i) smiley[i] = '\0';
			strcat(smiley,":'(");
		}

		
		
		free(temp);
		free(temp2);
		free(token);
		return;
	}

	sprintf(token,"%s",token);

	// printf("%s",token);
	char *temp = mallify; forn(i) temp[i] = '\0';
	getcwd(temp,1023);
	strcat(cdprevpath,temp);
	printf("cd prev path is %s\n",cdprevpath);

	int er = chdir(token);
	if(er != 0)
	{
		perror("chdir() failed");
		forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
	}

	
	// free(temp);
	free(token);

	return;
}

void ExecutePwd()
{
	char* pwd = mallify; forn(i) pwd[i] = '\0';
	getcwd(pwd,1024);
	printf("%s\n",pwd);
	// printf("i entered pwd\n");
}

void ExecuteEcho(char *token)
{
	printf("%s",token);

}