//#include<stdlib>
#include "Time.h"
#include<stdio.h>
#include <stdlib.h>
//debug for syscall[Eden 20201207]
#include <unistd.h>
#include <sys/syscall.h>
#include <vector>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
void testtime()
{
	//------time
	tm tt = getSystemTm();
	int i = 0x7F;
	printf("week=%d %x\n" ,tt.tm_wday,i<<1);
	
}

void testvector()
{
	std::vector<int> n;
	n.push_back(1);
	n.push_back(2);
	n.push_back(3);
	n.push_back(4);
	
	for (auto it = n.begin() ; it != n.end() ; ++it)
	{
		std::cout<<"value="<< *it << std::endl;
		//if (*it == 4)
			n.erase(it);
		std::cout<<"value1="<< *it << std::endl;
	}
}

int countDirFileNum(const char* strVideoDir)	//0 empty;
{
	int num = 0;
	string name;
	DIR* dirp;
	struct dirent *ptr;
	struct stat statbuf;
	dirp = opendir(strVideoDir);
	if (dirp == NULL ){
		printf("open dir=%s  failed. errno=%s", strVideoDir, strerror(errno));
		return 0;
	}
	//chdir(strVideoDir);
	while(NULL != (ptr = readdir(dirp))) {
		lstat(ptr->d_name, &statbuf);
		if(S_IFDIR & statbuf.st_mode) {
			printf("open dir:%s\n",ptr->d_name);
		} else {
			name = ptr->d_name;
			printf("open file:%s\n",ptr->d_name);
			num++;
		}
	}
	//chdir("..");
	closedir(dirp);
	printf("countDirFileNum %d in %s\r\n", num, strVideoDir);
	return num;
}

int main()
{
	
	int value = std::atoi("0300");
	printf("value = %d\n", value);
	int court = countDirFileNum("/home/gateway/Eden/Test");
	printf("court = %d\n", court);
	int ret = system("cp compile.sh ./chdir_test/compile.sh1");
	printf("ret = %d\n", ret);
	chdir("./chdir_test/");
	ret = system("mv compile.sh ./chdir_test/compile.sh");
	printf("ret1 = %d\n", ret);
	return 0;
	testvector();
	return 0;
	testtime();
	string tmp("123");
	return 0;
	printf("string length=%lu\n" ,tmp.length());
	int tid =  syscall(SYS_gettid);
	int pid =  pthread_self();
	printf(" pthreadid=%u tid=%d \n" ,pid,tid);
	int id = 0x1000;
	CreateTimer(id, 0, test ,60);
	sleep(1);
	//DeleteTimer(id);
	CreateTimer(id, 5, test ,10);
	while(1)
	{
		printf("wait.\n");
		sleep(5);
	}
	
}
