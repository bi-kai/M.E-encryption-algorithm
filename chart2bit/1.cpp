#include <stdio.h>

void char_bit(unsigned char char_array[4][4],unsigned char bit_array[128]);
void bit_char(unsigned char bit_array[128],unsigned char char_array[4][4]);

void main(){
	
	unsigned char state[4][4]={{50,136,49,224},{67,90,49,55},{246,48,152,7},{168,141,162,52}};	//初始明文
	unsigned char bits[128]={0};
	int kk=0,j=0;
	char_bit(state,bits);
	for (kk=0;kk<128;kk++)
	{
		printf("%d",bits[kk]);
	}
	
	printf("\r\n");
	bit_char(bits,state);
	for (kk=0;kk<4;kk++)
	{
		for(j=0;j<4;j++)
		printf("%d ",state[kk][j]);
	}

}

void char_bit(unsigned char char_array[4][4],unsigned char bit_array[128]){

	char i=0,j=0,k=0;
	int counter=0;

	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			for(k=7;k>=0;k--){
				bit_array[counter]=(char_array[i][j]& (0x01<<k))?1:0; 
				counter++;
			}
		}
	}

}


void bit_char(unsigned char bit_array[128],unsigned char char_array[4][4]){

	char i=0,j=0;
	int counter=0;

	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
			char_array[i][j]=0;//清零
			for (counter=(i*4*8+j*8);counter<(i*4*8+j*8+8);counter++)
			{
				char_array[i][j]|=bit_array[counter]<<(7-counter%8);
			}
		}
	}

}



