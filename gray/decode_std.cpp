#include<iostream>
using namespace std;
int decode_golay(int r_code[],int de_out[],int H[11][23])    /*��׼��������*/
{
	int error_model[23][2048]={0};
	int error[23]={0};
	int sc[11]={0};
	int S[11][2048]={0};
	int i=0,j=0,k=0,n=0;
	int er=0,er1=0,er2=0;
	int flag=0,sum=0;
	
	/*=====================��������һλ����ʱ===================*/
	for(j=0;j<23;j++)	
	{error_model[j][j]=1;
	for(i=0;i<11;i++)
		S[i][j]=H[i][j];
	}
	/*j=23��ʼ*/
	/*===============����������λ����ʱ=====================*/
	for (er=0;er<22;er++)
	{
		for(k=er+1;k<23;k++)
		{ error_model[er][j]=1;
		error_model[k][j]=1;
		for (i=0;i<11;i++)
		{
			S[i][j]=(H[i][er]+H[i][k])%2;
		}
		j++;
		}
	}/*��ʱjΪ276*/
	
	/*==========����������3λ����ʱ==================*/
	for(er=0;er<21;er++)
		for(er1=er+1;er1<22;er1++)
			for(er2=er1+1;er2<23;er2++)
			{
				error_model[er][j]=1;
				error_model[er1][j]=1;
				error_model[er2][j]=1;
				for(i=0;i<11;i++)
				{
					S[i][j]=H[i][er]+H[i][er1];
					S[i][j]=(S[i][j]+H[i][er2])%2;
				}
				j++;
			}                      /*����j=2046*/
			
			
			/*===========�������ʽsc=R*H'=========================*/
			for(n=0;n<23;n++)
			{
				if(r_code[n]==1)
					for(i=0;i<11;i++)
						sc[i]=(sc[i]+H[i][n])%2;
			}
			
f1:	for(j=0;j<2048;j++)
	{ flag=0;
	   {
		   for(i=0;i<11;i++)
			   if(sc[i]==S[i][j])           /*�ҵ�����õ��İ���ʽ��S�����е�λ����λ�ã���*/
				   flag+=1;
	   }
	   if (flag==11)
	   { for(k=0;k<23;k++)
	   error[k]=error_model[k][j];
	   break;
	   }
	   
	}
	
	
	
	for(i=0;i<23;i++)
	{
		de_out[i]=(r_code[i]+error[i])%2;
		sum=sum+de_out[i];
	}
	
	de_out[23]=sum%2;             /*��������ȫУ��λ*/        
	
	return 0;
	
}