#include "RS_head.h"
void syndrome(
	int *input_receive_from_channel, //从信道的输出值
	int n,//码长
	int k, //信息位长
	int m,//GF(2^m)
	int * Gal,//伽罗华域
	int *ind,//索引表
	int * syndrome_output//输出校验子
	)//计算校验值
{
	for(int i=0;i<=n-k-1;i++)
		syndrome_output[i]=0;
	for(int i=0;i<=n-k-1;i++)
	{
		int  sum=0;
        for(int j=n-1;j>=0;j--) 
			sum=rs_add(sum,rs_mul(Gal[((i+1)*(j)%(int)(pow(2.0,m)-1))],input_receive_from_channel[j],m,Gal,ind),m);
		//%这里按照下面的H校验矩阵进行校验
     syndrome_output[i]=sum;
    }
}

