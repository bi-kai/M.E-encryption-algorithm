#include "RS_head.h"
void decoder(
					int n,//   (n+1)进制，码字的长度(2^m)
					int k,//信息位长度
					int m ,//GF(2^m)
					int *Gal,//2^m个元素表
					int *ind,//index 索引表
					int * syndrome_output,//校验式输出的结果
					int *receive_from_channel,//从AWGN信道输出的结果
					int *Degree_sigma,//sigma的 次数
					int *errorvalue_output,//错误值的大小
					int decodeK_out[]//译码输出的结果
					)
{
	int decode_out[N]={0};
errorvalue(syndrome_output,N ,K,m,Gal,ind,Degree_sigma,errorvalue_output);
 //=============接受值减去错误值得到最佳的估计码字C^=============================
for(int i=0;i<n;i++)//replace 2^m-1 to n
    decode_out[i]=rs_add(receive_from_channel[i],errorvalue_output[i],m); 
//=================直接取出最佳码字的后K位，为最佳译码信息序列m^=========================
for(int j=n;j>=n-k+1;j--) 
    decodeK_out[j-(n-k)-1]=decode_out[j-1];
}

