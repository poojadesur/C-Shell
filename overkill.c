#include "functions.h"

void overkill()
{
    int track = global_jobnum;

    while(track)
    {
        int pid = searchbyJob(track);
       
        if(pid == -1)
        {
            track--;
            continue;
        }

        if( kill(pid,SIGKILL) < 0)
        {
            forn(i) smiley[i] = '\0';
			strcat(smiley,":'(");
            write(2,"Error with sending signal.\n",27);
        }

        sleep(0.2);
    
        track--;
    }

    return;
}