#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1, tid2, tid3;
int status1=0;
int status2=0;
int status3=0;

void* tulis(void *arg)
{

    	system("ps -aux | head -10 > ~/Documents/FolderProses1/SimpanProses1.txt");
    	system("ps -aux | tail -10 > ~/Documents/FolderProses2/SimpanProses2.txt");

    	status1= 1;
}

void* paketin(void *arg)
{
    	while(status1 != 1)
    	{
    	}

    	system("zip -m -j ~/Documents/FolderProses1/KompresProses1.zip ~/Documents/FolderProses1/SimpanProses1.txt");
    	system("zip -m -j ~/Documents/FolderProses2/KompresProses2.zip ~/Documents/FolderProses2/SimpanProses2.txt");
    	printf("Menunggu 15 Detik Untuk Meng-ekstrak Kembali\n");
    	sleep(15);
    	status2=1;
}

void* ekstrak(void *arg)
{
    	while(status2 != 1)
    	{
    	}
    	system("unzip ~/Documents/FolderProses1/KompresProses1.zip -d ~/Documents/FolderProses1/");
    	system("unzip ~/Documents/FolderProses2/KompresProses2.zip -d ~/Documents/FolderProses2/");
}

int main(void)
{

    	pthread_create(&(tid1), NULL, tulis, NULL);
    	pthread_create(&(tid2), NULL, paketin, NULL);
    	pthread_create(&(tid3), NULL, ekstrak, NULL);

    	pthread_join(tid1, NULL);
    	pthread_join(tid2, NULL);
    	pthread_join(tid3, NULL);
    	return 0;
}
