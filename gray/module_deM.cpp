#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<fstream>

using namespace std;

double GaussRand(double sigma);

int m_deM(int en_code[24],int m_code[24],int dem_code[24],double sigma)
{
	int i=0,j=0;
	double add_noise[24];
	for(i=0;i<24;i++)
	{	m_code[i]=2*en_code[i]-1;//BPSK调制，0变为-1，1变为1
	add_noise[i]=m_code[i]+GaussRand(sigma);
	
	if(add_noise[i]>=0)
		dem_code[i]=1;
	else dem_code[i]=0; 
	}
	
	return 0;
}





double GaussRand(double sigma)
{
	int num;            // total number of random to generate gaussRand
    double sum;         // sum of uniformly distributed random number
    double gaussRand;
    double mean = 0.0;  // mean of Gaussian noise
	
    sum = 0.0;
    num = 12;
	
    // compute sum of 12 uniform random number
    for (int i = 0; i < num; i++)
		sum+= rand()/(double)RAND_MAX;
	
    gaussRand=sigma*(sum-num/2.0)/(double)sqrt(num / 12.0)+mean;
	/*根据大数定理产生Gauss 随机数*/
    return gaussRand;
	
}



