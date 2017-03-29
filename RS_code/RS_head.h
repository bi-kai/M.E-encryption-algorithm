#ifndef  RS_HEAD_
#define RS_HEAD_
#define N 127  // 码长,这里修改参数
#define K  99 // 信息位长，这里修改参数
#define  M  8   //GF(2^M)
#define  T  (N-K)/2  //  可纠正的错误数目 
#define Rc (215.0)/255  //码率
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
//#define TEST1
//定义一个清零的宏函数
#define  CLEAR(b,start,end){\
	int ci;\
	for(ci=start;ci<=end;ci++){\
	(b)[ci]=0;\
	}\
}
char* Printf_time(); // 打印仿真的时间
void Galoias_generate(int m,int *M_out);  //产生伽罗华域元素
void index(int m,int * Gal,int * index_Gal); // 产生索引表
int rs_mul(int a,int b,int m, int *Gal,int * ind);// 伽罗华域的乘法
int rs_add(int a,int b,int m);//伽罗华域的加法
int rs_rev(int a,int m, int * Gal, int * ind);//伽罗华域的求逆
void de2bi(int input,int m,int *out);  //十进制转化为二进制
int Bi_to_Dec(int *input );//二进制转化为十进制
void rs_Coefficient_Polynomial(int m,int t,int *Gal,int* index,int *Coefficient_Polynomial);//RS码的生成多项式
void encoder(int *input,int n ,int k, int m,int * Gal,int *ind,int *Coefficient_Polynomial,int *output);//依据g(x)进行编码
void syndrome(int *input_receive_from_channel, int n ,int k, int m,int * Gal,int * ind,int * syndrome_output);//计算校验子
void errorpoly(int * input_syndrome, int n ,int k, int m,int * Gal,int * ind,int sigma[][N-K+1],int *Degree_sigma) ; //求解错位多项式
int errorsite(int *input_syndrome, int n ,int k, int m,int * Gal,int *ind,int *error_site,int sigma[][N-K+1],int *Degree_sigma,int error_site_Dec[]);//求解错误位置
int errorvalue(int * input_syndrome, int n ,int k, int m,int * Gal,int * ind,int *Degree_sigma,int * errorvalue_output);//求解错误值大小
void decoder(int n,int k,int m ,int *Gal,int *ind,int * syndrome_output,int *receive_from_channel,int *Degree_sigma,int *errorvalue_output,int decodeK_out[]);//译码器
void channel(
					double SNR,/*SNR是dB形式的*/
					int * coded_data/*传入输入的码字，经过这个函数后，是经过BPSK和Gauss噪声后硬判决的结果*/
					);
#endif