#include "RS_head.h"
int Bi_to_Dec(int *input )// 二进制转化为十进制
{
	int Dec_sum=0;
	for(int i=0;i<M;i++)
		if(input[i]==1)
		Dec_sum=Dec_sum+pow(2.0,i);
	return Dec_sum;
}

void Galoias_generate(int m,int *M_out)
{
	#if(M == 2)
/*本原多项式 1 + x + x^2 */
int Primitive_polynomial[M+1] = { 1, 1, 1 };

#elif(M == 3)
/* 本原多项式1 + x + x^3 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 1 };

#elif(M == 4)
/* 本原多项式 1 + x + x^4 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 0, 1 };

#elif(M == 5)
/* 本原多项式1 + x^2 + x^5 */
int Primitive_polynomial[M+1] = { 1, 0, 1, 0, 0, 1 };

#elif(M == 6)
/* 本原多项式1 + x + x^6 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 0, 0, 0, 1 };

#elif(M == 7)
/* 本原多项式1 + x^3 + x^7 */
int Primitive_polynomial[M+1] = { 1, 0, 0, 1, 0, 0, 0, 1 };

#elif(M == 8)
/*本原多项式 1+x^2+x^3+x^4+x^8 */
int Primitive_polynomial[M+1] = { 1, 0, 1, 1, 1, 0, 0, 0, 1 };

#elif(M == 9)
/* 本原多项式1+x^4+x^9 */
int Primitive_polynomial[M+1] = { 1, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

#elif(M == 10)
/*本原多项式 1+x^3+x^10 */
int Primitive_polynomial[M+1] = { 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 };

#elif(M == 11)
/* 本原多项式1+x^2+x^11 */
int Primitive_polynomial[M+1] = { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

#elif(M == 12)
/* 1+x+x^4+x^6+x^12 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 };

#elif(M == 13)
/* 本原多项式1+x+x^3+x^4+x^13 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

#elif(M == 14)
/*本原多项式 1+x+x^6+x^10+x^14 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 };

#elif(M == 15)
/* 本原多项式1+x+x^15 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

#elif(M == 16)
/* 本原多项式1+x+x^3+x^12+x^16 */
int Primitive_polynomial[M+1] = { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 };

#else
#error "M must be in range 2-16"
#endif

	int temp[M]= {0};
	for(int i=0;i<pow(2.0,m);i++)
		M_out[i]=0;
	    M_out[0]=1;
		temp[0]=1;
	// Polynomial(m,Primitive_polynomial);
	 for(int i=1;i<pow(2.0,m);i++)
	 {
		if(temp[m-1]==0)
		{
			for(int j=m-2;j>=0;j--)
				temp[j+1]=temp[j];
			temp[0]=0;
		}
		else if(temp[m-1]==1)
		{
			for(int j=m-2;j>=0;j--)
				temp[j+1]=temp[j];
			temp[0]=0;
			for(int p=0;p<m;p++)
			{
				temp[p]=Primitive_polynomial[p]^temp[p];
			}
		}
		 M_out[i]= Bi_to_Dec(temp);	
	 }
}