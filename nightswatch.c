
#include "functions.h"

//nightswatch -n 2 newborn

void interrupt(char *time)
{
	FILE *f;
	f = fopen("/proc/interrupts","r");

	char *buffer = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) buffer[i] = '\0';

	fgets(buffer,100000,f);
	// printf("buffer is %s\n",buffer);
	
	char *sptr;
	
	for(int x=0; ;x++)
	{
		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok_r(buffer," \t", &sptr);
		buffer = NULL;

		if(token == NULL) break;

		printf("%s\t",token);
	}

	printf("\n");
	
	fclose(f);

	char *sptr2;

	while(1)
	{
		f = fopen("/proc/interrupts","r");

		char *buffer1 = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) buffer1[i] = '\0';
		fgets(buffer1,100000,f);
		
		char *buffer2 = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) buffer2[i] = '\0';
		fgets(buffer2,100000,f);
		
		char *buffer3 = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) buffer3[i] = '\0';
		fgets(buffer3,100000,f);
		// printf("buffer is %s\n",buffer3);

		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok_r(buffer3," \t",&sptr2);
		buffer3 = NULL;

		for(int x=0; ;x++)
		{
			token = strtok_r(buffer3," \t",&sptr2);

			if(token == NULL) break;

			if(token[0] == 'I') break;

			printf("%s\t",token);
		}

		printf("\n");
		fclose(f);

		int t = atoi(time);
		sleep(t);
	}

	return;

}

void newborn(char *time)
{
	FILE *f;
	char buf[200];

	while(1)
	{
		f = fopen("/proc/loadavg","r");
		fgets(buf,sizeof(buf),f);

		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok(buf," \t\n");
		// printf("token is %s\n",token);
		
		for(int i=0;i<4;i++)
		{
			token = strtok(NULL," \t\n");
			// printf("token is %s\n",token);
			if(token == NULL)
			{
				// printf("didnt work\n");
				return;
			}
		}

		printf("%s\n",token);

		fclose(f);
		int t = atoi(time);
		sleep(t);

	}


}

void nightswatch(char *var)
{
	char *input = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) input[i] = '\0';

	char *time = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) time[i] = '\0';

	char *command = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) command[i] = '\0';

	char* sptr;

	for(int x = 0; ;x++)
	{
		input = strtok_r(var," \t",&sptr);
		var = NULL;

		if(input == NULL) break;

		if(x == 1) time = input;
		if(x == 2) command = input;

		if(x > 2)
		{
			forn(i) smiley[i] = '\0';
			strcat(smiley,":'(");
			printf("Wrong number of arguments\n");
			return;
		}
	}

	// printf("command and time is %s %s\n",command,time);

	int j = 0;

	if(strcmp(command,"interrupt") != 0 && strcmp(command,"newborn") != 0)
	{
		forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
		printf("Nightswatch: incorrect commands entered\n");
		return;
	}

	long int forkreturn;
	forkreturn = fork();

	if(forkreturn == 0)
	{
		if(strcmp(command,"interrupt") == 0)
		{
			// printf("entered child interrupt\n");
			interrupt(time);
		}
		if(strcmp(command,"newborn") == 0)
		{
			// printf("entered child newborn\n");
			newborn(time);
		}
		exit(0);
	}

	if(forkreturn > 0)
	{
		// printf("parent id and child id %d %ld\n",getpid(),forkreturn);
		while(1)
		{
			char ip = getc(stdin);
			if(ip == 'q')
			{
				kill(forkreturn,SIGKILL);
				waitpid(forkreturn,NULL,WUNTRACED);
				break;
			}
		}
		
		return;
	}
	
}