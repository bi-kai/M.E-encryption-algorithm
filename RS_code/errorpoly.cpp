#include "RS_head.h"
void errorpoly(
	int * input_syndrome, //����У����
	int n ,//�볤
	int k,//��Ϣλ����
	int m,//GF(2^m)
	int * Gal,//٤�޻����Ԫ��
	int * ind,//������
	int sigma[][N-K+1],//sigma���ݱ�
	int *Degree_sigma//�洢sigma�Ķ�
	) 
{
//%/�������ʽ�Ͷ���ʽ����ߴ���
//input_syndrome����n-k����
		int omega[N-K+2][N-K+1]={0};//�洢omega[][]���ڼ������ֵ
		int D[N-K+2]={0};         //  ������n-k+2�ε���
		int deltaD[N-K+2]={0}; //  ������n-k+2�ε���      
		int d[N-K+2]={0};         //  ������n-k+2�ε���      
		int sum=0;
//%��ʼ��
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
for(int j=2;j<=n-k;j++) //j=2:n-k  // %��������n-k-1=��2*t-1���Σ�Ӧ�ü���2*t�Σ�
{
	//=============================================calculate five datas when d(j-1)==0 =======================
    if (d[j-1]==0)     // ��d(j-1)==0ʱ��ǰһ������ֱ�Ӹ�����ǰ
   {  
	   for(int p=0;p<N-K+1;p++)
	   {
			sigma[j][p]=sigma[j-1][p]; //%��d(j-1)==0ʱ��ǰһ������ֱ�Ӹ�����ǰ
            omega[j][p]=omega[j-1][p]; //%��d(j-1)==0ʱ��ǰһ������ֱ�Ӹ�����ǰ
	   }
          D[j]=D[j-1]; //%��d(j-1)==0ʱ��ǰһ������ֱ�Ӹ�����ǰ
          deltaD[j]=j-1-D[j];
//%==============calculate dj===================================
          Degree_sigma[0]=0;  //%calculate maximum power of sigma(j,:)
		  for (int t=n-k;t>=0;t--) //% search the maximum power in the current sigma(j,:)��the maximum power always on the right of sigma(j,:)���ߴ��ݷ��ں��棩
		  {
			  if (sigma[j][t]!=0) //%find the first nonzero data��it��s location indicate the maximum power of the current sigma ��
			  {
				  Degree_sigma[0]=t;
					 break ;//%find maximum power and stop
			  }
		  } 
          sum=0;                                   
          for(int i1=0;i1<=Degree_sigma[0]-1;i1++)                         
              sum=rs_add(sum,rs_mul(input_syndrome[j-i1-2],sigma[j][i1+1],m,Gal,ind),m);//%����j==3ʱ�൱�ھ�����281ҳ�ĵ�һ�У�����dj�Ĺ�ʽ���
         // %=======����dj��ʽ�е����һ���������
          d[j]=rs_add(input_syndrome[j-1],sum,m);  // %calculate d(j)
    }
//%=============================================calculate five datas when d(j-1)!=0 ====================================================
    else
    {
		//%===========================Ѱ��max��j��D��j������i���ڵ�����===========================
       int  maxdeltaD=deltaD[0];     //  % initial maxdeltaD=-1 when calculating every five datas    search i and calculate D(j)&deltaD(j)
        int   i=0;           
          for(int ii=0;ii<=j-2;ii++)
		  {
              if  (deltaD[ii]>maxdeltaD&&d[ii]!=0)//% �����������£��ҳ�����deltaD
			  { 
				  maxdeltaD=deltaD[ii];
                  i=ii;
			  }
		  }
        // %===========================���D��j����deltaD��j��===================================================================================== 
              D[j]=D[j-1]>(j-1-i+D[i])?D[j-1]:(j-1-i+D[i]);       //D(j)=maximum(D(j-1),j-1-i+D(i));         
              deltaD[j]=j-1-D[j];    
       //  %===========================���sigma omega =====================================================================================  
			  int  u[N-K+1]={0};
			  int  v[N-K+1]={0};
			for(int p=0;p<N-K+1;p++)
			{
				u[p]=sigma[i][p];// u=sigma(i,:);%���ʽ��7.5.13���ұߵ�sigma��i��                         
              v[p]=omega[i][p];//v=omega(i,:);//%���ʽ��7.5.14���ұߵ�omega��i��
			}
             // %=========================����˾�����279ҳ-7.5.13��7.5.14��ʽ�������ֵļ���===============
             int  mul=rs_mul(d[j-1],rs_rev(d[i],m,Gal, ind),m,Gal,ind);//%calculate d(j)&d(i)^(-1)rs_rev(d[j-1],m,Gal,ind)
                for (int aa=0;aa<=n-k;aa++)
				{ 
					u[aa]=rs_mul(mul,u[aa],m,Gal,ind);///% calculate dj*��di��^��-1��*sigma^i��x��
                    v[aa]=rs_mul(mul,v[aa],m,Gal,ind);//% calculate dj*��di��^��-1��*omiga^i��x��
				}
               //==========================================================================
                for(int bb=n-k-(j-1-i);bb>=0;bb--) //
				{
					u[bb+1+j-2-i]=u[bb];//%�����ǳ���x^��j-i���Ĳ��֣�ֻ��Ҫ�� u �е����������ƶ���j-i��λ��
                    v[bb+1+j-2-i]=v[bb];//%�����ǳ���x^��j-i���Ĳ��֣�ֻ��Ҫ�� v �е����������ƶ���j-i��λ��
				}
                for(int cc=0;cc<=j-i-2;cc++)//
				{
					u[cc]=0;///% ���ߣ�(j-1-i)λ����ǰ���(j-1-i)λ����0��
                    v[cc]=0;///% ���ߣ�(j-1-i)λ����ǰ���(j-1-i)λ����0��
				} 
              //  %====================================
                for(int dd=0;dd<=n-k;dd++)
				{
					sigma[j][dd]=rs_add(sigma[j-1][dd],u[dd],m); //%sigma^(j)��x����dj*di^(-1)*x^(j-i)*sigma^(i)(x)
                    omega[j][dd]=rs_add(omega[j-1][dd],v[dd],m); //%omiga^(j)��x����dj*di^(-1)*x^(j-i)*omiga^(i)(x)
                 }
//%===========================calculate d(j) ==========================================================
               //  % =================sigma(x)�Ķ�=============      
              Degree_sigma[0]=0;  
                for(int t=n-k;t>=0;t--) //
				{
					if(sigma[j][t]!=0)  //% search the first nonzero data from the right����ߴ����ں��棩 
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
//%======================�ҳ����յĴ������ʽ=============================================================
	int j=n-k+1; //% ��2*t�����ݵ�������    
	if (d[j-1]==0)   //       %d(j-1)==0
			for(int p=0;p<N-K+1;p++)
			sigma[j][p]=sigma[j-1][p];  
	else   //%��j������2*t��d(j-1)���ǲ�����0 ����ʱ��Ҫ�ж�Ӧ����Ϊ��ֹ���ǣ��в����Ĵ���
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
					u[p]=sigma[i][p];// u=sigma(i,:);%���ʽ��7.5.13���ұߵ�sigma��i��                         
				   v[p]=omega[i][p];//v=omega(i,:);//%���ʽ��7.5.14���ұߵ�omega��i��
				}
				int   mul=rs_mul(d[j-1],rs_rev(d[i],m,Gal,ind),m,Gal,ind);//%d(j)&d(i)^(-1)
					for (int aa=0;aa<=n-k;aa++)//aa=1:n-k+1
					{ 
						u[aa]=rs_mul(mul,u[aa],m,Gal,ind);///% calculate dj*��di��^��-1��*sigma^i��x��
						v[aa]=rs_mul(mul,v[aa],m,Gal,ind);//% calculate dj*��di��^��-1��*omiga^i��x��
					}
				  for(int bb=n-k-(j-1-i);bb>=0;bb--) 
					{
						u[bb+1+j-2-i]=u[bb];//%�����ǳ���x^��j-i���Ĳ��֣�ֻ��Ҫ�� u �е����������ƶ���j-i��λ��
						v[bb+1+j-2-i]=v[bb];//%�����ǳ���x^��j-i���Ĳ��֣�ֻ��Ҫ�� v �е����������ƶ���j-i��λ��
					}
				  for(int cc=0;cc<=j-i-2;cc++)
					{
						u[cc]=0;/// ���ߣ�(j-1-i)λ����ǰ���(j-1-i)λ����0��
						v[cc]=0;/// ���ߣ�(j-1-i)λ����ǰ���(j-1-i)λ����0��
					} 
				   for(int dd=0;dd<=n-k;dd++)
						sigma[j][dd]=rs_add(sigma[j-1][dd],u[dd],m); //%sigma^(j)��x��-dj*di^(-1)*x^(j-i)*sigma^(i)(x)
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