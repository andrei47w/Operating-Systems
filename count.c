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

int main(int argc, char **argv){	
	int nr;
	int fa2b = open("fifoa2b", O_RDONLY);
	read(fa2b, &nr, sizeof(int));
	printf("%d \n", nr);
	close(fa2b);		
	exit(0);
	

}
