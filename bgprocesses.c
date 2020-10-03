#include "functions.h"

//linked list to keep track of all background proccesses

void insert(int pid, char *arg)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->pid = pid;
	newNode->arg = arg;
	++global_jobnum;
	newNode->jobnum = global_jobnum;

	newNode->next = head;

	// printf("\nnewNode->pid = %d newNode->arg = %s \n", newNode->pid, newNode->arg);

	head = newNode;
}

char* searchName(int pid)
{
	// printf("\nentered search\n");
	struct Node* curr = head;
	// printf("value of curr %d\n",curr);
	while(curr != NULL)
	{
		int rpid = curr->pid;
		char* com = curr->arg;
		// printf("curr->pid %d curr->arg %s\n",rpid,com);
		
		if(rpid == pid)
		{
			// printf("MATCHED\n");
			return com;
		}
		else
		{
			curr = curr->next;
		}

	}
	return " ";
}

 int searchbyJob(int jobnum)
{
	// printf("\nentered search\n");
	struct Node* curr = head;
	// printf("value of curr %d\n",curr);
	while(curr != NULL)
	{
		int rpid = curr->pid;
		char* com = curr->arg;
		int jn = curr->jobnum;
		// printf("curr->pid %d curr->arg %s\n",rpid,com);
		
		if(jn == jobnum)
		{
			// printf("MATCHED\n");
			return rpid;
		}
		else
		{
			curr = curr->next;
		}

	}
	return -1;
}


int delet(int pid)
{
	// printf("entered delete\n");
	struct Node* curr = head;
	struct Node* prev;

	if(curr != NULL && curr->pid == pid)
	{
		// write(2,"deletion complete\n",19);
		head = curr->next;
		free(curr);
		return 0;
	}

	while(curr != NULL && curr->pid != pid)
	{
		prev = curr;
		curr = curr->next;
	}

	if(curr == NULL) return -2;

	prev->next = curr->next;

	free(curr);
	// write(2,"deletion complete\n",19);
	return 0;
}