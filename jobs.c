#include "functions.h"


void Jobs()
{
	// printf("\nentered search\n");
	struct Node* curr = head;

    char *jobinfo[150];
    int i = 0;

	while(curr != NULL)
	{
		int pid = curr->pid;
		char* com = mallify; forn(i) com[i] = '\0';
        com = curr->arg;
        int jobn = curr->jobnum;

        char* filename = mallify; forn(i) filename[i] = '\0';
        sprintf(filename,"/proc/%d/stat",pid);
		
        FILE *f = fopen(filename,"r");

        if(f == NULL)
        {
            forn(i) smiley[i] = '\0';
		    strcat(smiley,":'(");
            perror("Error opening stat file");
            return;
        }

        char *arr = mallify; forn(i) arr[i] = '\0';

        fgets(arr,10000,f);

        char *sptr;
        char *state = mallify; forn(i) state[i] = '\0';

        for(int x=0; ;x++)
        {
            char *token = mallify; forn(i) token[i] = '\0';

            token = strtok_r(arr," \t",&sptr);
            arr = NULL;

            if(token == NULL)
                break;

            if(x == 2) 
            {
                state = token;
                if(strcmp(state,"T") == 0)
                    strcpy(state,"Stopped");
                else
                    strcpy(state,"Running");
    
                break;
            }   
	    }

        char* temp = mallify; forn(i) temp[i] = '\0';
        sprintf(temp,"[%d] %s %s [%d]\n",jobn,state,com,pid);
        jobinfo[i] = temp;
        i++;

	    curr = curr->next;
	}

    for(int k=i-1;k>=0;k--)
    {
        printf("%s",jobinfo[k]);
    }
	
    return;
}