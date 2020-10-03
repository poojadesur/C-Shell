#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include <unistd.h>
#include "functions.h"

void shellStart()
{
	
	printf("\n");

	for(int i=0;i<11;i++)
	{
		if(i%2==1) printf(" * ");
		else printf(" | ");
	}

	printf("\n");
	printf("\n");
	
	printf("\t   ");
	printf("*(^o^)*\n");

	printf("\n");

	
	for(int i=0;i<11;i++)
	{
		if(i%2==1) printf(" * ");
		else printf(" | ");
	}

	printf("\n");
	printf("\n");
	

}