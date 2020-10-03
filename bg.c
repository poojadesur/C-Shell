#include "functions.h"

void bg(int jobnum)
{
   int pid = searchbyJob(jobnum);

   if(pid == -1)
   {
        write(2,"Background process with given job number doesn't exist.\n",57);
        forn(i) smiley[i] = '\0';
		   strcat(smiley,":'(");
        return;
   }

   kill(pid,SIGCONT);

}