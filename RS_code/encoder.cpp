#include "RS_head.h"
void encoder(
	int *input, //�����������
	int n ,//�볤
	int k, //��Ϣλ��
	int m,//GF(2^m)
	int * Gal,//٤�޻�Ԫ�ر�
	int *ind,//������
	int *Coefficient_Polynomial,
	int * output
	)
{
	//%����ʽ��ϵ���������������磨14 3 21 15 29 15 16 20 25 24  2  8 13 1 28 15  1��
	int Reg[N-K]={0}; //%n=30,k=14���ݴ�16��У��λ
	int  message[K]={0};// %k=14�ݴ���Ϣλ
	int feedback=0;
	for (int i=0;i<k;i++)
	{
		feedback=rs_add(input[k-i-1],Reg[n-k-1],m);//% ��Ϣλ�ɸ�λ����λ����Ĵ�����input�����λ�ں��棩
		for(int j=n-k;j>=2;j--) //j=n-k:-1:2    %n-k=16  ���θ���Reg��15����Reg��0���Ĵ���������
		  { 
			  if(Coefficient_Polynomial[j-1]!=0)
				  Reg[j-1]=rs_add(Reg[j-2],rs_mul(Coefficient_Polynomial[j-1],feedback,m,Gal,ind),m);
				 // %��j���Ĵ����������ɣ���һ���Ĵ��������ݣ����ϣ���j��ϵ�����Է���ֵ��
			  else
				  Reg[j-1]=Reg[j-2];//%������ɶ���ʽ�ĵ�j��ϵ��Ϊ0����j���Ĵ�����ֱֵ������һ���Ĵ�����ֵ�õ�
		  }  
      Reg[0]=rs_mul(Coefficient_Polynomial[0],feedback,m,Gal,ind);//%Reg��1����ֱֵ����Coefficient_Polynomial(1)��feedback�õ�
	}
for(int p=0;p<k;p++)  
    message[p]=input[p];
	for(int p=0;p<n;p++)
	{	
		if(p<(N-K))
	output[p]=Reg[p];//%����Ľ���ߴ����ں��棬�ʹ�����ǰ��
		else 
		output[p]=message[p-(N-K)];
	}
}             