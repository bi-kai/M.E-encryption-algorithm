#include "RS_head.h"
   int  errorsite(
	int *input_syndrome,//����У����
	int n ,//�볤
	int k, //��Ϣλ����
	int m,//GF(2^m)
	int * Gal,//٤�޻���Ԫ��
	int *ind,//������
	int * error_site,//ָʾ�˴���λ�ã�����alpha^125���洢125����ʾ125����λ�ó���
	int sigma[][N-K+1],//sigma ���ݱ�
	int *Degree_sigma,//�洢sigma�Ķ�
	int error_site_Dec[]////ָʾ�˴���λ�ã�����alpha^125���洢alpha^125��Ӧ��ʮ���ƣ���ʾ125����λ�ó���
	)//  ��������1ʱ����ʾ�в��ɾ����Ĵ���0��ʾ������������
{
	int flag=0;
//% error_site_Decָʾ�˴�λλ�ӣ�ʮ���ƣ���error_site����λλ�ӣ�ʮ���ƣ���Ӧ���ݴ�������Degree_sigma[0]����ߴ���
	 errorpoly(input_syndrome, n , k,  m, Gal,ind,sigma,Degree_sigma) ; 
//%�ɴ������ʽ������λλ�ã���ⷽ�̵ĸ������̵ĸ�ָʾ�˴�λλ�ã�
	int aa=0;
	for(int p=0;p<n;p++ )
		error_site[p]=0;//������¼����ͼ���Ķ���ʽ�����е�����ָʾ�˴���λ�ӣ���Ӧʮ��������

	for(int p=0;p<Degree_sigma[0];p++ )
		error_site_Dec[p]=0;//����λ�ӣ���Ӧʮ����������Ӧ���ݴ���

for(int j=0;j<=pow(2.0,m)-2;j++) // ����2^m-2��Ԫ�أ�(����0)��������̵Ľ�
  {
	 int  sum=sigma[n-k+1][0];//%��ʼ������sigma�ĵ�һ�����ݣ�0�������sum
    for(int i=0;i<=Degree_sigma[0]-1;i++) //i=1:Degree_sigma[0] % ��Degree_sigma[0]��ѭ�����ӷ���
	{
		if (sigma[n-k+1][i+1]!=0)
			sum=rs_add(sum,Gal[(ind[sigma[n-k+1][i+1]-1]+ind[j]*(i+1))%(int)(pow(2.0,m)-1)],m);
       // ind(sigma(n-k+2,i+1)) ָ����sigma(n-k+2,i+1)��Ӧ��aerfa���ݴ�����ind(j)*iָ����x^i(x=ind(j))��Ӧ�ĵ��ݴ���
	}
    if (sum==0 )    //%aerfa^ind��j)�Ƿ��̵ĸ�(��Ϊj����ʮ���Ʊ�ʾ����
	{
		error_site[aa]=j+1;
       aa=aa+1; // %�Ѽ�������㷽�̵ĸ����εĴ���s��
	}
}
//=========================================================================
  int    bb=0;              // %calculate maximum power
     for(int t=n-1;t>=0;t--)          
         if (error_site[t]!=0)
		 {
			 bb=t+1;  //%tָʾ�˴������ʽ���Ĵ�����Ҳ��Ϊ���̸��ĸ�����
            break ;//                          %find maximum power and stop
	 }  
//%==================�ж��Ƿ����==============================
		if ( (Degree_sigma[0]!=bb)||(Degree_sigma[0]>(n-k)/2) ) /// %sigma has no answer or Degree_sigma[0] is overflow
			flag=1;  //   %�в��ɾ��������
		else
		{
			for(int cc=0;cc<=aa-1;cc++) // ����Ϊ��������һ��aa�Լ���һ��
		   {
			   error_site_Dec[cc]=rs_rev(error_site[cc],m,Gal,ind);//% ȡ��Ԫ��
			   error_site[cc]=ind[rs_rev(error_site[cc],m,Gal,ind)-1]+1;//% ��Ԫ�أ�ʮ���ƣ���Ӧ���ݴ���
		   }
			flag=0;
		}
		return flag;
}