#pragma once
#include <ctime>
#include <sys/time.h>
#include <signal.h>
#include <string>
#include <signal.h>

using namespace std;

void test(sigval_t v);
void CreateTimer(int id, int time, void (*_function)(sigval_t),
		int repeat = 0, const string& payload = "");
		
void DeleteTimer(int id);
struct tm getSystemTm();