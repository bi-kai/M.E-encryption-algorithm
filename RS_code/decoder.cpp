#include "RS_head.h"
void decoder(
					int n,//   (n+1)���ƣ����ֵĳ���(2^m)
					int k,//��Ϣλ����
					int m ,//GF(2^m)
					int *Gal,//2^m��Ԫ�ر�
					int *ind,//index ������
					int * syndrome_output,//У��ʽ����Ľ��
					int *receive_from_channel,//��AWGN�ŵ�����Ľ��
					int *Degree_sigma,//sigma�� ����
					int *errorvalue_output,//����ֵ�Ĵ�С
					int decodeK_out[]//��������Ľ��
					)
{
	int decode_out[N]={0};
errorvalue(syndrome_output,N ,K,m,Gal,ind,Degree_sigma,errorvalue_output);
 //=============����ֵ��ȥ����ֵ�õ���ѵĹ�������C^=============================
for(int i=0;i<n;i++)//replace 2^m-1 to n
    decode_out[i]=rs_add(receive_from_channel[i],errorvalue_output[i],m); 
//=================ֱ��ȡ��������ֵĺ�Kλ��Ϊ���������Ϣ����m^=========================
for(int j=n;j>=n-k+1;j--) 
    decodeK_out[j-(n-k)-1]=decode_out[j-1];
}

