#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

char *parameters[1];

void print_prompt() {
    printf("$S ");
}

void read_command( char* command ) {

    memset( command , '\0' , 255 );

    fgets( command , 255 , stdin );
    char* p = strchr(command , '\n');
    *p = '\0'; /* Turns it into a C string. */
    printf("Your command is: %s\n\n" , command);

}


int main() {
  
    while(1) {
        char command[255];
        print_prompt();
        read_command(command);

        if( strcmp(command , "exit" ) == 0 ) {
            printf("Goodbye.\n");
            exit(0);
        }

        if( fork() != 0 ) {
            wait(NULL); //waitpid(-1 , &status , 0);
        }else {
            char** array = {NULL};
            int returnValue = execv( command , array ); /* You can't check if execve succeeds because an entire new process runs with a new program. */
            if( returnValue < 0 ) {
                printf("There was a problem with the commmand.\n");
                exit(returnValue);
            } else {
                printf("There was NO problem with the command.\n");
            }
            exit(0); /* Terminate it because if you don't, then the child will start a new program and if that errors, then another child will be created ... etc. */
        }
        
    }
    

}
