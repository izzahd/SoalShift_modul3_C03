#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int numbers[100];
int k;

void* print_factorial(void* arg)
{
    	int answer = numbers[k];
    	int iter;

    	for(iter = 1; iter < numbers[k]; iter++)
    	{
 	   	answer = answer * iter;
    	}

    	printf("%d! = %d\n", numbers[k], answer);
}

int main(int argc, char* argv[])
{
    	int i, j, temp;
    	pthread_t thread[argc - 1];

    	for (i = 0; i < argc - 1; i++)
    	{
 	   	numbers[i] = atoi(argv[i + 1]);
    	}

    	for (i = 0; i < argc - 1; i++)
    	{
 	   	for (j = i + 1; j < argc - 1; j++)
 	   	{
 		   	if (numbers[i] > numbers[j])
 		   	{
 			   	temp = numbers[i];
 			  	numbers[i] = numbers[j];
 			   	numbers[j] = temp;
 		   	}
 	   	}
    	}

    	for (k = 0; k < argc - 1; k++)
    	{
 	   	pthread_create(&(thread[k]), NULL, print_factorial, &numbers[k]);
 	   	pthread_join(thread[k], NULL);
    	}

    	exit(0);
    	return EXIT_SUCCESS;
}
