#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;
#define N 50
#define M 12

void encode(char bitin[],char code[]);
char decode_error_catch(char r1_code[24],char de_out[24]);//�����Ĳ�������

void main( )
{	                                
	char de_out_catch[24];
	char j=0;

	char input[12]={0,0,0,0,0,0,0,0,0,0,0,0};            /*�������50000����Ϣ��ÿ��Ϊһ����Ϣ*/
	char output[24];           /*����������֣�ÿ��Ϊһ������*/	
		
	unsigned long error_catch=0;	
/*==================���������Ϣ���б��룬���ƽ����Ӳ�о�����======================*/                                                                       	
	encode(input,output);                                             /*�������*/
/*==============================�������뷽ʽ===================================================*/
// 	for (j=0;j<24;j++)
// 	{
// 		//		cout<<de_out_catch[j];
// 		printf("%d",output[j]);
// 	}
// 	cout<<endl;

// 	output[1]=0;
// 	output[2]=0;
// 	output[3]=0;
//	output[16]=0;
	decode_error_catch(output, de_out_catch);                       /*�����������*/
	   
	 for(j=0;j<12;j++)
	 {
		 if(de_out_catch[j]!=output[j])
			error_catch++;                /*���㲶�����������Ԫ�ĸ���*/ 
	 }
	 printf("����ǰ��\r\n");
	 for (j=0;j<12;j++)
	 {
//		 cout<<input[j];
		 printf("%d",input[j]);
	 }
	 cout<<endl;
	 printf("�����\r\n");
	 for (j=0;j<24;j++)
	 {
		 //		cout<<de_out_catch[j];
		 printf("%d",output[j]);
	 }
	cout<<endl;
	printf("�����\r\n");
	for (j=0;j<24;j++)
	{
//		cout<<de_out_catch[j];
		printf("%d",de_out_catch[j]);
	}
	cout<<endl;
	cout<<"���������"<<error_catch<<endl;
}







void encode(
			char bitin[],      /*�����������*/
			char code[]		/*�����������������Ĺ�ϵ code[ 24]={bitin[11]--bitin[0],Reg[10],Reg[0],parity} ����*/
			)      
{	
	char Reg[11]={0};             /*11���Ĵ�����ʼ��Ϊ0*/
	char i=0,j=0,sum=0;                        /*ѭ�����Ʊ���*/
	char charer_value[12];			/*�м�����ڵ�*/
	
	/*=============��������ϵͳ��ĳ˳�����·�õ����¹�ϵ====================================================*/
	for(i=0;i<M;i++)
	{	
		/*�����м�����ڵ������*/
		charer_value[11]=(bitin[M-i-1]+Reg[10])%2;  /*����������ǵ�λ�����룬��bitin[0]��ʾm0*/
		charer_value[10]=charer_value[11];          /*charer_value[11]���ɵ�ǰ���������λ�ͼĴ���Reg[10]���õ�*/
		charer_value[6]=charer_value[10];
		charer_value[5]=charer_value[6];
		charer_value[4]=charer_value[5];
		charer_value[2]=charer_value[4];
		charer_value[0]=charer_value[2];
		/*����Ĵ����ڵ������*/
		Reg[10]=(Reg[9]+charer_value[10])%2;           /*Reg[4]����Reg[3]�����ݺ�charer_value[4]���õ�*/
		Reg[9]=Reg[8];                                        /*Reg[3]����Reg[2]�����ݸ��µõ�*/
		Reg[8]=Reg[7];
		Reg[7]=Reg[6];
		Reg[6]=(Reg[5]+charer_value[6])%2;          /*Reg[2]����Reg[1]�����ݺ�charer_value[2]������µõ�*/
		Reg[5]=(Reg[4]+charer_value[5])%2;
		Reg[4]=(Reg[3]+charer_value[4])%2;
		Reg[3]=Reg[2];											/*Reg[1]����Reg[0]�����ݸ��µõ�*/
		Reg[2]=(Reg[1]+charer_value[2])%2;
		Reg[1]=Reg[0];	
		Reg[0]=charer_value[0];								/*Reg[0]����charer_value[0]�����ݸ��µõ�*/
		/*���㵱ǰ�������ݵı�����*/
		code[i]=bitin[M-i-1];                     /*ÿ�����ֵ���Ϣλֱ�����������Ϣ����*/
		
	}
	/*=====================��M��R-1����ѭ���õ����ֵ�У��λ========================*/
	for(j=0;j<11;j++)
	{	
		code[i]=Reg[10-j];			/*У��λ��������Reg[10]--Reg[0]����*/
		i++;
	}
	for(i=0;i<23;i++)
		sum=sum+code[i];
	code[23]=sum%2;
	
	return;
}


