#include "RS_head.h"
    int errorvalue(
	int * input_syndrome, //����У����
	int n ,//�볤
	int k, //��Ϣλ����
	int m,//GF(2^m)
	int * Gal,//٤�޻���Ԫ��
	int * ind,//������
	int *Degree_sigma,//sigma�Ķ�
	int * errorvalue_output//����ֵ��С
	)// ����ֵ����1ʱ����ʾ���ֲ��ɾ����Ĵ���0��ʾ������������
{
	int error_site[N]={0};
	int sigma[N-K+2][N-K+1]={0};
	int error_site_Dec[N-K+1]={0};
	int sigmaji[N-K+1][N-K+1]={0};
	int flag=0;int flag_errorvalue=0;
	flag=errorsite(input_syndrome, n ,k,m, Gal,ind,error_site,sigma,Degree_sigma,error_site_Dec);
// error_site_Decָʾ�˴�λλ�ӣ�ʮ���ƣ�,S����λλ�ӣ�ʮ���ƣ���Ӧ���ݴ�������Ϊ�ڼ�λ�д�
	//Degree_sigma[0]�Ƕ���ʽ����ߴ�����flag ָʾ�����޲��ɾ���
	if (flag==1)  //flag=1 ָʾ���в��ɾ�������ֱֵ�Ӹ�Ϊ0
	{
		for(int p=0;p<n;p++)  
			errorvalue_output[p]=0; 
		flag_errorvalue=1;
	} 
    else //       flag=0 ָʾ���޲��ɾ���
	{
		for(int p=0;p<N-K+1;p++)
		 sigmaji[p][0]=1;//%sigmaji�ĳ�ʼ��
	//==================���վ�����287--7.5.31��ʽ����sigmaji====================
		if (error_site[0]!=0)
		  for(int j=0;j<=Degree_sigma[0]-1;j++)
			 for(int i=0;i<=Degree_sigma[0]-1;i++)
				  sigmaji[j][i+1]=rs_add(sigma[n-k+1][i+1],rs_mul(sigmaji[j][i],error_site_Dec[j],m,Gal,ind),m);
	//===================���վ�����287--7.5.32��ʽ����Yj======================
		 for(int j=0;j<=Degree_sigma[0]-1;j++)// % һ����Degree_sigma[0]����������  
			 {
				 int  sum1=0;
			   int sum2=0;
					for(int i=0;i<=Degree_sigma[0]-1;i++)//  for i=1:Degree_sigma[0]
				   {
					   sum1=rs_add(sum1,rs_mul(sigmaji[j][i],input_syndrome[Degree_sigma[0]-1-(i)],m,Gal,ind),m);
					   //%������287--7.5.32��ʽ�ķ��Ӳ���
					   sum2=rs_add(sum2,rs_mul(sigmaji[j][i],Gal[(ind[error_site_Dec[j]-1]*(Degree_sigma[0]-(i)))%((int)pow(2.0,m)-1)],m,Gal,ind),m);
					   //%������287--7.5.32��ʽ�ķ�ĸ����
				   }
				   errorvalue_output[error_site[j]-1]=rs_mul(sum1,rs_rev(sum2,m,Gal,ind),m,Gal,ind);//% ���յ�Yjֵ
			}
		 flag_errorvalue=0;
	}
	return  flag_errorvalue;
}
