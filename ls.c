
#include "functions.h"


int isDir(char *file_name)
{
	struct stat st;
	if(stat(file_name,&st) < 0)
	{
		return -1;
	}
	if(S_ISDIR(st.st_mode)) 
	{
			// printf("yes it is dir %s\n",file_name);
			return 1;
	}
	else return 0;

}

int isFile(char *file)
{
	struct stat st;
	if(stat(file,&st) < 0)
	{
		return -1;
	}
	if(S_ISREG(st.st_mode)) 
	{
			// printf("yes it is dir %s\n",file_name);
			return 1;
	}
	else return 0;
}


void longFormat(char *file)
{
	struct stat st;
	if(stat(file,&st) < 0)
	{
		// perror("Program longf");
		return;
	} 

	char *temp = (char *)calloc(1024,sizeof(char));
	for(int i=0;i<1024;i++) temp[i] = '\0';
	getcwd(temp,1024);
	// printf("cwd is %s\n",temp);

	char *op = (char *)calloc(1024,sizeof(char));
	for(int i=0;i<1024;i++) op[i] = '\0';

	//permissions
	if(S_ISDIR(st.st_mode)) op[0] = 'd';
	else op[0] = '-';

	if(st.st_mode & S_IRUSR) op[1] = 'r';
	else op[1] = '-';
	if(st.st_mode & S_IWUSR) op[2] = 'w';
	else op[2] = '-';
	if(st.st_mode & S_IXUSR) op[3] = 'x';
	else op[3] = '-';
	if(st.st_mode & S_IRUSR) op[4] = 'r';
	else op[4] = '-';
	if(st.st_mode & S_IRUSR) op[5] = 'w';
	else op[5] = '-';
	if(st.st_mode & S_IRUSR) op[6] = 'x';
	else op[6] = '-';
	if(st.st_mode & S_IRUSR) op[7] = 'r';
	else op[7] = '-';
	if(st.st_mode & S_IRUSR) op[8] = 'w';
	else op[8] = '-';
	if(st.st_mode & S_IRUSR) op[9] = 'x';
	else op[9] = '-';

	//hardlinks
	sprintf(op,"%s %ld ",op,st.st_nlink);

	//user and group
	struct passwd *pw = getpwuid(st.st_uid);
	struct group *gr = getgrgid(st.st_gid);
	sprintf(op,"%s %s %s ",op,pw->pw_name,gr->gr_name);

	//size
	sprintf(op,"%s %ld ",op,st.st_size);

	//modification date
	char *t = (char *)calloc(1024,sizeof(char));
	strftime(t,1024,"%b %d %H:%M ",localtime(&st.st_mtime));
	sprintf(op,"%s %s ",op,t);

	//file name
	sprintf(op,"%s %s",op,file);

	printf("%s\n",op);

	free(op);
	free(temp);
	
}


