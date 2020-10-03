#include "functions.h"

void z_signal_handler(int sig)
{
    int pid = getpid();
    int currgpid = getpgid(pid);

    // char* temp = mallify; forn(i) temp[i] = '\0';
    // sprintf(temp,"pid and currpgid is %d %d\n",pid,currgpid);
    // write(2,temp,30);

    if(shellpgid != currgpid)
        kill(pid,SIGTSTP);

    else
        display();

}
