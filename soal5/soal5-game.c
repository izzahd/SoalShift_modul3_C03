#include <sys/shm.h>
#include <termios.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char name[30];
int *value, health, hunger, hygiene, mode, enemy, food, cd;

void* background(){
    	while(1){
        	if(mode == 0){
            		sleep(10);
            		health+=5;
            		hunger-=5;
            		sleep(10);
            		health+=5;
            		hunger-=5;
            		sleep(10);
            		health+=5;
            		hunger-=5;
            		hygiene-=10;

        	}
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

void keluar() {
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
}

void* menu(){
    	while(hunger > 0 && hygiene > 0  && health > 0){
        	if(mode == 0){
            		printf("Standby Mode\n\nHealth : %d\nHunger : %d\nHygiene : %d\nFood left : %d\n", health, hunger, hygiene, food);
            		if(cd <= 0){
                		puts("Bath is ready");
           		}else{
                		printf("Bath will be ready in %ds\n", cd);
            		}
            		printf("\nChoices\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n");
        	}
        	if(mode == 1){
            		printf("Battle Mode\n\n%s’s Health : %d\nEnemy’s Health : %d\n\nChoices\n1. Attack\n2. Run\n", name, health, enemy);
        	}
        	if(mode == 2){
            		printf("Shop Mode\n\nShop food stock : %d\nYour food stock : %d\n\nChoices\n1. Buy\n2. Back\n", *value, food);
        	}
        	cd--;
        	sleep(1);
        	system("clear");
    	}
	printf("%s died :(\n", name);
    	sleep(3);
    	system("clear");
    	keluar();
    	exit(0);
}

int main(){
    	health = 300;
    	hunger = 200;
    	hygiene = 100;
    	mode = 0;
    	enemy = 100;
    	food = 0;
    	cd = 0;
    	pthread_t thread;
    	char ch;
    	key_t key = 1234;

    	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    	value = shmat(shmid, NULL, 0);

    	printf("Insert your monster name : ");
    	scanf("%s", name);
    
    	pthread_create(&thread, NULL, menu, NULL);
    	pthread_create(&thread, NULL, background, NULL);

    	while(1){
        	if(hunger>200) hunger = 200;
        	ch = getch();

        	switch(mode)
        	{
            		case 0:
                	switch(ch)
                	{
                    		case '1':
                        	if(food > 0){
                            		hunger += 15;
                            		food--;
                        	}else{
                            		printf("Please buy food in the shop.\n");
                        	}
                        	break;

                    		case '2':
                        	if(cd <= 0){
                            		cd = 20;
                            		hygiene += 30;
                        	}else{
                            		printf("Bath will be ready in %ds\n", cd);
                        	}
                        	break;

                    		case '3':
                        	mode = 1;
                        	break;

                    		case '4':
                        	mode = 2;
                        	break;

                    		case '5':
                        	system("clear");
                        	exit(0);
                        	break;
                	}
                	break;

            		case 1:
                	switch(ch)
                	{
                    		case '1':
                        	health -= 20;
                        	enemy -= 20;
                        	if(enemy <= 0){
                            		printf("%s win!\n", name);
                            		sleep(0.7);
                            		mode = 0;
                            		enemy = 100;
                        	}
                        	break;

                    		case '2':
                        	mode = 0;
                        	break;
                	}
                	break;

            		case 2:
                	switch(ch)
                	{
                    		case '1':
                        	if(*value > 0){
                            		*value -= 1;
                            		food++;
                        	}else{
                            		puts("Food is out of stock.");
                        	}
                        	break;

                    		case '2':
                        	mode = 0;
                        	break;
                	}
                	break;
        	}
    	}
}
