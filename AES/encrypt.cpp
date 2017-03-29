#include<stdio.h>
#include<stdlib.h>
#include "encrypt.h"

extern unsigned char state[4][4];
unsigned char expandedkey[176],temp[4][4],key[4][4];		//将状态矩阵与轮密钥设置为全局变量
void Encrypt(unsigned char state[4][4],const unsigned char cipherkey[16])
{
	int i,j,k;
	unsigned char expandedkey1[16],temp[4][4];	
	KeyExpansion(cipherkey,expandedkey);	//通过函数调用，密钥扩展获取扩展密钥
	/************取出expandedkey[176]的前16个元素****************/
	for(i=0; i<16; i++)
		expandedkey1[i]=expandedkey[i];
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			temp[i][j]=expandedkey1[i+(j<<2)];
	RoundKeyAddition(state,temp);		//函数调用，第一轮的初始轮密钥加
	/***********进行轮变换**************/
	for(i=1; i<10; i++)
	{
		ByteSub(state);
		ShiftRow(state);
		MixColumn(state);
		for(j=0; j<16; j++)
			expandedkey1[j]=expandedkey[(i<<4)+j];
		for(j=0; j<4; j++)
			for(k=0; k<4; k++)
				temp[j][k]=expandedkey1[j+(k<<2)];
		RoundKeyAddition(state,temp);
	}
	/**********最后一轮的轮运算***********/
	ByteSub(state);
	ShiftRow(state);
	for(i=0; i<16; i++)
		expandedkey1[i]=expandedkey[160+i];
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			temp[i][j]=expandedkey1[i+(j<<2)];
	RoundKeyAddition(state,temp);
/*	printf("The matrix of state after Encryption is: \n");
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(state[i][j]<16)
				printf("0%x ",state[i][j]);
			else
				printf("%x ",state[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/
}
void KeyExpansion(const unsigned char cipherkey[16],unsigned char enpandedkey[176])
{
	int i,j,k,l;
	static unsigned char temp[4];
	unsigned char Rcon[4]={1,0,0,0};
	for(i=0; i<16; i++)
		expandedkey[i]=cipherkey[i];
	for(i=16; i<176; i+=16)
	{
		for(l=0; l<4; l++)
			temp[l]=expandedkey[i-4+l];		//四个字节一组进行移位字节替换运算
		RotSub(temp);//函数调用，进行循环左移然后字节替换
		for(l=0; l<4; l++)
			temp[l]^=expandedkey[i-16+l];//与前一块的首字的四个字节进行异或运算
		/**********将与前一块首字异或的结果与每一轮轮常数进行异或*************/
		Rcon[0]<<=((i>>4)-1);		//对每一次循环的Rcon[0]进行重新计算
		if((i>>4)>8)
			Rcon[0]=27<<((i>>4)-9);//对于i/16大于8之后的数用x^4+x^3+x+1来代替x^8
		for(l=1; l<4; l++)
			Rcon[l]=0;
		for(l=0; l<4; l++)
			temp[l]^=Rcon[l];
		Rcon[0]=1;
		for(j=0; j<4; j++)
		{
			expandedkey[i+j] = temp[j];		//获取4个字为一块的首字
			temp[j] = 0;					//对暂存字节的临时数组重新置零
		}
		for(k=i+4; k<(i+16); k++)
			expandedkey[k]=expandedkey[k-4]^expandedkey[k-16];
	}
}
void RotSub(unsigned char temp[4])
{
	int i;
	int row,column;
	//左循环一个字节
	unsigned char b=temp[0];
	for(i=0; i<3; i++)
		temp[i]=temp[(i+1)&0x03];//一个字中的四个字节进行循环左移
	temp[3]=b;
	//字节替换
	for(i=0; i<4; i++)
	{
		row = temp[i] >> 4;
		column = temp[i] & 0x0f;
		temp[i] = sbox[row][column];
	}
}
void ByteSub(unsigned char state[4][4])
{
	int i,j;
	int row,column;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			row = state[i][j] >> 4;
			column = state[i][j] & 0x0f;
			state[i][j] = sbox[row][column];
		}
}
void ShiftRow(unsigned char state[4][4])
{
	int i,j;
	char temp1[4][4];
	for(i=1; i<4; i++)
	{
		for(j=0; j<4; j++)
			temp1[i][j]=state[i][j];			//将状态矩阵整体暂存
		for(j=0; j<=3; j++)
			state[i][j]=state[i][(j+i)&0x03];
		for(j=1; j<=i; j++)
			state[i][4-j]=temp1[i][(4+i-j)&0x03];//通过暂存矩阵求得被覆盖掉的元素
	}
}
void MixColumn(unsigned char state[4][4])
{
	int i,j,k;
	static unsigned char state1[4][4];
	unsigned char temp=0;
	/*******两矩阵Xtime乘然后异或模块*******/
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			for(k=0; k<4; k++)
			{
				temp^=Xtime(state[k][j],Polymatrix[i][k]);
			}
			state1[i][j]=temp;
			temp=0;
		}
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			state[i][j]=state1[i][j];
}
unsigned char Xtime(unsigned char a,unsigned char b)
{
	unsigned char temp=0;
	if(b==1)
		a*=b;
	else if(b==2)
		if(a>=128)
		{
			a<<=1;
			a^=27;
		}
		else
			a<<=1;
	else if(b==3)
	{
		temp=a;
		a=Xtime(a,(b-1));
		a^=temp;
	}
	return a;
}
void RoundKeyAddition(unsigned char state[4][4],unsigned char temp[4][4])
{
	int i,j;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
			state[i][j]^=temp[i][j];			//状态矩阵元素与轮密钥矩阵对应元素异或
}
