#include "functions.h"

void kjob(int jobnum, int sig)
{
    printf("in kjob\n");
    int pid = searchbyJob(jobnum);

    if(pid == -1)
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        write(2,"No job with given job number exists.\n",38);
        return;
    }

    if( kill(pid,sig) < 0 )
    {
        forn(i) smiley[i] = '\0';
		strcat(smiley,":'(");
        write(2,"Error with sending signal.\n",27);
    }

    return;

}