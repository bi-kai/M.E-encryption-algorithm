#include "RS_head.h"
void syndrome(
	int *input_receive_from_channel, //���ŵ������ֵ
	int n,//�볤
	int k, //��Ϣλ��
	int m,//GF(2^m)
	int * Gal,//٤�޻���
	int *ind,//������
	int * syndrome_output//���У����
	)//����У��ֵ
{
	for(int i=0;i<=n-k-1;i++)
		syndrome_output[i]=0;
	for(int i=0;i<=n-k-1;i++)
	{
		int  sum=0;
        for(int j=n-1;j>=0;j--) 
			sum=rs_add(sum,rs_mul(Gal[((i+1)*(j)%(int)(pow(2.0,m)-1))],input_receive_from_channel[j],m,Gal,ind),m);
		//%���ﰴ�������HУ��������У��
     syndrome_output[i]=sum;
    }
}

