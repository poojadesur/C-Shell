#include "functions.h"

struct Node* head = NULL;
struct Node* start = NULL;

char *smiley;

void signal_handler(int sig)
{
	int status;
	int childpid = waitpid(-1,&status,WNOHANG);

	if(childpid == -1)
		return;
	
	if(childpid > 0)
	{

		char *com = searchName(childpid);

		int err = delet(childpid);

		if(err == -2) 
		{
			// printf("error after deleting\n");
			return;
		}

		char *buf = (char*)malloc(1000*sizeof(char));
		for(int i=0;i<1000;i++) buf[i] = '\0';

		//WIFEXITED returns true when proccesses are normally terminated.
		// printf("WIFEXITED VAL %d\n",WIFEXITED(status));

		if ( !WIFEXITED(status))
		{	
			sprintf(buf,"\n%swith pid %d exited abnormally.\n",com,childpid);
			write(2,buf,100);
			fflush(NULL);
			return;	
		}

		int exit_status = WEXITSTATUS(status);
		sprintf(buf,"\n%swith pid %d exited normally with exit status %d.\n",com,childpid,exit_status);
		write(2,buf,1000);
		fflush(NULL);

		return;
	}

}

char root_dir[] = "";
int global_jobnum; //keep track of all background jobs
int shellpid;
int shellpgid;
char *cdprev;
char *cdprevpath;
char *cdreqprev;
char *cdreqprevpath;


int main()
{
	int status = 1; //1 means no error, 0 means error

	system("clear");
	
	getcwd(root_dir,1024);

	cdprev = mallify; forn(i) cdprev[i] = '\0';
	cdprevpath = mallify; forn(i) cdprevpath[i] = '\0';
	cdreqprev = mallify; forn(i) cdreqprev[i] = '\0';
	cdreqprevpath = mallify; forn(i) cdreqprevpath[i] = '\0';

	smiley = mallify; forn(i) smiley[i] = '\0';
	strcat(smiley,":')");

	strcat(cdreqprev,"\0");
	strcat(cdreqprevpath,root_dir);
	strcat(cdprev,"\0");
	strcat(cdprevpath,root_dir);

	// read, parse, execute loop
	shellStart();

	shellpid = getpid();
	shellpgid = getpgid(shellpid);

	signal(SIGCHLD,signal_handler);
	signal(SIGTSTP,z_signal_handler);
	signal(SIGINT,c_signal_handler);

	global_jobnum = 0;
	
	do
	{	
		display(); //displaying the username and hostname

		forn(i) smiley[i] = '\0';
		strcat(smiley,":')");
		
		//reading input
		char *rline = (char*)malloc(1024*sizeof(char)); forn(i) rline[i] = '\0';
		long int len = 0;
		long int char_read = getline(&rline,&len,stdin);
		int length = (int)strlen(rline);
		rline[length-1] = '\0';

		if(char_read == -1)
		{
			perror("Error:");
			exit(0);
		}
	
		command(rline);
		// printf("exited command\n");

	} while(status);


	return 0;
}