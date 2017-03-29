#include "RS_head.h"
void encoder(
	int *input, //待编码的序列
	int n ,//码长
	int k, //信息位长
	int m,//GF(2^m)
	int * Gal,//伽罗华元素表
	int *ind,//索引表
	int *Coefficient_Polynomial,
	int * output
	)
{
	//%多项式的系数（升幂排序）例如（14 3 21 15 29 15 16 20 25 24  2  8 13 1 28 15  1）
	int Reg[N-K]={0}; //%n=30,k=14，暂存16个校验位
	int  message[K]={0};// %k=14暂存信息位
	int feedback=0;
	for (int i=0;i<k;i++)
	{
		feedback=rs_add(input[k-i-1],Reg[n-k-1],m);//% 信息位由高位到低位进入寄存器（input的最高位在后面）
		for(int j=n-k;j>=2;j--) //j=n-k:-1:2    %n-k=16  依次更新Reg（15）到Reg（0）寄存器的数据
		  { 
			  if(Coefficient_Polynomial[j-1]!=0)
				  Reg[j-1]=rs_add(Reg[j-2],rs_mul(Coefficient_Polynomial[j-1],feedback,m,Gal,ind),m);
				 // %第j个寄存器的数据由（上一个寄存器的数据）加上（第j个系数乘以反馈值）
			  else
				  Reg[j-1]=Reg[j-2];//%如果生成多项式的第j个系数为0，第j个寄存器的值直接由上一个寄存器的值得到
		  }  
      Reg[0]=rs_mul(Coefficient_Polynomial[0],feedback,m,Gal,ind);//%Reg（1）的值直接由Coefficient_Polynomial(1)和feedback得到
	}
for(int p=0;p<k;p++)  
    message[p]=input[p];
	for(int p=0;p<n;p++)
	{	
		if(p<(N-K))
	output[p]=Reg[p];//%输出的结果高次幂在后面，低次幂在前面
		else 
		output[p]=message[p-(N-K)];
	}
}             