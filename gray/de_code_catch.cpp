#include<iostream>
using namespace std;
int decode_error_catch(int r1_code[24],int de_out[24]) /*修正的捕错译码*/
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

/*====================提取码字的前23位，得到（23，12）完备格雷码===========================*/
	
	for(i=0;i<23;i++)
		r_code[i]=r1_code[i];

/*===================将23位码字依次送入伴随式寄存器=====================================*/
	
	 for(k=0;k<23;k++)
	{  middle=de_reg[10];                 /*输入11位后，再输入时，寄存器经反馈更新，反馈值为middle*/

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

/*=================计算伴随式的重量===============================*/
 f1: for(i=0;i<11;i++)
    weight=weight+de_reg[i]; 

/*==========根据伴随式的重量大小，进行纠错译码======================*/
  if(weight<=3)
	{  T=1;                 /*错误均在后11位伴随式的值即为错误图样*/
  for(i=0;i<11;i++)
	  inter[i]=de_reg[i];          /*inter值即为错误图样*/
  
  }

  else 
  {   weight=0;
	                               /*Q(x)=x^5*/
	  inter[10]=de_reg[10];
	  inter[9]=(de_reg[9]+1)%2;            /*inter值即为S0-Si后得到的伴随式的值*/
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
	  r_code[(6+flag)%23]=(r_code[(6+flag)%23]+1)%2;}          /*信息位x^16纠错*/
	  else
	  {   
		  weight=0;                           /*Q(x)=x^6*/
		  inter[10]=(de_reg[10]+1)%2;
		  inter[9]=(de_reg[9]+1)%2;            /*inter值即为S0-Si后得到的伴随式的值，后11位的错误图样*/
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
		  r_code[(5+flag)%23]=(r_code[(5+flag)%23]+1)%2;           /*信息位x^17纠错*/
		  }
		  else 
			
			{  weight=0;
			   middle=de_reg[10];    /*以上3中情况均不成立，伴随式和缓存循环移位一次*/

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
	   de_reg[0]=middle;                       /*进行无输入的循环移位，计算伴随式*/
	                                     /*由于（23，12）格雷码是完备码，最多移位23次，即可完成纠错，错误数大于3，则发生错译*/
		flag=flag+1;             /*记录循环移位的次数*/
	  goto f1;
		  }
	  }
  }
  correct_bit=(12+flag)%23;                  /*开始纠错的位置，11级缓存的第一位输出*/

/*============================纠错过程==================================*/
  for(i=correct_bit,j=10;j>=0;i++,j--)              /*移位后相应的伴随式即为错误图样，r+e即完成到译码*/
 {
	 r_code[i%23]=(r_code[i%23]+inter[j])%2;
	   
  }
  for(i=0;i<23;i++)
  {
	  de_out[i]=r_code[i];
     sum=sum+de_out[i];
  }

  de_out[23]=sum%2;
/*=================完成一次译码后要消除伴随式的影响===============================*/
  for(i=0;i<11;i++)
  {
  de_reg[i]=0;
  
  }
  return 0;
}