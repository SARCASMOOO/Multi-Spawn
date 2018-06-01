#include "singlePrime.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int isFile(char* filename)
{
	 FILE* fp = fopen(filename, "r");
	 if(fp == NULL)
		 return 0;
	 fclose(fp);
	 return 1;
}

char* getFirstIntFromFIle(char *filename, char *buffer)
{
	FILE * fp;
	ssize_t read;
	unsigned int r = 0;
					 
	fp = fopen("prime.bin", "rb");
	if (fp == NULL)
		return -1;
 
	while(fread(&r, sizeof(unsigned int), 1, fp) == 1)
	{
		sprintf(buffer, "%u", r);
		break;
	}

	fclose(fp);
	return buffer;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("Usage: ./singlePrime filename.\n");
		return 0;
	}
	else if(isFile(argv[1]) == 0)
	{
		printf("File %s does not exist.\n", argv[1]);
		return 0;
	}
	else
	{
		char buffer [sizeof(unsigned int)+1];
		morph(getFirstIntFromFIle(argv[1], buffer));
	}
	return 1;
}

int morph(char *number)
{
	int rc = fork();                                                                              
	if(rc < 0)                                                                                    
	{                                                                                             
		fprintf(stderr, "fork failed\n"); 
		return -1;                                                                              
	}                                                                                             
	else if(rc == 0) //child (new process)                                                        
	{                                                                                             
		char *args[] = {"./isPrime", number, NULL};
		//Check if morph failed
		if(execv(args[0], args) == -1)
			return -1;
	}                                                                                             
	else                                                                                        
	{                                                                                             
		int status = -1;
		wait(&status);
		if(status != 0)
		{
	             printf("This is a prime number");
	        }
		else
		{
	              printf("This is not a prime number");
		}

	}                                                                                             
	return 1;	
}
