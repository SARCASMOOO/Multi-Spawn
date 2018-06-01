#include <errno.h>
#include<signal.h>
#include <unistd.h>
#include "multiSpawnSignal.h"
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

//Bonus signal handler variable
int countFinished = 0;

int isFile(char* filename)
{
	 FILE* fp = fopen(filename, "r");
	 if(fp == NULL)
		 return 0;
	 fclose(fp);
	 return 1;
}

void sig_handler(int signo)                                  
{                                                            
	if (signo == SIGUSR1)                              
		printf("Count is: %d\n", countFinished);     
}                                                            

int getFirstIntFromFIle(char *filename, char userInput[][11])
{
	
	FILE * fp;
	ssize_t read;
	unsigned int r = 0;
				 
	fp = fopen(filename, "rb");
	if (fp == NULL)
		exit(0);
 
	char buffer [11];

	for(int i = 0; i < 10; i++)
	{
		fread(&r, sizeof(unsigned int), 1, fp);
		sprintf(buffer, "%u", r);
		strcpy(userInput[i], buffer); 
	}

	fclose(fp);
	//exit(0);
	//return userInput;
	return 1;
}

int main(int argc, char *argv[])
{
	if (signal(SIGUSR1, sig_handler) == SIG_ERR)  
		printf("\ncan't catch SIGUSR1\n");    

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
		//Make buffer then pass to getFirstIntFromFile to populate
		char userInput[10][11];
		//long int userInput[10];
		getFirstIntFromFIle(argv[1], userInput);
		morph(userInput);
	}
	return 1;
}

void loadBinary(char* args[])
{
	execvp("./isPrime", args);
	printf("ERROR: execvp failed\n");
}


int makeNewIsPrime(char *number, int id)
{
	int returnCode = fork();
	char *args[] = {"./isPrime", number, NULL};
	
	if(returnCode == 0)
	{
		loadBinary(args);
		exit(-1);
	}
	else if(returnCode < 0)                                                                                    
	{                                                                                             
		fprintf(stderr, "fork failed\n"); 
	}      
	else
	{
		//i am the parent
		return returnCode;
	}
}

void putInOrder(int pidList[], int response, int status, int recordStatus[])
{
	int index = -1;
	for(int i = 0; i < 10; i++)
	{
		if(pidList[i] == response)
		{
			index = i;
			break;
		}
	}

	if(index == -1)
	{
		printf("Something went wrong bad index\n");
	}

	recordStatus[index] = status;
}

int morph(char number[][11])
{
	int status = -1;
	int processIDList[10];
	int response = 0;
	int recordStatus[10];

	//1 for yes 0 for no, then number 
	for(int i = 0; i < 10; i++)
	{
		processIDList[i] = makeNewIsPrime(number[i], i);
	}
	for(int i = 0; i < 10; i++)
	{
		response = waitpid(-1, &status, 0);
		if(response == -1)
			return -1;
		if(WIFEXITED(status))
		{
			putInOrder(processIDList, response, WEXITSTATUS(status), recordStatus);
			countFinished += 1;
		}
		else
		{
			printf("Child process failed\n");
		}
		status = 0;
	}
	printNumbers(number, recordStatus);
	return 1;	
}

void printNumbers(char number[][11], int recordStatus[10])
{
	int i;
	for(i=0; i < 10; i++)
	{
		if(recordStatus[i] == 0)
		{
			printf("Number: %s, is not a prime number\n", number[i]);
		}
		else
		{
			printf("Number: %s, is a prime number\n", number[i]);
		}
	}
}
