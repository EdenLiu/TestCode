#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int index = 0;

int io1(size_t bufsize)
{
	
}

int main(int arg, char** argc){
	printf("CLOCKS_PER_SEC = %u\n", CLOCKS_PER_SEC);
	io1(1);
	io1(2);
	io1(512);
	//clock_t tt;
	//clock_t tt1;
	//tt = clock();
	//tt = time(NULL);
	//printf("tt=%u\n", tt);
	//sleep(2);
	//tt1 = clock();
	//tt1 = time(NULL);
	//printf("test tt1=%u time=%u \n",tt1, tt1-tt);
	return 0;
}
