#include "RS_head.h"
//===================================Gauss channel ===============================================
//==================产生服从高斯分布的随机数=====================================================
double GaussNoise(double sigma)
{			// sigma -- standard deviation of Gaussian noise
    int num;            // total number of random to generate gaussRand
    double sum;         // sum of uniformly distributed random number
    double gaussRand;
    double mean = 0.0;  // mean of Gaussian noise
sum = 0.0;
    num =12;
// compute sum of 12 uniform random number
    for (int i = 0; i < num; i++)
	sum += (double)rand()/RAND_MAX;
    gaussRand = sigma * (sum - num/2.0) *sqrt((double)num / 12.0) + mean;
	///根据大数定理产生Gauss 随机数//
    return gaussRand;
}

void channel(
					double SNR,/*SNR是dB形式的*/
					int *coded_data/*传入输入的码字，经过这个函数后，是经过BPSK和Gauss噪声后硬判决的结果*/
					)
{
	double * transfered_data= new double[N*M];
	/*动态分配NN*8=2040个double型储存单元，首地址赋给transfered_data*/
	double Eb_N0, sigma;
	int i;
	Eb_N0 = pow(10.0, 0.1*SNR);/*将分贝dB形式的SNR转化成一般形式*/
	sigma =sqrt(1.0 /(2*Rc) /Eb_N0); /*求出噪声方差*/
	/*==============modulate signal  by BPSK method and add Gauss noise=========================*/
	for(i=0; i<N*M; i++)
		transfered_data[i] =(1-2*coded_data[i]) + GaussNoise(sigma);
	 /*=======================hard detector==============================*/
	for(i = 0; i < N*M; i ++)
	{
		if(transfered_data[i] < 0)
			coded_data[i] = 1;
		else
			coded_data[i] = 0;                 //hard detector
	}
delete [] transfered_data;/*free the space*/
}

