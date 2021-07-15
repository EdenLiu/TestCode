#include "Time.h"
#include <thread>
#include <map>
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
//debug for syscall[Eden 20201207]
#include <unistd.h>
#include <sys/syscall.h>

static map<int, timer_t> timerMap;
void test(sigval_t v)
{
	static int i = 0;
	int id =  pthread_self();
	++i;
	int tid =  syscall(SYS_gettid);
	while(1)
	{
		printf("%d. pthreadid=%u tid=%d \n" ,i,id,tid);
		sleep(3);
	}
}


void CreateTimer(int id, int time, void (*_function)(sigval_t),
		int repeat, const string& payload) {
	try {
		printf("%s\n" ,__FUNCTION__);
		DeleteTimer(id);
		struct sigevent evp;
		timer_t timer;
		memset(&evp, 0, sizeof(evp));
		evp.sigev_notify = SIGEV_THREAD;
		evp.sigev_notify_function = _function;
		evp.sigev_value.sival_int = id;

		if (timer_create(CLOCK_REALTIME, &evp, &timer) == -1) {
			//DEBUG(Debug::WARN, "create timer error");
			return;
		}
		struct itimerspec it;
		it.it_interval.tv_sec = repeat;
		it.it_interval.tv_nsec = 0;
		it.it_value.tv_sec = time;
		it.it_value.tv_nsec = 10;

		if (timer_settime(timer, 0, &it, NULL) == -1) {
			//DEBUG(Debug::WARN, "fail to timer_settime");
			return;
		}
		//DEBUG(Debug::INFO,"Create timer:"+to_string(id)+", delay:"+to_string(time));
		//DEBUG(Debug::INFO, "Payload:"+payload);
		//payloadMap.insert(pair<int, string>(id, payload));
		timerMap.insert(pair<int, timer_t>(id, timer));
	} catch (exception& e) {
		//DEBUG(Debug::ERROR, e.what());
	}
}

void DeleteTimer(int id) {
	printf("%s\n" ,__FUNCTION__);
	auto iter = timerMap.find(id);
	if (iter != timerMap.end()) {
		if (timer_delete(iter->second) == -1) {
			//DEBUG(Debug::WARN, "delete timer failed:"+to_string(id));
		} else {
			//DEBUG(Debug::INFO, "Delete timer:"+to_string(id));
			printf("Delete timer: %d\n",id);
			timerMap.erase(iter);
		}
	}
}

struct tm getSystemTm() {
		/*time_t tt;
		time(&tt);
		char symbol[1];
		int hour = 0, min = 0;
		sscanf(timeZone.c_str(), "GMT%1s%d:%d", &symbol, &hour, &min);

		if (strcmp(symbol, "-") == 0) {
			tt = tt - hour * 3600 - min * 60;
		} else {
			tt = tt + hour * 3600 + min * 60;
		}
		tt = tt+DST*3600;
		gmtime_r(&tt, &systemTm);
		systemTm.tm_year += 1900;
		systemTm.tm_mon +=  1;
		return systemTm;*/
		struct tm systemTm;
		time_t tt;
		time(&tt);
		struct tm* p;
		p = localtime(&tt);
		systemTm = *p;
		systemTm.tm_year +=1900;
		systemTm.tm_mon +=1;
		return systemTm;
}