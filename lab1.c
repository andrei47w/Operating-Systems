#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>  
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
 *  * Write 2 C programs: A & B, that communicate via FIFO.
 *   * Program A reads a number N from keyboard, then reads N integers and stores them in an array.
 *    * Once all the integers are read and stored in the array, program A sends them to program B, which:
 *     *   -> counts all the numbers that end in 5.
 *      *   -> sends this nunmber to A
 *       *   -> A prints it
 *        * Both programs perform all the necessary checks. The necessary FIFO(s) can be created from either one of the
 *         * programs or by using bash commands.
 *          */

int main(int argc, char **argv) {
	mkfifo("fifoa2b", 0666);
	int fa2b;
	int fa = fork();
	int len = 0;

	if(fa<0) {printf("Error!"); exit(1);}
	if(fa == 0) {
		scanf("%d", &len);
		int arr[len];
		for(int i=0;i<len;i++) scanf("%d", arr[i]);
		fa2b = open("fifoa2b", O_WRONLY);
		for(int i=0;i<len;i++) {
			write(fa2b, &arr[i], sizeof(int));
			close(fa2b);
			execlp("./count", "./count", NULL, NULL);
			exit(0);
		}
	}

	for(int i=0;i<len;i++) wait(0);
}
