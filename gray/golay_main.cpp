 
#include <iostream>
#include "FEC.h"
using namespace std;
#define N 50000 
int codeword[4096][24];

int m_deM_sd(int en_code[24],int m_code[24],int dem_code[24],double sigma);
void main( )
{	FILE *fp;
char filename[20];


	int input_error=0,                             /*�������ʱ��ָʾ*/
		code[24]={0},                           /*���ɵ�����  m(11)--m(0),check(10)--check(0),parity*/
		bitin[M]={0};                        /*���������Ϣ  m(0)--m(11)*/
	                                
	int de_out_catch[N][24];

	int i=0,j=0,k=0;

	int G[12][23]={0};
	int H[11][23]={0};
	int input[N][12];             /*�������50000����Ϣ��ÿ��Ϊһ����Ϣ*/
	int output[N][24];           /*����������֣�ÿ��Ϊһ������*/	
		
	int m_code[N][24];
	int dem_code_h[N][24]={0};
	double  sigma=0;
	

	int snr_dB=0;
	unsigned long error_catch[13]={0};
	double long pe_catch[13]={0};

	
	
/*===========================����(23,12)Golayϵͳ������ɾ���G��I��P��======================================*/
	
	for (i=M-1;i>=0;i--)
	{
	bitin[i]=1;                /*bitin[i]=1,����λΪ0ʱ���õ�һ�����֣���Ϊ���ɾ���ĵ�i��*/
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
/*=====================�����ɾ���G�õ�У�����H��P��I��========================*/
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
	                       
  
	
/*==================���������Ϣ���б��룬���ƽ����Ӳ�о�����======================*/

	printf("please input the file name:");
	scanf("%s",filename);

	if((fp=fopen(filename,"a+"))==NULL)
	{
		printf("cannot open this file \n");
		exit(0);
	}
	fclose(fp);


	k=0;
	srand((unsigned)time(NULL));                 /*����ϵͳʱ����Ϊ����*/
for(snr_dB=0;snr_dB<13;snr_dB=snr_dB+1)           /*��������ȵ�dBֵ*/
{
	sigma=sqrt(1.0/pow(10.0,0.1*snr_dB));                  /*��˹�������ı�׼��*/
	cout<<"sigma= "<<sigma<<endl;
	
for(i=0;i<N;i++)
	{ 
	   {
		for(j=0;j<12;j++)
	    {		
	input[i][j]=rand()%2;                /*����������Ƿ����������*/
	    }                                                                                 
	
	encode(input[i],output[i]);                                             /*�������*/
 m_deM( output[i], m_code[i], dem_code_h[i], sigma);                  /*Ӳ�о����ƽ��*/


/*==============================�������뷽ʽ===================================================*/
  
 decode_error_catch( dem_code_h[i], de_out_catch[i]);                       /*�����������*/
  //decode_golay( dem_code_h[i], de_out_std[i], H);                      /*��׼��������*/
	//decode_soft_sd( dem_code_sd[i], de_out_sd[i]);                  /*��С���������*/
  


	   
 for(j=0;j<12;j++)
 {
	 if(de_out_catch[i][j]!=output[i][j])
	 error_catch[k]=error_catch[k]+1;                /*���㲶�����������Ԫ�ĸ���*/
 
 }
}
}
pe_catch[k]=error_catch[k]/(double)(N*12.0);                 /*��������������*/

 printf("when SNR_dB = %ddB, the error catch BER = %e\n", snr_dB, pe_catch[k]);
 
 		
  /*=======================д��filename�ļ���=======================*/
			if((fp=fopen(filename,"a+"))==NULL)
			{
				printf("cannot open this file \n");
				exit(0);
			}
			fprintf(fp, "%ddB\t%e\n", snr_dB, pe_catch[k]);			
			
			fclose(fp);

cout<<"The error catch number of bits is"<<"  "<<error_catch[k]<<"    ";/*�������������Ԫ�ĸ���*/
cout<<"The error ratio is "<<" "<<pe_catch[k]<<"  "  ;            /*���������*/	
k++;
cout<<endl;
}

 return;
}




		


