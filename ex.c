

#include <stdio.h>

int main() {

int w,n,k=10;
int r = open("abc", O_WRONLY);
n = write(r, &k, sizeof(int));
printf("%d\n", n);

}
