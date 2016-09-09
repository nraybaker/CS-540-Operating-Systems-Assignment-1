/* Author: Nathan Baker
   myWSU ID: A767P375
   Assignment: #1
   Due: Wednesday, September 14, 2016
   
   Description:
     This program invokes a child process
   to run an integer supplied via the command
   line through the Collatz algorithm printing
   each number in the sequence.

*/

/* pre-processing */
#include <stdio.h>     /* for printing the sequence */
#include <unistd.h>    /* brings in the fork() command */
#include <sys/wait.h>  /* for wait */
#include <stdlib.h>    /* for the atoi library call */

/* main */
int main(int argc, char** argv){
	/* check if correct number of arguments supplied */
	if(argc != 2){
		fprintf(stderr, "Usage: %s <integer value>\n", argv[0]);
	}
	
	/* store supplied integer in variable n, the starting
	   point of the Collatz algorithm */
	int n = atoi(argv[1]);
	
	/* if n < 1 or > 500000 we treat it as out of bounds */
	if((n < 1) || (n > 500000)){
		fprintf(stderr, "Integer %d entered is out of bounds.\n", n);
	}
	
	/* fork a child process*/
	pid_t pid;
	pid = fork();
	
	/* if the process id (pid) < 0 the fork failed */
	if(pid < 0){
		fprintf(stderr, "Fork Failed");
		return(1);
	}
	/* else if pid == 0 run child process */
	else if(pid == 0){
		printf("%d", n);
		printf(", ");
		
		/* output counter counts the number of numbers
			in the sequence so that the output line is never
			more than 10 numbers long */
		int output_counter = 0;
		
		/* while loop to run the algorithm */
		while(n != 1){
			if(n % 2 == 0){
				n /= 2;
			}
			else{
				n = 3*n + 1;
			}

			/* print formatting */			
			printf("%d", n);
			if(n != 1){
				printf(", ");			
			}
			else{
				printf(" ");
			}
			
			/* if line longer than 10 go to next line */
			output_counter++;
			if(output_counter >= 10){
				printf("\n");
				output_counter = 0;
			}
		}
	}
	else{
		/* parent process waits for child process to complete */
		wait(NULL);
		printf("\nChild Complete\n");
	}
	
	return(0);
}



