#include "functions.h"

void pinfo(long int p)
{
	// printf("entered pinfo func\n");
	long int pid;
	if(p == -1)
		pid = getpid();
	else
		pid = p;


	char *filename = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) filename[i] = '\0';
	sprintf(filename,"/proc/%ld/stat",pid);
	
	FILE *f = fopen(filename,"r");

	if(f == NULL) 
	{
		forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
		perror("Program");
		return;
	}

	char *arr = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) arr[i] = '\0';

	fgets(arr,10000,f);

	char *sptr;
	char *state;
	char *vm;

	for(int x=0; ;x++)
	{
		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok_r(arr," \t",&sptr);
		arr = NULL;

		if(token == NULL)
			break;

		if(x == 2) state = token;
		if(x == 22) vm = token;

	}

	char *filename2 = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) filename2[i] = '\0';
	sprintf(filename2,"/proc/%ld/exe",pid);

	char *com = (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) com[i] = '\0';

	readlink(filename2,com,1024);
	
	fclose(f);
	
	printf("pid -- %ld\n",pid);
	printf("Process Status -- %s\n",state);
	printf("memory -- %s\n",vm);
	printf("Executable Path -- %s\n",com);

	free(com);
	free(filename2);
	free(filename);
	free(arr);

}
