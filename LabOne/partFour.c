#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void spawn() {

	int i;
	int level = 1;
	int maxHeight = 4;
	int children = 3;
	int doOnce = 0;

	for( i = 0 ; i < children ; i++ ) {
	
		//printf("PID is %d ... i is %d ... level is %d\n" , getpid() , i , level );
		int pid = fork();
		
		if( pid == 0 ) { /* Child Process. */
			level = level + 1;
			printf("Child is %d ... Parent is %d ... i is %d ... level is %d ... doOnce is %d\n" , getpid() , getppid() , i , level , doOnce );
			if( level == 2 && i == 0 ) {
				doOnce = 1;
			}
			if( level == 3 && doOnce == 1 ) {
				children = 3;
			} else if( level ==3 && doOnce == 0 ) {
				children = 0;
			} else if( level == 2 ) {
				children = 2;
			} 

			i = -1;

		} else {
			wait(NULL);
			//printf("We are the parent.\n");
		}

		if( level >= maxHeight ) {
			//printf("I am about to break.\n");
				exit(0);
		}

	}

}

int main() {
	spawn();
}

