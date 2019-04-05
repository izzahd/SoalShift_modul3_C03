#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>

long int fact[50], number[50], t;
int x, y, i, j, a;

void *Fact(void *temp)
{

    a = 1;
    number[0] = 0;
    while(scanf("%d", &x) != EOF)
    {
	if (x==0) break;

	number[a] = x;
	a++;
    }

    long int f;
    long int b ;

    fact[0] = 0;

    int c = a - 1;
    for(c; c>0; c--)
    {
	b = number[c];
    	for(f = 1; number[c] > f; f++)
	{
	   b = f * b;
	}
    	fact[c] = b;
    }
    return fact;
}

void*Sortfact(void *temp)
{
        for (i = 1; i < sizeof(fact); i++) 
        {
            for (j = i + 1; j < sizeof(fact); j++)
            {
                if (fact[i] > fact[j]) 
                {
                    t =  fact[i];
                    fact[i] = fact[j];
                    fact[j] = t;
                }
            }
        }

	return fact;
}

void *Sortnumb(void *temp)
{
        for (i = 1; i < sizeof(number); i++) 
        {

            for (j = i + 1; j < sizeof(number); j++)
            {
                if (number[i] > number[j]) 
                {
                    t =  number[i];
                    number[i] = number[j];
                    number[j] = t;

                }
            }
        }

	return number;
}

int main(void)
{
    pthread_t thread1,thread2,thread3;
    //printf("\nThreads creating.....\n");
    pthread_create(&thread1, NULL, Fact, NULL);
    pthread_create(&thread2, NULL, Sortfact, NULL);
    pthread_create(&thread3, NULL, Sortnumb, NULL);
   // printf("Threads created\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    for (y = 1; y < a; y++)
    {
    	printf("%ld! = %ld\n", number[y], fact[y]);
    }
    exit(1);
}
