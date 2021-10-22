#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int pipes[argc][2];
	int i;
	for(i=1;i<argc;i++) {
		pipe(pipes[i]);
		int child = fork();
		if(child < 0) {
			int j;
			for(j=1;j<=i;j++) { close(pipes[j][0]); close(pipes[j][1]); }
			perror("Error on fork!");
			exit(1);
		}
		else if(child == 0) {
			close(pipes[i][0]);
			dup2(pipes[i][1], 1);
			close(pipes[i][1]);
			execlp("./remove_vowels", "./remove_vowels", argv[i], NULL);
			close(pipes[i][1]);
			exit(1);
		}
		else close(pipes[i][1]);
	}
	for(i=1;i<argc;i++) wait(0);
	for(i=1;i<argc;i++) {
		int child = fork();
		if(child < 0) {
			int j;
			for(j=i;j<argc;j++) close(pipes[j][0]);
			perror("Error on fork!");
			exit(1);
		}
		else if(child == 0) {
			char str[100];
			read(pipes[i][0], str, strlen(argv[i])+1);
			close(pipes[i][0]);
			execlp("./compute_length", "./compute_length", str, NULL);
			exit(1);
		}
		else close(pipes[i][0]);
	}
	for(i=1;i<argc;i++) wait(0);
	
	return 0;
}
