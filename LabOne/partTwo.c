#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

/* Globals */
static int childCounter = 0;
static int x = 1;
static int doOnce = 0;

void test( int number ) {

	int i;
	for( i = 0 ; i < 7 ; i++ ) {
		//printf("PID is %d\n" , getpid() );
		int pid;
		if( ( pid = fork() ) != 0 ) {
			//printf("i is %d ... PID is %d\n" , i , getpid() );
			//printf("I am about to wait.\n");
			wait(NULL);
			//printf("Hey I'm back ... childCounter is %d\n" , childCounter);
			break;
		} else {
			//printf("i is %d ... PID is %d\n" , i , getpid() );
			printf("Child is %d ... Parent is %d ... i is %d\n" , getpid() , getppid() , i );
			childCounter++;

			//printf("childCounter is %d\n" , childCounter);
		}
	}
}

int main() {
	test(0);
}
