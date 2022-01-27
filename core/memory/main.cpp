//#include<stdlib>
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
#include "nvwa/debug_new.h"
#define MEMORY_SIZE 1024*1024*10

void fun(){
	char* p = new char[10];
	return ;
}
int main(int arg, const char** argv)
{
	fun();
	while(1){
		sleep(2);
	}
	return 0;
	if (arg > 1){
		int size = atoi(argv[1]);
		std::cout << "size = " << size << std::endl;
		if (size < 0){
			std::cout << "size is invaild " << std::endl;
			return -1;
		}
		for (int i = 0 ; i < size; ++i){
			char* p = new char[MEMORY_SIZE];
			memset(p ,0 ,MEMORY_SIZE);
			std::cout << "allocate mempry = " << MEMORY_SIZE << std::endl;
		}
	}
	
	while(1){
		sleep(2);
	}
	
}
