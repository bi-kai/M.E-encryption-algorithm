#include<time.h>  
#include<stdio.h>  
char* Printf_time()
{ 
	time_t now; //ʵ����time_t�ṹ
	struct tm *timenow; //ʵ����tm�ṹָ��
	time(&now);
	timenow = localtime(&now);
	return asctime(timenow);
}