#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
void test_printf(const char * formatString, va_list ap)
{
	vprintf(formatString, ap);
}

void _printf(const char * formatString, ...)
{
	va_list ap;
	va_start(ap, formatString);
	test_printf(formatString, ap);
	va_end(ap);
}

int main(int arg, char** argc){
	_printf("test : %d\n", 1);
	return 1;
}
