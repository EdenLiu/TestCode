#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

static int index = 0;

int io1(size_t bufsize)
{
	//printf("bufsize = %d\n", bufsize);
	int n;
	int pipeH[2];
	char* buf = new char[bufsize];

	pipe(pipeH);
	pid_t pid = fork();
	if (pid == 0){
		char cmd[128];
		printf("child start %d\n", ++index);
		sprintf(cmd, "./copysource_%d.txt", bufsize);
		FILE* fdw = fopen(cmd, "w");
		if (fdw == NULL ){
			printf("open copysource failed\n");
			return -1;
		}
		close(pipeH[1]);
		clock_t tt;
		tt = clock();
		
		while((n = read(pipeH[0], buf, bufsize)) > 0){
			printf("child index=%d n = %d\n", index, n);
			fwrite(buf, 1, n, fdw);
			fflush(fdw);
		}
		tt = clock() - tt;
		printf("bufsize=%d time=%d\n", bufsize, tt);
		fclose(fdw);
		close(pipeH[0]);
		delete[] buf;
		exit(0);
	}
	else if(pid > 0){
		printf("main start %d\n", ++index);
		close(pipeH[0]);
		FILE* fd = fopen("./source1.txt", "r");
		if (fd == NULL ){
			printf("open source failed\n");
			return -1;
		}
		clock_t tt;
		clock_t tt1;
		tt = clock();
		//printf("main tt=%u\n", tt);
		while((n = fread(buf, 1, bufsize, fd)) > 0){
			printf("index=%d n = %d\n", index, n);
			write(pipeH[1], buf, n);
		}
		printf("\n");
		tt1 = clock();
		printf("main write tt1=%d time=%d\n", tt1, tt1-tt);
		close(pipeH[1]);
		fclose(fd);
		delete[] buf;
		sleep(2);
	}
	return 0;
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
