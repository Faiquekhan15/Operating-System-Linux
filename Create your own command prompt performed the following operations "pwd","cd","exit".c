//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
//Muhammad Faique(16l-4196)//
//C-SHELL//

//----------------------------------------------------------------------------------//
//----------------------------------------------------------------------------------//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 1024

//----------------******Array for comparison*******---------------------------------//
//----------------------------------------------------------------------------------//
const char *mypath[] = {
	
        "pwd",
         "cd",
        "exit",
};

//----------------******-----------PWD-----------------*******----------------------//
//----------------------------------------------------------------------------------//

int myownpwd()
{
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir\n: %s", cwd);
    
    return 1;
}

//----------------******-----------CD-----------------*******----------------------//
//----------------------------------------------------------------------------------//


int myowncd(char **args)
{
        if (args[1] == NULL)
        { 
            printf("NOT Working");
         }
         else 
        { 
          chdir(args[1]);
         }
	return 1;
}
//----------------******-----------Exit-----------------*******----------------------//
//----------------------------------------------------------------------------------//


int myownexit()
{
    return 0;
}
//----------------******-----------Parsing-----------------*******----------------------//
//----------------------------------------------------------------------------------//



char **parse(char *command)
{
    int size = 64;
    int i = 0;
    char *arg1;
    char **arg2 = malloc(size * sizeof(char*));
    
    arg1 = strtok(command, " \t\r\n\a");
    while (arg1 != NULL) {
        arg2[i] = arg1;
        i++;
        arg1 = strtok(NULL, " \t\r\n\a");
    }
    
    arg2[i] = NULL;
    
    return arg2;
}
//----------******-----------Commands for shell---------*******---------------------//
//----------------------------------------------------------------------------------//




int implementedcommand(char** args, char** pipe) 
{
    int flag;
    char* _pipe[2]; 
    if (strcmp(args[0],mypath[0] ) == 0) {
        flag = myownpwd();
    }
	
    if (strcmp(args[0],mypath[1]) == 0) {
        flag = myowncd(args);
    }
    if (strcmp(args[0], mypath[2]) == 0) {
        flag = myownexit();
    }
    if(flag)
    {
       return 0;
    }
    else
    {
     int l; 
     for (l = 0; l < 2; l++) { 
        _pipe[l] = strsep(&args[0], "|"); 
        if (_pipe[l] == NULL) 
            break; 
     }
      if (_pipe[1] == NULL)
      {
        flag=0;
      } 
      else 
      { 
        flag=1; 
      }
         if (flag) 
         {
           args=parse(_pipe[0]);
	       pipe=parse(_pipe[1]);
         }
     }
   return 1 + flag;
 }
  
//----------------******-----------Check function-----------------*******----------//
//----------------------------------------------------------------------------------//


int checkInput(char* str) 
{ 
    if (strlen(str) != 0) 
    { 
        return 0; 
    } 
    else 
    { 
        return 1; 
    } 
} 

//----------------******-----------Input getter-----------------*******-------------//
//----------------------------------------------------------------------------------//



char *Inputfunction(void)
{
    char *my_buf = malloc(sizeof(char) * MAX);
    int c;
    int i = 0;
    
    while ( c != '\n' ) {
        c = getchar();
        my_buf[i] = c;
        i++;
    }
    
    return my_buf;
}

//---------------------******-----------If pipe-----------------*******-------------//
//----------------------------------------------------------------------------------//



void Pipedwiseexecution(char**Args, char**Piped)
{
    int fd[2];  
    int pid1, pid2; 
    pid1 = fork(); 
    if (pid1 < 0) 
    { 
        return; 
    }
    if (pid1 == 0) 
    { 
        close(fd[0]); 
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[1]); 
  
        if (execvp(Args[0], Args)) 
        { 
            exit(0); 
        } 
    } 
    else 
    {
        pid2 = fork(); 
        if (pid2 < 0) 
        { 
		    return; 
        }
        if (pid2 == 0) 
        { 
            close(fd[1]); 
            dup2(fd[0], STDIN_FILENO); 
            close(fd[0]); 
            if (execvp(Piped[0], Piped)) 
            { 
                exit(0); 
            } 
        } 
        else 
        { 
            	wait(NULL); 
            	wait(NULL); 
        }
	}
}

//----------------******-----------If not pipe-----------------*******-------------//
//----------------------------------------------------------------------------------//



void Myexecution(char** _command) 
{ 
    pid_t pid = fork();  
    if (pid == 0) 
     {
		 {
			execvp(_command[0], _command);
		  } 
        exit(0); 
    } 
    else 
    { 
        wait(NULL);  
        return; 
    } 
} 
int main(int argc, char **arg)
{ 
    char **Usercommand;
    char *buf;
    char* parsedPiped[100]; 
    int flag=1;
    while (flag)
	{
          printf("\n My shell>>>");
          buf=Inputfunction();
          if(checkInput(buf))
		  {
			printf("\nCommand not get\n");
		  }
		    Usercommand = parse(buf);                 
		    flag=implementedcommand(Usercommand,parsedPiped);
			if (flag == 1) 
            {
		       Myexecution(Usercommand);
		    }
			if (flag == 2)
            {
				Pipedwiseexecution(Usercommand, parsedPiped);
            }
 
	}
	return 0;
}
