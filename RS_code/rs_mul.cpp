#include "RS_head.h"
int rs_mul(int a,int b,int m, int *Gal,int * ind)
{
	int a1=0,b1=0,c=0;
	if (a*b==0) 
   return 0;
	else
	{
			a1=ind[a-1];//a��٤�޻����Ԫ��,����a=��i^3��=01000��ind(8)���Ƿ��ص���i��ָ�� ��00011��
			 b1=ind[b-1];//b��٤�޻����Ԫ������b=��i^20��=01100��ind(12)���Ƿ��ص���i��ָ����10100��
		  c=(a1+b1)%(int)(pow(2.0,m)-1); //c��a��b�˻���ָ����10111��=23
			return Gal[c];//y=gal��24����Ϊ����i^23��=01111��
	}
 
}
 
