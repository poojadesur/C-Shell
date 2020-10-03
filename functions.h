#ifndef HEADER_FILE
#define HEADER_FILE

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include <unistd.h>
#include<dirent.h>
#include<signal.h>
#include<sys/wait.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
 
#define forn(i) for(int i=0;i<1024;i++)
#define mallify (char*)malloc(1024*sizeof(char));
struct Node
{
	int pid;
	char* arg;
	int jobnum;
	struct Node *next;
};

extern struct Node* head;
extern struct Node* start;

void signal_handler(int sig);
void z_signal_handler(int sig);
void c_signal_handler(int sig);

void insert(int pid, char*arg);
char* searchName(int pid);
int searchbyJob(int jobnum);
int delet(int pid);
void initialise();


//global variables
char root_dir[1024];
int global_jobnum;
int shellpid;
int shellpgid;
char *cdprev;
char *cdprevpath;
char *cdreqprev;
char *cdreqprevpath;

char *smiley;

void shellStart();

void display();
void command(char* rline);

void ExecuteCd(char *token);
void ExecutePwd();
void ExecuteEcho(char *token);
void ExecuteLs(char *var, int l, int a, int al);

int isDir(char *file);
int Dir(char *file);

void longFormat(char *file);

void pinfo(long int var);

void nightswatch(char *var);
void interrupt(char *time);
void newborn(char *time);

void redirec(char *line);

void piping(char *line);

void Setenv(char *var, char *value);
void Unsetenv(char *var);

void Jobs();
void kjob(int jn,int sig);

void fg(int jn);
void bg(int jn);

void overkill();


#endif
