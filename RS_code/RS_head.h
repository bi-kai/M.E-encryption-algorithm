#ifndef  RS_HEAD_
#define RS_HEAD_
#define N 127  // �볤,�����޸Ĳ���
#define K  99 // ��Ϣλ���������޸Ĳ���
#define  M  8   //GF(2^M)
#define  T  (N-K)/2  //  �ɾ����Ĵ�����Ŀ 
#define Rc (215.0)/255  //����
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//#define TEST1
//����һ������ĺ꺯��
#define  CLEAR(b,start,end){\
	int ci;\
	for(ci=start;ci<=end;ci++){\
	(b)[ci]=0;\
	}\
}
char* Printf_time(); // ��ӡ�����ʱ��
void Galoias_generate(int m,int *M_out);  //����٤�޻���Ԫ��
void index(int m,int * Gal,int * index_Gal); // ����������
int rs_mul(int a,int b,int m, int *Gal,int * ind);// ٤�޻���ĳ˷�
int rs_add(int a,int b,int m);//٤�޻���ļӷ�
int rs_rev(int a,int m, int * Gal, int * ind);//٤�޻��������
void de2bi(int input,int m,int *out);  //ʮ����ת��Ϊ������
int Bi_to_Dec(int *input );//������ת��Ϊʮ����
void rs_Coefficient_Polynomial(int m,int t,int *Gal,int* index,int *Coefficient_Polynomial);//RS������ɶ���ʽ
void encoder(int *input,int n ,int k, int m,int * Gal,int *ind,int *Coefficient_Polynomial,int *output);//����g(x)���б���
void syndrome(int *input_receive_from_channel, int n ,int k, int m,int * Gal,int * ind,int * syndrome_output);//����У����
void errorpoly(int * input_syndrome, int n ,int k, int m,int * Gal,int * ind,int sigma[][N-K+1],int *Degree_sigma) ; //����λ����ʽ
int errorsite(int *input_syndrome, int n ,int k, int m,int * Gal,int *ind,int *error_site,int sigma[][N-K+1],int *Degree_sigma,int error_site_Dec[]);//������λ��
int errorvalue(int * input_syndrome, int n ,int k, int m,int * Gal,int * ind,int *Degree_sigma,int * errorvalue_output);//������ֵ��С
void decoder(int n,int k,int m ,int *Gal,int *ind,int * syndrome_output,int *receive_from_channel,int *Degree_sigma,int *errorvalue_output,int decodeK_out[]);//������
void channel(
					double SNR,/*SNR��dB��ʽ��*/
					int * coded_data/*������������֣���������������Ǿ���BPSK��Gauss������Ӳ�о��Ľ��*/
					);
#endif