char decode_error_catch(char r1_code[24],char de_out[24]) /*�����Ĳ�������*/
{
	char de_reg[11]={0};
	char r_code[23]={0};
//	char T=0;
	char middle=0;
	char flag=0,sum=0;
	char correct_bit=0;
	char charer[11]={0};
	char weight=0;
	char i=0,j=0,k=0;

/*====================��ȡ���ֵ�ǰ23λ���õ���23��12���걸������===========================*/
	
	for(i=0;i<23;i++)
		r_code[i]=r1_code[i];

/*===================��23λ���������������ʽ�Ĵ���=====================================*/
	
	 for(k=0;k<23;k++)
	{  middle=de_reg[10];                 /*����11λ��������ʱ���Ĵ������������£�����ֵΪmiddle*/

	   de_reg[10]=(middle+de_reg[9])%2;
       de_reg[9]=de_reg[8];
	   de_reg[8]=de_reg[7];
	   de_reg[7]=de_reg[6];
	   de_reg[6]=(de_reg[5]+middle)%2;
	   de_reg[5]=(de_reg[4]+middle)%2;
	   de_reg[4]=(de_reg[3]+middle)%2;
	   de_reg[3]=de_reg[2];
	   de_reg[2]=(de_reg[1]+middle)%2;
	   de_reg[1]=de_reg[0];
	   de_reg[0]=(r_code[k]+middle)%2;
  }                                

/*=================�������ʽ������===============================*/
 f1: for(i=0;i<11;i++)
    weight=weight+de_reg[i]; 

/*==========���ݰ���ʽ��������С�����о�������======================*/
  if(weight<=3)
	{//  T=1;                 /*������ں�11λ����ʽ��ֵ��Ϊ����ͼ��*/
  for(i=0;i<11;i++)
	  charer[i]=de_reg[i];          /*charerֵ��Ϊ����ͼ��*/
  
  }

  else 
  {   weight=0;
	                               /*Q(x)=x^5*/
	  charer[10]=de_reg[10];
	  charer[9]=(de_reg[9]+1)%2;            /*charerֵ��ΪS0-Si��õ��İ���ʽ��ֵ*/
	  charer[8]=(de_reg[8]+1)%2; 
      charer[7]=de_reg[7];
      charer[6]=(de_reg[6]+1)%2;
      charer[5]=(de_reg[5]+1)%2;
      charer[4]=de_reg[4];
      charer[3]=de_reg[3];
      charer[2]=(de_reg[2]+1)%2;
      charer[1]=(de_reg[1]+1)%2;
      charer[0]=de_reg[0];

	  for(i=0;i<11;i++)
		  weight=weight+charer[i];

	  if (weight<=2)
		{ // T=1;
	  r_code[(6+flag)%23]=(r_code[(6+flag)%23]+1)%2;}          /*��Ϣλx^16����*/
	  else
	  {   
		  weight=0;                           /*Q(x)=x^6*/
		  charer[10]=(de_reg[10]+1)%2;
		  charer[9]=(de_reg[9]+1)%2;            /*charerֵ��ΪS0-Si��õ��İ���ʽ��ֵ����11λ�Ĵ���ͼ��*/
		  charer[8]=de_reg[8];
          charer[7]=(de_reg[7]+1)%2;
		  charer[6]=(de_reg[6]+1)%2;
		  charer[5]=de_reg[5];
		  charer[4]=de_reg[4];
		  charer[3]=(de_reg[3]+1)%2;
		  charer[2]=(de_reg[2]+1)%2;
		  charer[1]=de_reg[1];
		  charer[0]=de_reg[0];
		  
		  for(i=0;i<11;i++)
		  weight=weight+charer[i];

		  if(weight<=2)
			{//  T=1;
		  r_code[(5+flag)%23]=(r_code[(5+flag)%23]+1)%2;           /*��Ϣλx^17����*/
		  }
		  else 
			
			{  weight=0;
			   middle=de_reg[10];    /*����3�������������������ʽ�ͻ���ѭ����λһ��*/

	   de_reg[10]=(middle+de_reg[9])%2;
       de_reg[9]=de_reg[8];
	   de_reg[8]=de_reg[7];
	   de_reg[7]=de_reg[6];
	   de_reg[6]=(de_reg[5]+middle)%2;
	   de_reg[5]=(de_reg[4]+middle)%2;
	   de_reg[4]=(de_reg[3]+middle)%2;
	   de_reg[3]=de_reg[2];
	   de_reg[2]=(de_reg[1]+middle)%2;
	   de_reg[1]=de_reg[0];                  
	   de_reg[0]=middle;                       /*�����������ѭ����λ���������ʽ*/
	                                     /*���ڣ�23��12�����������걸�룬�����λ23�Σ�������ɾ�������������3����������*/
		flag=flag+1;             /*��¼ѭ����λ�Ĵ���*/
	  goto f1;
		  }
	  }
  }
  correct_bit=(12+flag)%23;                  /*��ʼ�����λ�ã�11������ĵ�һλ���*/

/*============================�������==================================*/
  for(i=correct_bit,j=10;j>=0;i++,j--)              /*��λ����Ӧ�İ���ʽ��Ϊ����ͼ����r+e����ɵ�����*/
 {
	 r_code[i%23]=(r_code[i%23]+charer[j])%2;
	   
  }
  for(i=0;i<23;i++)
  {
	  de_out[i]=r_code[i];
     sum=sum+de_out[i];
  }

  de_out[23]=sum%2;
/*=================���һ�������Ҫ��������ʽ��Ӱ��===============================*/
  for(i=0;i<11;i++)
  {
  de_reg[i]=0;
  
  }
  return 0;
}


