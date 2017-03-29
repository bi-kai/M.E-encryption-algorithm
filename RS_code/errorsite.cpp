#include "RS_head.h"
   int  errorsite(
	int *input_syndrome,//输入校验子
	int n ,//码长
	int k, //信息位长度
	int m,//GF(2^m)
	int * Gal,//伽罗华域元素
	int *ind,//索引表
	int * error_site,//指示了错误位置，例如alpha^125，存储125，表示125次幂位置出错
	int sigma[][N-K+1],//sigma 数据表
	int *Degree_sigma,//存储sigma的度
	int error_site_Dec[]////指示了错误位置，例如alpha^125，存储alpha^125对应的十进制，表示125次幂位置出错
	)//  函数返回1时，表示有不可纠正的错误，0表示可以正常纠错
{
	int flag=0;
//% error_site_Dec指示了错位位子（十进制），error_site（错位位子（十进制）对应的幂次数），Degree_sigma[0]的最高次数
	 errorpoly(input_syndrome, n , k,  m, Gal,ind,sigma,Degree_sigma) ; 
//%由错误多项式，求解错位位置（求解方程的根，方程的根指示了错位位置）
	int aa=0;
	for(int p=0;p<n;p++ )
		error_site[p]=0;//用来记录错误图样的多项式，其中的数据指示了错误位子（对应十进制数）

	for(int p=0;p<Degree_sigma[0];p++ )
		error_site_Dec[p]=0;//错误位子（对应十进制数）对应的幂次数

for(int j=0;j<=pow(2.0,m)-2;j++) // 收索2^m-2个元素，(除开0)以求出方程的解
  {
	 int  sum=sigma[n-k+1][0];//%初始化，将sigma的第一个数据（0次幂项）给sum
    for(int i=0;i<=Degree_sigma[0]-1;i++) //i=1:Degree_sigma[0] % 做Degree_sigma[0]次循环（加法）
	{
		if (sigma[n-k+1][i+1]!=0)
			sum=rs_add(sum,Gal[(ind[sigma[n-k+1][i+1]-1]+ind[j]*(i+1))%(int)(pow(2.0,m)-1)],m);
       // ind(sigma(n-k+2,i+1)) 指的是sigma(n-k+2,i+1)对应的aerfa的幂次数，ind(j)*i指的是x^i(x=ind(j))对应的的幂次数
	}
    if (sum==0 )    //%aerfa^ind（j)是方程的根(即为j（用十进制表示））
	{
		error_site[aa]=j+1;
       aa=aa+1; // %把计算的满足方程的根依次的存入s中
	}
}
//=========================================================================
  int    bb=0;              // %calculate maximum power
     for(int t=n-1;t>=0;t--)          
         if (error_site[t]!=0)
		 {
			 bb=t+1;  //%t指示了错误多项式最大的次数（也即为方程根的个数）
            break ;//                          %find maximum power and stop
	 }  
//%==================判断是否出错==============================
		if ( (Degree_sigma[0]!=bb)||(Degree_sigma[0]>(n-k)/2) ) /// %sigma has no answer or Degree_sigma[0] is overflow
			flag=1;  //   %有不可纠错的码字
		else
		{
			for(int cc=0;cc<=aa-1;cc++) // 是因为上面最后的一次aa自加了一次
		   {
			   error_site_Dec[cc]=rs_rev(error_site[cc],m,Gal,ind);//% 取逆元素
			   error_site[cc]=ind[rs_rev(error_site[cc],m,Gal,ind)-1]+1;//% 逆元素（十进制）对应的幂次数
		   }
			flag=0;
		}
		return flag;
}