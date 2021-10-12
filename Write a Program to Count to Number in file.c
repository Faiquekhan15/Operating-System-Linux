#include<stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])  {
	char ch;
	int count=0;
	FILE *fptr;
	fptr=fopen(argv[1],"r");
	if(fptr==NULL) 
        {
		printf("Unable to open file\a");

	}
          ch = fgetc(fptr);
    	while (ch != EOF)
    	{
        if(ch>=48&&ch<=57)
	{
	   count++;
	}
        ch = fgetc(fptr);
    	}
	fclose(fptr);
	printf("\nNumber count is: %d",count);
	return 0;
}
