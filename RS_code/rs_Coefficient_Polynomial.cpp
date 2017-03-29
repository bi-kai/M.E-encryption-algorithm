#include "RS_head.h"
void rs_Coefficient_Polynomial(
	int m,//GF(2^m)
	int t,//(N-K)/2
	int *Gal,// 伽罗华元素数据表
	int* index,//索引表
	int *Coefficient_Polynomial//多项式的系数
	)//计算出生成多项式的系数
{
	for(int i=0;i<2*T+1;i++)
		 Coefficient_Polynomial[i]=0;
	int bb[2]={0};
	int cc[2*T+1]={0};
	int dd[2*T+1]={0};
	Coefficient_Polynomial[0]=Gal[1];
	Coefficient_Polynomial[1]=1;
	for(int i=0;i<2*T-1;i++)
	{
		 bb[0]=Gal[(i+1)%(int)(pow(2.0,m)-1)+1];
         bb[1]=1;
				 for(int j=0;j<2*T;j++)
			{
				 cc[j]=rs_mul(bb[0],Coefficient_Polynomial[j],m,Gal,index);
				 dd[j+1]=rs_mul(bb[1],Coefficient_Polynomial[j],m,Gal,index);
			}
			for(int p=0;p<2*T+1;p++)
			{
				Coefficient_Polynomial[p]=rs_add(cc[p],dd[p],m);
			}
    }
}