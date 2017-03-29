#include <iostream>
using namespace std;
#define M 12
void encode(
			int bitin[],      /*待编码的数据*/
			int code[]		/*编码后的数据有这样的关系 code[ 24]={bitin[11]--bitin[0],Reg[10],Reg[0],parity} 构成*/
			)      
{	
	int Reg[11]={0};             /*11个寄存器初始化为0*/
	int i=0,j=0,sum=0;                        /*循环控制变量*/
	int Inter_value[12];			/*中间变量节点*/
	
	/*=============根据生成系统码的乘除法电路得到以下关系====================================================*/
	for(i=0;i<M;i++)
	{	
		/*计算中间变量节点的数据*/
		Inter_value[11]=(bitin[M-i-1]+Reg[10])%2;  /*输入的数据是低位先输入，即bitin[0]表示m0*/
		Inter_value[10]=Inter_value[11];          /*Inter_value[11]是由当前输入的数据位和寄存器Reg[10]异或得到*/
		Inter_value[6]=Inter_value[10];
		Inter_value[5]=Inter_value[6];
		Inter_value[4]=Inter_value[5];
		Inter_value[2]=Inter_value[4];
		Inter_value[0]=Inter_value[2];
		/*计算寄存器节点的数据*/
		Reg[10]=(Reg[9]+Inter_value[10])%2;           /*Reg[4]是由Reg[3]的数据和Inter_value[4]异或得到*/
		Reg[9]=Reg[8];                                        /*Reg[3]是由Reg[2]的数据更新得到*/
		Reg[8]=Reg[7];
		Reg[7]=Reg[6];
		Reg[6]=(Reg[5]+Inter_value[6])%2;          /*Reg[2]是由Reg[1]的数据和Inter_value[2]异或后更新得到*/
		Reg[5]=(Reg[4]+Inter_value[5])%2;
		Reg[4]=(Reg[3]+Inter_value[4])%2;
		Reg[3]=Reg[2];											/*Reg[1]是由Reg[0]的数据更新得到*/
		Reg[2]=(Reg[1]+Inter_value[2])%2;
		Reg[1]=Reg[0];	
		Reg[0]=Inter_value[0];								/*Reg[0]是由Inter_value[0]的数据更新得到*/
		/*计算当前输入数据的编码结果*/
		code[i]=bitin[M-i-1];                     /*每个码字的信息位直接由输入的信息构成*/
		
	}
	/*=====================后M（R-1）次循环得到码字的校验位========================*/
	for(j=0;j<11;j++)
	{	
		code[i]=Reg[10-j];			/*校验位是由最后的Reg[10]--Reg[0]构成*/
		i++;
	}
	for(i=0;i<23;i++)
		sum=sum+code[i];
	code[23]=sum%2;
	
	return;
}