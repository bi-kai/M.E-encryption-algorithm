 
#include <iostream>
#include "FEC.h"
using namespace std;
#define N 50000 
int codeword[4096][24];

int m_deM_sd(int en_code[24],int m_code[24],int dem_code[24],double sigma);
void main( )
{	FILE *fp;
char filename[20];


	int input_error=0,                             /*输入错误时的指示*/
		code[24]={0},                           /*生成的码字  m(11)--m(0),check(10)--check(0),parity*/
		bitin[M]={0};                        /*待编码的信息  m(0)--m(11)*/
	                                
	int de_out_catch[N][24];

	int i=0,j=0,k=0;

	int G[12][23]={0};
	int H[11][23]={0};
	int input[N][12];             /*随机产生50000个信息，每行为一个信息*/
	int output[N][24];           /*输出编码码字，每行为一个码字*/	
		
	int m_code[N][24];
	int dem_code_h[N][24]={0};
	double  sigma=0;
	

	int snr_dB=0;
	unsigned long error_catch[13]={0};
	double long pe_catch[13]={0};

	
	
/*===========================计算(23,12)Golay系统码的生成矩阵G（I，P）======================================*/
	
	for (i=M-1;i>=0;i--)
	{
	bitin[i]=1;                /*bitin[i]=1,其它位为0时，得到一个码字，作为生成矩阵的第i行*/
	encode(bitin,code);
	bitin[i]=0;
	for(j=0;j<23;j++)
	
		G[M-1-i][j]=code[j];
		cout<<endl;
	}
	cout<<"the Matrix of G is"<<endl;
	for(i=0;i<12;i++)
		{
			for(j=0;j<23;j++)
			cout<<G[i][j]<<" ";
	     cout<<endl;
	}
/*=====================由生成矩阵G得到校验矩阵H（P，I）========================*/
	cout<<"the Matrix of H is"<<endl;
	for(i=0;i<11;i++)
	{
		H[i][i+12]=1;}
	for(i=0;i<12;i++)
	{
		for(j=0;j<11;j++)
	   H[j][i]=G[i][j+12];
	    }
	
	for(i=0;i<11;i++)
		{
			for(j=0;j<23;j++)
			cout<<H[i][j]<<" ";
      cout<<endl;
	}		
	                       
  
	
/*==================对输入的信息进行编码，调制解调，硬判决译码======================*/

	printf("please input the file name:");
	scanf("%s",filename);

	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("cannot open this file \n");
		exit(0);
	}
	fclose(fp);


	k=0;
	srand((unsigned)time(NULL));                 /*返回系统时间作为种子*/
for(snr_dB=0;snr_dB<13;snr_dB=snr_dB+1)           /*设置信噪比的dB值*/
{
	sigma=sqrt(1.0/pow(10.0,0.1*snr_dB));                  /*高斯白噪声的标准差*/
	cout<<"sigma= "<<sigma<<endl;
	
for(i=0;i<N;i++)
	{ 
	   {
		for(j=0;j<12;j++)
	    {		
	input[i][j]=rand()%2;                /*输入的序列是否随机？？？*/
	    }                                                                                 
	
	encode(input[i],output[i]);                                             /*编码输出*/
 m_deM( output[i], m_code[i], dem_code_h[i], sigma);                  /*硬判决调制解调*/


/*==============================三种译码方式===================================================*/
  
 decode_error_catch( dem_code_h[i], de_out_catch[i]);                       /*捕错译码输出*/
  //decode_golay( dem_code_h[i], de_out_std[i], H);                      /*标准阵列译码*/
	//decode_soft_sd( dem_code_sd[i], de_out_sd[i]);                  /*最小软距离译码*/
  


	   
 for(j=0;j<12;j++)
 {
	 if(de_out_catch[i][j]!=output[i][j])
	 error_catch[k]=error_catch[k]+1;                /*计算捕错译码错误码元的个数*/
 
 }
}
}
pe_catch[k]=error_catch[k]/(double)(N*12.0);                 /*捕错译码误码率*/

 printf("when SNR_dB = %ddB, the error catch BER = %e\n", snr_dB, pe_catch[k]);
 
 		
  /*=======================写到filename文件中=======================*/
			if((fp=fopen(filename,"a+"))==NULL)
			{
				printf("cannot open this file \n");
				exit(0);
			}
			fprintf(fp, "%ddB\t%e\n", snr_dB, pe_catch[k]);			
			
			fclose(fp);

cout<<"The error catch number of bits is"<<"  "<<error_catch[k]<<"    ";/*捕错译码错误码元的个数*/
cout<<"The error ratio is "<<" "<<pe_catch[k]<<"  "  ;            /*输出误码率*/	
k++;
cout<<endl;
}

 return;
}




		


