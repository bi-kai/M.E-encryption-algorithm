#include <iostream>
using namespace std;
#define M 12
void encode(
			int bitin[],      /*�����������*/
			int code[]		/*�����������������Ĺ�ϵ code[ 24]={bitin[11]--bitin[0],Reg[10],Reg[0],parity} ����*/
			)      
{	
	int Reg[11]={0};             /*11���Ĵ�����ʼ��Ϊ0*/
	int i=0,j=0,sum=0;                        /*ѭ�����Ʊ���*/
	int Inter_value[12];			/*�м�����ڵ�*/
	
	/*=============��������ϵͳ��ĳ˳�����·�õ����¹�ϵ====================================================*/
	for(i=0;i<M;i++)
	{	
		/*�����м�����ڵ������*/
		Inter_value[11]=(bitin[M-i-1]+Reg[10])%2;  /*����������ǵ�λ�����룬��bitin[0]��ʾm0*/
		Inter_value[10]=Inter_value[11];          /*Inter_value[11]���ɵ�ǰ���������λ�ͼĴ���Reg[10]���õ�*/
		Inter_value[6]=Inter_value[10];
		Inter_value[5]=Inter_value[6];
		Inter_value[4]=Inter_value[5];
		Inter_value[2]=Inter_value[4];
		Inter_value[0]=Inter_value[2];
		/*����Ĵ����ڵ������*/
		Reg[10]=(Reg[9]+Inter_value[10])%2;           /*Reg[4]����Reg[3]�����ݺ�Inter_value[4]���õ�*/
		Reg[9]=Reg[8];                                        /*Reg[3]����Reg[2]�����ݸ��µõ�*/
		Reg[8]=Reg[7];
		Reg[7]=Reg[6];
		Reg[6]=(Reg[5]+Inter_value[6])%2;          /*Reg[2]����Reg[1]�����ݺ�Inter_value[2]������µõ�*/
		Reg[5]=(Reg[4]+Inter_value[5])%2;
		Reg[4]=(Reg[3]+Inter_value[4])%2;
		Reg[3]=Reg[2];											/*Reg[1]����Reg[0]�����ݸ��µõ�*/
		Reg[2]=(Reg[1]+Inter_value[2])%2;
		Reg[1]=Reg[0];	
		Reg[0]=Inter_value[0];								/*Reg[0]����Inter_value[0]�����ݸ��µõ�*/
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