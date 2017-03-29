#include<time.h>  
#include<stdio.h>  
char* Printf_time()
{ 
	time_t now; //实例化time_t结构
	struct tm *timenow; //实例化tm结构指针
	time(&now);
	timenow = localtime(&now);
	return asctime(timenow);
}