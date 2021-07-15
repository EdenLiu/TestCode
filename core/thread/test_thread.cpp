//#include<stdlib>
#include<stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>

/*
在m_Thread对应的线程函数还未执行完的时候，对m_Thread再次进行赋值会引起系统崩溃
try catch 也拯救不了
*/

using namespace std;
static int index = 0;
void CommandHandler(){
	printf("test std::thread opeator=() index=%d\n" ,++index);
	//while(1){
		//sleep(1);
	//}
}

int main()
{
	std::thread m_Thread, m_Thread1;
	m_Thread.join();
	//m_Thread = m_Thread1; //error thread的opeator=操做delete了
	try{
		for (int i = 1 ; i < 100 ; ++i){
			m_Thread = std::thread(CommandHandler);
			m_Thread.join();
		}
	}
	catch(exception& e){
		printf("exception %s\n", e.what());
	}
	printf("exit\n");
	
	return 0;
}
