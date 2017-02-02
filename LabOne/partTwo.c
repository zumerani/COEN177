#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void spawn() {

	printf("Main Process is: %d\n" , getpid() );

	int i;
	int pid;
	for( i = 0 ; i < 7 ; i++ ) {
		if( ( pid = fork() ) != 0 ) {
			wait(NULL);
			break; /* Enforces the parents not to go through the rest of the for loop. */
		} else {
			printf("Child is %d ... Parent is %d\n" , getpid() , getppid() );
		}
	}
}

int main() {
	spawn();
}
