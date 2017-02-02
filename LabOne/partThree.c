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
	
		int pid = fork();
		
		if( pid == 0 ) { /* Child Process. */
			level = level + 1;
			printf("Child is %d ... Parent is %d\n" , getpid() , getppid() );
			if( i == 1 && level == 2 ) {
				children = 2;
			} else {
				children = 3;
			}

			i = -1; /* Change 'i' to -1 so that each child about to be forked in the iteration will 'children'. */

		} else {
			wait(NULL); /*If parent, have it wait so it doesn't get killed - prevents parent id from becoming '1'. */
		}

		if( level >= maxHeight ) {
			exit(0); /* Once at the third level, do not create any more children. */
		}

	}

}

int main() {
	spawn();
}
	


