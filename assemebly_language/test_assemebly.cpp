#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int main(int arg, char** argc){
	int i = 0x22;
	int b = argc[1][0];
	return i + b;
}
