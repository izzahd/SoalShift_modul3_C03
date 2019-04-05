#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1, tid2, tid3;
int wakeup_status=0;
int spirit_status=100;
int flag=0;
int counteragmal = 0;
int counteriraj = 0;
int tidur1=0, tidur2=0;

void* agmal(void *arg)
{
   while(1){
    if(wakeup_status >= 100){
        printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
        exit(0);
        }

    else if(flag == 1){
    flag=0;
    if(counteriraj ==3){
    counteriraj=0;
    tidur1=1;
    flag=0;
    sleep(10);
    tidur1=0;
    continue;
    }

    else{
    printf("Agmal\n");
    wakeup_status+=15;
    counteragmal+=1;
    if(counteragmal == 3){
    flag = 2;
    printf("Iraj Disabled\n");
          }
       }
     }

    }
}

void* iraj(void *arg)
{
   while(1){
   if(spirit_status <= 0){
        printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
        exit(0);
      }

   else if(flag==2){
    flag=0;
    if(counteragmal == 3){
    counteragmal=0;
    tidur2=1;
    flag=0;
    sleep(10);
    tidur2=0;
    continue;
    }

   else {
   printf("Iraj\n");
   spirit_status-=20;
   counteriraj+=1;
      if(counteriraj == 3){
     flag = 1;
      printf("Agmal Disabled\n");
                          }
         }
       }
     }
   }


void* ustatus(void *arg)
{
    while(1){
    if(flag==3){
    flag=0;
    printf("Agmal memiliki WakeUp_Status = %d\n", wakeup_status);
    printf("Iran memiliki Spirit_Status = %d\n", spirit_status);


       }
    }
}


int main(void)
{

    pthread_create(&(tid1), NULL, agmal, NULL);
    pthread_create(&(tid2), NULL, iraj, NULL);
    pthread_create(&(tid3), NULL, ustatus, NULL);
    printf("1. Agmal Ayo Bangun\n");
    printf("2. Iraj Ayo Tidur\n");
    printf("3. View Status\n");
    while(1){
    while(flag!=0) {}
    int inp;
    scanf("%d", &inp);
    if(inp == 1 || inp == 2 || inp == 3){
       if(tidur1==0)
          flag=inp;
       else if(tidur2==0)
          flag=inp;
     }

   }

    return 0;
}
