#include "functions.h"

void fg(int jobnum)
{
    int pid = searchbyJob(jobnum);
    int pgid = getpgid(pid);

    if(pid == -1)
    {
        write(2,"Background process with given job number doesn't exist.\n",57);
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
	
        return;
    }

    //does it matter before or after? yes it does
    signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);

    if (tcsetpgrp(STDIN_FILENO , pgid) == -1)
    { 
        perror("tcsetgroup error 1");
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        exit(EXIT_FAILURE);

    }
    kill(pid,SIGCONT);

    int status;
   
    //change to group for control z
    waitpid(pid,&status,WUNTRACED);

    if(status != 0)
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
    }

    // printf("shellpgid is %d\n",shellpgid);

    if (tcsetpgrp(STDIN_FILENO,shellpgid) == -1)
    {
         perror("tcsetgroup error");
         forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        exit(EXIT_FAILURE);
    }

    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    char *com = searchName(pid);

    delet(pid);

    if(WIFSTOPPED(status) == 1)
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        insert(pid,com);
    }

    return;
}