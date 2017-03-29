#include "RS_head.h"
void errorpoly(
	int * input_syndrome, //输入校验子
	int n ,//码长
	int k,//信息位长度
	int m,//GF(2^m)
	int * Gal,//伽罗华域的元素
	int * ind,//索引表
	int sigma[][N-K+1],//sigma数据表
	int *Degree_sigma//存储sigma的度
	) 
{
//%/错误多项式和多项式的最高次数
//input_syndrome共有n-k个数
		int omega[N-K+2][N-K+1]={0};//存储omega[][]用于计算错误值
		int D[N-K+2]={0};         //  最大进行n-k+2次迭代
		int deltaD[N-K+2]={0}; //  最大进行n-k+2次迭代      
		int d[N-K+2]={0};         //  最大进行n-k+2次迭代      
		int sum=0;
//%初始化
sigma[0][0]=1;
sigma[1][0]=1;
//%=================================================
omega[0][0]=0;
omega[1][0]=1;
//%=================================================
deltaD[0]=-1;
deltaD[1]=0;
//%=================================================
d[0]=1;
d[1]=input_syndrome[0];
//%=================================================
for(int j=2;j<=n-k;j++) //j=2:n-k  // %（计算了n-k-1=（2*t-1）次，应该计算2*t次）
{
	//=============================================calculate five datas when d(j-1)==0 =======================
    if (d[j-1]==0)     // 当d(j-1)==0时，前一个数据直接赋给当前
   {  
	   for(int p=0;p<N-K+1;p++)
	   {
			sigma[j][p]=sigma[j-1][p]; //%当d(j-1)==0时，前一个数据直接赋给当前
            omega[j][p]=omega[j-1][p]; //%当d(j-1)==0时，前一个数据直接赋给当前
	   }
          D[j]=D[j-1]; //%当d(j-1)==0时，前一个数据直接赋给当前
          deltaD[j]=j-1-D[j];
//%==============calculate dj===================================
          Degree_sigma[0]=0;  //%calculate maximum power of sigma(j,:)
		  for (int t=n-k;t>=0;t--) //% search the maximum power in the current sigma(j,:)（the maximum power always on the right of sigma(j,:)，高次幂放在后面）
		  {
			  if (sigma[j][t]!=0) //%find the first nonzero data（it’s location indicate the maximum power of the current sigma ）
			  {
				  Degree_sigma[0]=t;
					 break ;//%find maximum power and stop
			  }
		  } 
          sum=0;                                   
          for(int i1=0;i1<=Degree_sigma[0]-1;i1++)                         
              sum=rs_add(sum,rs_mul(input_syndrome[j-i1-2],sigma[j][i1+1],m,Gal,ind),m);//%这里j==3时相当于纠错码281页的第一行，按照dj的公式求解
         // %=======计算dj公式中的左边一项，单独计算
          d[j]=rs_add(input_syndrome[j-1],sum,m);  // %calculate d(j)
    }
//%=============================================calculate five datas when d(j-1)!=0 ====================================================
    else
    {
		//%===========================寻找max（j—D（j））和i所在的行数===========================
       int  maxdeltaD=deltaD[0];     //  % initial maxdeltaD=-1 when calculating every five datas    search i and calculate D(j)&deltaD(j)
        int   i=0;           
          for(int ii=0;ii<=j-2;ii++)
		  {
              if  (deltaD[ii]>maxdeltaD&&d[ii]!=0)//% 在满足条件下，找出最大的deltaD
			  { 
				  maxdeltaD=deltaD[ii];
                  i=ii;
			  }
		  }
        // %===========================求解D（j）和deltaD（j）===================================================================================== 
              D[j]=D[j-1]>(j-1-i+D[i])?D[j-1]:(j-1-i+D[i]);       //D(j)=maximum(D(j-1),j-1-i+D(i));         
              deltaD[j]=j-1-D[j];    
       //  %===========================求解sigma omega =====================================================================================  
			  int  u[N-K+1]={0};
			  int  v[N-K+1]={0};
			for(int p=0;p<N-K+1;p++)
			{
				u[p]=sigma[i][p];// u=sigma(i,:);%表达式（7.5.13）右边的sigma（i）                         
              v[p]=omega[i][p];//v=omega(i,:);//%表达式（7.5.14）右边的omega（i）
			}
             // %=========================完成了纠错码279页-7.5.13和7.5.14公式第三部分的计算===============
             int  mul=rs_mul(d[j-1],rs_rev(d[i],m,Gal, ind),m,Gal,ind);//%calculate d(j)&d(i)^(-1)rs_rev(d[j-1],m,Gal,ind)
                for (int aa=0;aa<=n-k;aa++)
				{ 
					u[aa]=rs_mul(mul,u[aa],m,Gal,ind);///% calculate dj*（di）^（-1）*sigma^i（x）
                    v[aa]=rs_mul(mul,v[aa],m,Gal,ind);//% calculate dj*（di）^（-1）*omiga^i（x）
				}
               //==========================================================================
                for(int bb=n-k-(j-1-i);bb>=0;bb--) //
				{
					u[bb+1+j-2-i]=u[bb];//%这里是乘以x^（j-i）的部分（只需要把 u 中的数据往后移动（j-i）位）
                    v[bb+1+j-2-i]=v[bb];//%这里是乘以x^（j-i）的部分（只需要把 v 中的数据往后移动（j-i）位）
				}
                for(int cc=0;cc<=j-i-2;cc++)//
				{
					u[cc]=0;///% 移走（(j-1-i)位后，最前面的(j-1-i)位补上0）
                    v[cc]=0;///% 移走（(j-1-i)位后，最前面的(j-1-i)位补上0）
				} 
              //  %====================================
                for(int dd=0;dd<=n-k;dd++)
				{
					sigma[j][dd]=rs_add(sigma[j-1][dd],u[dd],m); //%sigma^(j)（x）—dj*di^(-1)*x^(j-i)*sigma^(i)(x)
                    omega[j][dd]=rs_add(omega[j-1][dd],v[dd],m); //%omiga^(j)（x）—dj*di^(-1)*x^(j-i)*omiga^(i)(x)
                 }
//%===========================calculate d(j) ==========================================================
               //  % =================sigma(x)的度=============      
              Degree_sigma[0]=0;  
                for(int t=n-k;t>=0;t--) //
				{
					if(sigma[j][t]!=0)  //% search the first nonzero data from the right（最高次幂在后面） 
					{ 
						Degree_sigma[0]=t;
					    break;
					}
				}
               // %===========================calculate d(j) ============
              sum=0;
                for(int i1=0;i1<=Degree_sigma[0]-1;i1++) 
                    sum=rs_add(sum,rs_mul(input_syndrome[j-2-i1],sigma[j][i1+1],m,Gal,ind),m);
                    d[j]=rs_add(input_syndrome[j-1],sum,m); 
          }
}
//%======================找出最终的错误多项式=============================================================
	int j=n-k+1; //% 第2*t行数据单独处理    
	if (d[j-1]==0)   //       %d(j-1)==0
			for(int p=0;p<N-K+1;p++)
			sigma[j][p]=sigma[j-1][p];  
	else   //%当j等于了2*t，d(j-1)还是不等于0 ，此时需要判断应该判为终止还是（有不纠的错误）
	  {  
		 int  maxdeltaD=deltaD[0];     //  %search i and calculate D(j)&deltaD(j)
			int    i=0;           
			  for(int ii=0;ii<=j-1-1;ii++)              
			  {
				  if  (deltaD[ii]>maxdeltaD&&d[ii]!=0)
				  {
					  maxdeltaD=deltaD[ii];
					  i=ii;
				  } 
			  }
				int  u[N-K+1]={0};
				  int  v[N-K+1]={0};
				for(int p=0;p<N-K+1;p++)
				{
					u[p]=sigma[i][p];// u=sigma(i,:);%表达式（7.5.13）右边的sigma（i）                         
				   v[p]=omega[i][p];//v=omega(i,:);//%表达式（7.5.14）右边的omega（i）
				}
				int   mul=rs_mul(d[j-1],rs_rev(d[i],m,Gal,ind),m,Gal,ind);//%d(j)&d(i)^(-1)
					for (int aa=0;aa<=n-k;aa++)//aa=1:n-k+1
					{ 
						u[aa]=rs_mul(mul,u[aa],m,Gal,ind);///% calculate dj*（di）^（-1）*sigma^i（x）
						v[aa]=rs_mul(mul,v[aa],m,Gal,ind);//% calculate dj*（di）^（-1）*omiga^i（x）
					}
				  for(int bb=n-k-(j-1-i);bb>=0;bb--) 
					{
						u[bb+1+j-2-i]=u[bb];//%这里是乘以x^（j-i）的部分（只需要把 u 中的数据往后移动（j-i）位）
						v[bb+1+j-2-i]=v[bb];//%这里是乘以x^（j-i）的部分（只需要把 v 中的数据往后移动（j-i）位）
					}
				  for(int cc=0;cc<=j-i-2;cc++)
					{
						u[cc]=0;/// 移走（(j-1-i)位后，最前面的(j-1-i)位补上0）
						v[cc]=0;/// 移走（(j-1-i)位后，最前面的(j-1-i)位补上0）
					} 
				   for(int dd=0;dd<=n-k;dd++)
						sigma[j][dd]=rs_add(sigma[j-1][dd],u[dd],m); //%sigma^(j)（x）-dj*di^(-1)*x^(j-i)*sigma^(i)(x)
					Degree_sigma[0]=0;  //  %calculate maximum power of the sigma 
					for(int t=n-k;t>=0;t--) 
						{
							if (sigma[j][t]!=0)
							  { 
								  Degree_sigma[0]=t;
									break  ;//    %find maximum power and stop
								}   
						 }
	}
}