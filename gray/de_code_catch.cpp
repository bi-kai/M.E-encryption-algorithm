#include<iostream>
using namespace std;
int decode_error_catch(int r1_code[24],int de_out[24]) /*�����Ĳ�������*/
{
	int de_reg[11]={0};
	int r_code[23]={0};
	int T=0;
	int middle=0;
	int flag=0,sum=0;
	int correct_bit=0;
	int inter[11]={0};
	int weight=0;
	int i=0,j=0,k=0;

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
	{  T=1;                 /*������ں�11λ����ʽ��ֵ��Ϊ����ͼ��*/
  for(i=0;i<11;i++)
	  inter[i]=de_reg[i];          /*interֵ��Ϊ����ͼ��*/
  
  }

  else 
  {   weight=0;
	                               /*Q(x)=x^5*/
	  inter[10]=de_reg[10];
	  inter[9]=(de_reg[9]+1)%2;            /*interֵ��ΪS0-Si��õ��İ���ʽ��ֵ*/
	  inter[8]=(de_reg[8]+1)%2; 
      inter[7]=de_reg[7];
      inter[6]=(de_reg[6]+1)%2;
      inter[5]=(de_reg[5]+1)%2;
      inter[4]=de_reg[4];
      inter[3]=de_reg[3];
      inter[2]=(de_reg[2]+1)%2;
      inter[1]=(de_reg[1]+1)%2;
      inter[0]=de_reg[0];

	  for(i=0;i<11;i++)
		  weight=weight+inter[i];

	  if (weight<=2)
		{  T=1;
	  r_code[(6+flag)%23]=(r_code[(6+flag)%23]+1)%2;}          /*��Ϣλx^16����*/
	  else
	  {   
		  weight=0;                           /*Q(x)=x^6*/
		  inter[10]=(de_reg[10]+1)%2;
		  inter[9]=(de_reg[9]+1)%2;            /*interֵ��ΪS0-Si��õ��İ���ʽ��ֵ����11λ�Ĵ���ͼ��*/
		  inter[8]=de_reg[8];
          inter[7]=(de_reg[7]+1)%2;
		  inter[6]=(de_reg[6]+1)%2;
		  inter[5]=de_reg[5];
		  inter[4]=de_reg[4];
		  inter[3]=(de_reg[3]+1)%2;
		  inter[2]=(de_reg[2]+1)%2;
		  inter[1]=de_reg[1];
		  inter[0]=de_reg[0];
		  
		  for(i=0;i<11;i++)
		  weight=weight+inter[i];

		  if(weight<=2)
			{  T=1;
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
	 r_code[i%23]=(r_code[i%23]+inter[j])%2;
	   
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