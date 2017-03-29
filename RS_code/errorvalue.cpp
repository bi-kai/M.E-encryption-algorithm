#include "RS_head.h"
    int errorvalue(
	int * input_syndrome, //输入校验子
	int n ,//码长
	int k, //信息位长度
	int m,//GF(2^m)
	int * Gal,//伽罗华域元素
	int * ind,//索引表
	int *Degree_sigma,//sigma的度
	int * errorvalue_output//错误值大小
	)// 函数值返回1时，表示出现不可纠正的错误，0表示可以正常纠错
{
	int error_site[N]={0};
	int sigma[N-K+2][N-K+1]={0};
	int error_site_Dec[N-K+1]={0};
	int sigmaji[N-K+1][N-K+1]={0};
	int flag=0;int flag_errorvalue=0;
	flag=errorsite(input_syndrome, n ,k,m, Gal,ind,error_site,sigma,Degree_sigma,error_site_Dec);
// error_site_Dec指示了错位位子（十进制）,S（错位位子（十进制）对应的幂次数，即为第几位有错）
	//Degree_sigma[0]是多项式的最高次数，flag 指示了有无不可纠错
	if (flag==1)  //flag=1 指示了有不可纠错，错误值直接赋为0
	{
		for(int p=0;p<n;p++)  
			errorvalue_output[p]=0; 
		flag_errorvalue=1;
	} 
    else //       flag=0 指示了无不可纠错
	{
		for(int p=0;p<N-K+1;p++)
		 sigmaji[p][0]=1;//%sigmaji的初始化
	//==================按照纠错码287--7.5.31公式计算sigmaji====================
		if (error_site[0]!=0)
		  for(int j=0;j<=Degree_sigma[0]-1;j++)
			 for(int i=0;i<=Degree_sigma[0]-1;i++)
				  sigmaji[j][i+1]=rs_add(sigma[n-k+1][i+1],rs_mul(sigmaji[j][i],error_site_Dec[j],m,Gal,ind),m);
	//===================按照纠错码287--7.5.32公式计算Yj======================
		 for(int j=0;j<=Degree_sigma[0]-1;j++)// % 一共是Degree_sigma[0]个错误数据  
			 {
				 int  sum1=0;
			   int sum2=0;
					for(int i=0;i<=Degree_sigma[0]-1;i++)//  for i=1:Degree_sigma[0]
				   {
					   sum1=rs_add(sum1,rs_mul(sigmaji[j][i],input_syndrome[Degree_sigma[0]-1-(i)],m,Gal,ind),m);
					   //%纠错码287--7.5.32公式的分子部分
					   sum2=rs_add(sum2,rs_mul(sigmaji[j][i],Gal[(ind[error_site_Dec[j]-1]*(Degree_sigma[0]-(i)))%((int)pow(2.0,m)-1)],m,Gal,ind),m);
					   //%纠错码287--7.5.32公式的分母部分
				   }
				   errorvalue_output[error_site[j]-1]=rs_mul(sum1,rs_rev(sum2,m,Gal,ind),m,Gal,ind);//% 最终的Yj值
			}
		 flag_errorvalue=0;
	}
	return  flag_errorvalue;
}
