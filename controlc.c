#include "functions.h"

void c_signal_handler(int sig)
{
    int pid = getpid();
    int currgpid = getpgid(pid);

    if(shellpgid != currgpid)
    {
        kill(pid,SIGINT);
    }
}