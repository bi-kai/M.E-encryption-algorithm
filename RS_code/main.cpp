#include "RS_head.h"		
#include <iostream>
#include <cstddef>
using namespace std;
int main()
{ 
			srand((unsigned)time(0));
				FILE *fp;
	            int Gal[256]={0};//修改参数值(2^m)
		       int  ind[255]={0};//修改参数值(2^m-1)
				int Coefficient_Polynomial[2*T+1]={0};
				int sigma[N-K+2][N-K+1]={0};
				int m_data[K]={0};
				int m_data_bit[K][M]={0};
				int * encode_output=new int[N];
				int * encode_output_bit=new int[N*M];
				int * receive_from_channel=new int[N];
				int *sys_output=new int[2*T];
				int *decode_out=new int[K];
				int *errorvalue_output=new int[N];
				int *decode_out_bit=new int[K*M];
				int Degree_sigma[1]={0};
				int i=0,j=0,j1=0;
				char filename[20];
				double EbN0,//信噪比//
					BYER,////字节错误率/
					step;
				step = 0.5;  EbN0=1.5;//EbN0是dB形式的，3dB是2//
	int EbN0_level; //EbN0的样本点个数//
	unsigned long total_length,//发送的总字节数目//
		errorcount;///字节错误数目//
	total_length=0;
	printf("please input the file name to store BER value:");
	scanf("%s",filename);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("please enter the step（the sample number of  SNR）:  ");
	scanf("%d", &EbN0_level);	
//======================================================================================================================/
	if((fp=fopen(filename,"a+"))==NULL)
		{
			printf("cannot open this file \n");
			exit(0);
		}
		 fprintf(fp,"Simulation time is %s\n",Printf_time());
		fprintf(fp, "coding with BM_algorithm:\n");
		fprintf(fp, "Eb/N0(dB)\tBYER\n");
		 	fclose(fp);
			   Galoias_generate(M,Gal);
				index(M,Gal, ind);
			    rs_Coefficient_Polynomial(M,T,Gal, ind,Coefficient_Polynomial);
//========================================================================================================================//
 for(j=1; j<=EbN0_level; j++) //EbN0的样本点个数//
		{
			errorcount=0;
			BYER=0.0;
			total_length=0;
	while((total_length<1e9)&&(errorcount<300))
			{
				//======随机的产生K*M个位于（1 0）序列===========//
				for(i=0; i<K; i++)
					for(j=0; j<M; j++)
					m_data_bit[i][j] = rand()&1;	
#ifdef TEST1 
				printf("------------------------m_data_bit------------------------------------------------------------------------------------------------\n");
				for(i=0; i<K; i++)//产生KK个信息位//
					for(j=0; j<M; j++)
					printf("%d",m_data_bit[i][j]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
				for(i=0; i<K; i++)//产生K个信息位(八个bit转为一个十进制)//
				m_data[i]=Bi_to_Dec(m_data_bit[i]);
#ifdef TEST1 
				printf("------------------------m_data----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<K; i++)//产生KK个信息位//
				//	for(j=0; j<M; j++)
					printf("%d,",m_data[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
					CLEAR(encode_output,0,(N-1));
					encoder(m_data,N ,K,M,Gal,ind,Coefficient_Polynomial,encode_output);
#ifdef TEST1 
				printf("------------------------encode_output----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<N; i++)//产生KK个信息位//
					printf("%d,",encode_output[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
					 CLEAR(encode_output_bit,0,(M*N-1));
			 j1=0;
          for(i=0; i<N; i++)//将N个256进制的码字映射成N*M个的二进制bit
				{
					int temp[M]={0};
					de2bi(encode_output[i],M,temp);
						for(int p=0;p<M;p++)
								encode_output_bit[j1++]=temp[p];
				}
#ifdef TEST1 
				printf("------------------------encode_output_bit----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<N*M; i++)//产生KK个信息位//
					printf("%d",encode_output_bit[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
//=================Gauss信道下非编码的BPSK调制=================//
			channel(EbN0, encode_output_bit);
#ifdef TEST 
				printf("------------------------encode_output_bit_from_channel----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<N*M; i++)//产生KK个信息位//
					printf("%d",encode_output_bit[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
					j1=0;
					CLEAR(receive_from_channel,0,(N-1));
					 for(i=0; i<N; i++)
							{
								int temp[M]={0};
								for(int p=0;p<M;p++)
									temp[p]=encode_output_bit[j1++];
								receive_from_channel[i]=Bi_to_Dec(temp);
							}					 
#ifdef TEST1 
				printf("------------------------receive_from_channel----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<N; i++)//产生KK个信息位//
					printf("%d,",receive_from_channel[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
               CLEAR(sys_output,0,(2*T-1));
				 CLEAR(errorvalue_output,0,(N-1));
				 CLEAR(decode_out,0,(K-1));
				 CLEAR(decode_out_bit,0,(K*M-1));
				 Degree_sigma[0]=0;
				syndrome(receive_from_channel,N,K, M, Gal,ind,sys_output);	
#ifdef TEST1 
				printf("------------------------sys_output----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<N-K; i++)//产生KK个信息位//
					//for(j=0; j<M; j++)
					printf("%d,",sys_output[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
				decoder(N,K,M,Gal,ind,sys_output,receive_from_channel,Degree_sigma,errorvalue_output,decode_out);
#ifdef TEST1 
				printf("------------------------decode_out----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<K; i++)//产生KK个信息位//
					//for(j=0; j<M; j++)
					printf("%d,",decode_out[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
				j1=0;
             for(i=0; i<K; i++)//译码部分的输出结果
				{
					int temp[M]={0};
					de2bi(decode_out[i],M,temp) ;
					for(int p=0;p<M;p++)
						decode_out_bit[j1++]=temp[p];//译码部分的输出
				}
 #ifdef TEST1 
				printf("------------------------decode_out_bit----------------------------------------------------------------------------------------------------\n");
				for(i=0; i<K*M; i++)//产生KK个信息位//
					//for(j=0; j<M; j++)
					printf("%d",decode_out_bit[i]);//m_data_bit[i][j] = rand()&1;//产生-90----32767的随机整数//	
					printf("\n");
#endif
				//============统计信息位的错误数目==================//
				for(i=0; i<K; i++)//统计映射后的错误比特数
					for(j=0; j<M; j++)
							if(m_data_bit[i][j]!=decode_out_bit[i*M+j]) 
								errorcount++;
				total_length+=N*M;
			}
			BYER = (double)errorcount/total_length;//计算bit错误率//  信息位错位的数目除以发送的长度
			printf("when Eb/N0 = %fdB, the BYER = %e\n", EbN0, BYER);
			///=======================写到filename文件中=======================//
			if((fp=fopen(filename,"a+"))==NULL)
		{
			printf("cannot open this file \n");
			exit(0);
		}
			fprintf(fp, "%fdB\t%e\n", EbN0, BYER);
			fclose(fp);
			EbN0 = EbN0 + step;//EbN0是dB形式的，3dB是2， 
			}	
			clock_t tick = clock();
			encoder(m_data,N ,K,M,Gal,ind,Coefficient_Polynomial,encode_output);
			for(int i = 0; i != 10000; ++i) {
				decoder(N,K,M,Gal,ind,sys_output,receive_from_channel,Degree_sigma,errorvalue_output,decode_out);
			}
			clock_t tick2 = clock();
			cout << "the time: ";
			cout << (tick2 - tick) / CLOCKS_PER_SEC << endl;
				delete []  encode_output;
			    delete [] encode_output_bit;
				delete [] decode_out;
				delete []  decode_out_bit;
				delete []  receive_from_channel;
			    delete [] sys_output;
				delete [] errorvalue_output;
}
