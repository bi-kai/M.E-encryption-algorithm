#include "RS_head.h"
int rs_mul(int a,int b,int m, int *Gal,int * ind)
{
	int a1=0,b1=0,c=0;
	if (a*b==0) 
   return 0;
	else
	{
			a1=ind[a-1];//a是伽罗华域的元素,例如a=（i^3）=01000，ind(8)则是返回的是i的指数 （00011）
			 b1=ind[b-1];//b是伽罗华域的元素例如b=（i^20）=01100，ind(12)则是返回的是i的指数（10100）
		  c=(a1+b1)%(int)(pow(2.0,m)-1); //c是a与b乘积的指数（10111）=23
			return Gal[c];//y=gal（24）即为（（i^23）=01111）
	}
 
}
 