void ExecuteLs(char *var, int l, int a, int al)
{
	char *var2 =  (char*)malloc(1024*sizeof(char));
	for(int i=0;i<1024;i++) var2[i] = '\0';

	int j=0;
	for(int i=3;i<strlen(var)-1;i++)
	{
		var2[j] = var[i]; j++;
	}

	// printf("var2 is %s\n",var2);
	char *sptr;

	for(int i=0; ; i++)
	{
		char *token = (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) token[i] = '\0';

		token = strtok_r(var2," \t",&sptr);
		// printf("token is %s\n",token);

		var2 = NULL;

		if(token == NULL) break;

		//modify for ~
		char *str =  (char*)malloc(1024*sizeof(char));
		for(int i=0;i<1024;i++) str[i] = '\0';

		int tilda = 0;
		
		if (token[0] == '~')
		{
			tilda = 1;
			char *var3 =  (char*)malloc(1024*sizeof(char));
			for(int i=0;i<1024;i++) var3[i] = '\0';
			
			int j=0;
			for(int i=1;i<strlen(token);i++)
			{
				var3[j] = token[i]; j++;
			}

			sprintf(str,"%s%s",root_dir,var3);

			free(var3);
		}
		else
			str = token;

		// printf("str is %s\n",str);

		//if ls for a file
		if(isFile(str) == 1)
		{
			// lsiprintf("%s:\n",str);
			if(l == 1 || al == 1)
				longFormat(str);
			else
				printf("%s\n",str);
		}

		//reading a directory
		//FORMAT FOR MORE THAN ONE DIRECTORY
		if(isDir(str) == 1) 
		{
			int parent = 0;
			printf("%s:\n",str);
			struct dirent *de;  // Pointer for directory entry 
			
			if(strcmp(str,"..") == 0) parent = 1;
			if(strcmp(str,"~") == 0) tilda = 1;
			  
			// opendir() returns a pointer of DIR type.  
			DIR *dr = opendir(str); 
			  
			if (dr == NULL)  // opendir returns NULL if couldn't open directory 
			{
				perror("Program null");
				forn(i) smiley[i] = '\0';
		        strcat(smiley,":'(");
			}

			// printf("value of tilda %d\n",tilda);
			    
			if(al == 1 || ((l==1) && (a==1)))
			{
				char *temp = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) temp[i] = '\0';
				getcwd(temp,1024);
				int err = 0;

				if (parent == 1) err = chdir("..");
				if (tilda == 1) err = chdir(root_dir); 
				
				if(err != 0)
				{
					 perror("Program");
					 forn(i) smiley[i] = '\0';
		            strcat(smiley,":'(");
				}
				
				while ((de = readdir(dr)) != NULL) 
				{
			    	longFormat(de->d_name); 
				}

				if(parent == 1 || tilda == 1) 
				{
					err = chdir(temp);
				
					if(err != 0)
					{
						 perror("Program");
						 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
					}
				}

				fflush(NULL);
				
				closedir(dr);  
				free(temp);
				continue;
			}   

			else if(l == 1)
			{
				char *temp = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) temp[i] = '\0';
				getcwd(temp,1024);
				int err = 0;

				if (parent == 1) err = chdir("..");
				if (tilda == 1) err = chdir(root_dir); 
				
				if(err != 0)
				{
					 perror("Program");
					 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
				}

				while (( de = readdir(dr)) != NULL)
				{
			   		if (de->d_name[0] != '.')
			   		{
			    		longFormat(de->d_name); 
				    	
			   		}
				}

				if(parent == 1 || tilda == 1) 
				{
					err = chdir(temp);
				
					if(err != 0)
					{
						 perror("Program");
						 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
					}
				}

				fflush(NULL);

				closedir(dr);
				free(temp);
				continue;
			}

			else if(a == 1)   //doesnt work
			{
				char *temp = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) temp[i] = '\0';
				getcwd(temp,1024);
				int err = 0;

				if (parent == 1) err = chdir("..");
				if (tilda == 1) err = chdir(root_dir); 
				
				if(err != 0)
				{
					 perror("Program");
					 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
				}
			
				while ((de = readdir(dr)) != NULL) 
			   		printf("%s\n", de->d_name); 

			   	if(parent == 1 || tilda == 1) 
				{
					err = chdir(temp);
				
					if(err != 0)
					{
						perror("Program");
						forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
					}
				}

				fflush(NULL);
			  	
			  	free(temp);
				closedir(dr);  
				continue;
			}

			else
			{
				char *temp = (char*)malloc(1024*sizeof(char));
				for(int i=0;i<1024;i++) temp[i] = '\0';
				getcwd(temp,1024);
				int err = 0;

				if (parent == 1) err = chdir("..");
				if (tilda == 1) err = chdir(root_dir); 
				
				if(err != 0)
				{
					 perror("Program");
					 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
				}
				
				while (de = readdir(dr))
				{
			   		if (de->d_name[0] != '.')
			        	printf("%s\n",de->d_name);
				}

				fflush(NULL);

				if(parent == 1 || tilda == 1) 
				{
					err = chdir(temp);
				
					if(err != 0)
					{
						 perror("Program");
						 forn(i) smiley[i] = '\0';
		            	strcat(smiley,":'(");
					}
				}

				free(temp);
				closedir(dr);

			}
			
		}

	}

	free(var2);
}

