#include "RS_head.h"
void de2bi(int input,int m,int *out)//十进制转化为二进制
{
	int i=0,temp=input;
	while(temp!=0)
	{
	out[m-i-1]=temp/(int)pow(2.0,m-i-1);
	temp=temp%(int)pow(2.0,m-i-1);
	i++;
	}
}

int rs_add(int a,int b,int m)//伽罗华域的加法
{
	int a1[M]={0},b1[M]={0},y[M]={0};
   de2bi(a,m,a1);// 把十进制数a转化为m位二进制数，这里是低位在前，例如de2bi（3）=11000
  de2bi(b,m,b1);// 把十进制数b转化为m位二进制数，这里是低位在前
  for(int i=0;i<m;i++)
	  y[i]=a1[i]^b1[i];
 return Bi_to_Dec(y);
}