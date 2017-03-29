#include "RS_head.h"
//===================================Gauss channel ===============================================
//==================�������Ӹ�˹�ֲ��������=====================================================
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
	///���ݴ����������Gauss �����//
    return gaussRand;
}

void channel(
					double SNR,/*SNR��dB��ʽ��*/
					int *coded_data/*������������֣���������������Ǿ���BPSK��Gauss������Ӳ�о��Ľ��*/
					)
{
	double * transfered_data= new double[N*M];
	/*��̬����NN*8=2040��double�ʹ��浥Ԫ���׵�ַ����transfered_data*/
	double Eb_N0, sigma;
	int i;
	Eb_N0 = pow(10.0, 0.1*SNR);/*���ֱ�dB��ʽ��SNRת����һ����ʽ*/
	sigma =sqrt(1.0 /(2*Rc) /Eb_N0); /*�����������*/
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

