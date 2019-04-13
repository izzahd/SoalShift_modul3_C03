#include <sys/shm.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int *value;

void* menu(){
    	while(1){
        	printf("Shop\n\nFood stock : %d\n\nChoices\n1. Restock\n2. Back\n", *value);
        	sleep(1);
        	system("clear");
    	}
}

char getch() {
    	char buf = 0;
    	struct termios old = {0};
    	if (tcgetattr(0, &old) < 0)
            	perror("tcsetattr()");
    	old.c_lflag &= ~ICANON;
    	old.c_lflag &= ~ECHO;
    	old.c_cc[VMIN] = 1;
    	old.c_cc[VTIME] = 0;
    	if (tcsetattr(0, TCSANOW, &old) < 0)
            	perror("tcsetattr ICANON");
    	if (read(0, &buf, 1) < 0)
            	perror ("read()");
    	old.c_lflag |= ICANON;
    	old.c_lflag |= ECHO;
    	if (tcsetattr(0, TCSADRAIN, &old) < 0)
            	perror ("tcsetattr ~ICANON");
    	return (buf);
}

int main(){
    	pthread_t thread;
    	char ch;
    	key_t key = 1234;

    	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    	value = shmat(shmid, NULL, 0);

    	pthread_create(&thread, NULL, menu, NULL);

    	while(1){
        	ch = getch();
        	switch(ch)
        	{
            		case '1':
                	*value += 1;
                	break;

            		case '2':
                	system("clear");
                	exit(0);
                	break;
        	}
    	}
    	return 0;
}
