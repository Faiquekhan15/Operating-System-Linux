#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>

const char *mypath[] = {
	"pwd",
	"cd",
        "exit",
};

int path_size = sizeof(mypath) / sizeof(char *);

int my_pwd()
{
    char cwd[1024];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL){
        fprintf(stdout, "%s\n", cwd);
    }
    else {
        printf("getcwd() error!\n");
    }
    
    return 1;
}

int my_cd(char **args)
{
	if(args[1]!=NULL)
	{
		chdir( args[1] );
	}
	else 
	{
        printf("error!\n");
    }
	return 1;
}

int my_exit()
{
    return 0;
}


int execute_built_in_command(char **args)
{
    int flag;
    if (strcmp(args[0],mypath[0] ) == 0) {
        flag = my_pwd();
    }
	
    if (strcmp(args[0],mypath[1]) == 0) {
        flag = my_cd(args);
    }
    
    
    if (strcmp(args[0], mypath[2]) == 0) {
        flag = my_exit();
    }
	return flag;
}


int main(int argc, char **arg)
{ 
    int pipe[2];
    char **my_command;
    int bufsize = 1024;
    pid_t p1, p2; 
    int count = 0;
    char buffer[1024] ;
    int t=0;
    char*file;
	char *found;
	while (1)
	{
		printf ("prompt> ");
    int c;
    int j = 0;
    
    while ( j != '\n' ) {
        c = getchar();
        buffer[j] = c;
        j++;
    }



    int i = 0;
    char *arg1;
    char **args ;//= malloc(buffer_size * sizeof(char*));
        

    arg1 = strtok(buffer, " \t\r\n\a");
    while (arg1 != NULL) {
        args[i] = arg1;
        i++;
        arg1 = strtok(NULL, " \t\r\n\a");
    }
    
    args[i] = NULL;
    my_command=args;
    
    
		//if ( my_command[0] == NULL ) 
		//{
		//	t=0;
		//}
		//or (i=0; i < path_size; i++) 
		//{
		//	if (strcmp(my_command[0], mypath[i]) == 0) 
		//	{
		//		t=1;
		//	}
		//}
                if ( my_command[0] != NULL ) 
		{
		
		while( (found = strsep(&my_command[0]," ")) != NULL )
		{
        		printf("%s\n",found);
		}
		}
		flag = execute_built_in_command(args[0]);
	        p1=fork(); 
		if (p1 == 0) 
		{
			close(pipefd[0]); 
        		dup2(pipefd[1], STDOUT_FILENO); 
        		close(pipefd[1]); 
               	   if (execvp([my_command[0], my_command) < 0) { 
            		printf("\nCould not execute command 1.."); 
            		exit(0);
			}
                } 
                   else  
		{ 
     			p2=fork(); 
        		
			if (p2 < 0) 
			{ 
            			printf("\nCould not fork"); 
            			return; 
        		}	 
                         if(p2==0)
			{
  				close(pipefd[1]); 
            			dup2(pipefd[0], STDIN_FILENO); 
            			close(pipefd[0]); 
			}			
			 if (execvp(my_command[0], my_command) < 0) 
			{ 
                	printf("\nCould not execute command2.."); 
		                exit(0); 
            		} 
    		       
		}
		else
		{
 			wait(NULL); 
            		wait(NULL); 
		}
	}
	return 0;
}