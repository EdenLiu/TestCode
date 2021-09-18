#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
int fun1(unsigned word){
	return (int)((word << 24) >> 24);
}

int fun2(unsigned word){
	return ((int)(word << 24) >> 24);
}
/*
深入理解计算机
2.2.6
整数 扩展一个数字的位表示

结果：
a=00000078
a=000000c9
a=00000087
a=00000078
a=ffffffc9
a=ffffff87
*/
int main(int arg, char** argc){
	printf("a=%08x\n", fun1(0x00000078));
	printf("a=%08x\n", fun1(0x000000C9));
	printf("a=%08x\n", fun1(0xEDCBA987));
	printf("a=%08x\n", fun2(0x00000078));
	printf("a=%08x\n", fun2(0x000000C9));
	printf("a=%08x\n", fun2(0xEDCBA987));
	return 0;
}
