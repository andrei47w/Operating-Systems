#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait>

int main(int args, char *argv[]) {
	int n, v[100], Max, Min;
	double avg;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d", &v[i]);
	int p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);

	//CHILD 1
	
	int pid = fork();
	if(pid == 0) {
		close(p2c[1]);
		read(p2c[0], v, n*sizeof(int));
		close(p2c[0]);
		Max = -99999999;
		for(int i=0;i<n;i++)
			if(v[i]>Max) Max = v[i];
		close(c2p[0]);
		write(c2p[1], &Max, sizeof(int));
		close(c2p[1]);
		exit(0);
	}
}

