#ifndef FEC_H
#define FEC_H
#define M 12


#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<fstream>



void encode(int bitin[],int code[]);
double GaussRand(double sigma);
int m_deM(int en_code[24],int m_code[24],int dem_code[24],double sigma);//Ӳ�о��ĵ�������
int decode_golay(int r_code[],int de_out[23],int H[11][23]);//��׼��������
int decode_error_catch(int r1_code[24],int de_out[24]);//�����Ĳ�������



#endif