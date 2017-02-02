#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void spawn() {

	int i;
	int level = 1;
	int maxHeight = 4;
	int children = 3;
	int doOnce = 0; /* Boolean variable that determines which side of the tree to print the two extra sets of children (3 each) on the left side of the tree. */

	for( i = 0 ; i < children ; i++ ) {
	
		int pid = fork();
		
		if( pid == 0 ) { /* Child Process. */
			level = level + 1;
			printf("Child is %d ... Parent is %d\n" , getpid() , getppid() );
			if( level == 2 && i == 0 ) { /* We want this side of the tree to have two sets of three children on the fourth level. */
				doOnce = 1; 
			}
			if( level == 3 && doOnce == 1 ) {
				children = 3;
			} else if( level == 3 && doOnce == 0 ) {
				children = 0; /* Spawn no children here because this would be level four and the boolean variable is not set. */
			} else if( level == 2 ) {
				children = 2;
			} 

			i = -1;
		} else {
			wait(NULL);
		}

		if( level >= maxHeight ) {
			exit(0);
		}

	}

}

int main() {
	spawn();
}

