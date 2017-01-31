#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void spawn() {

	int i;
	int level = 1;
	int maxHeight = 3;
	int children = 3;

	for( i = 0 ; i < children ; i++ ) {
	
		//printf("PID is %d ... i is %d ... level is %d\n" , getpid() , i , level );
		int pid = fork();
		
		if( pid == 0 ) { /* Child Process. */
			level = level + 1;
			printf("Child is %d ... Parent is %d ... i is %d ... level is %d\n" , getpid() , getppid() , i , level );
			if( i == 1 && level == 2 ) {
				children = 2;
			} else {
				children = 3;
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
	


