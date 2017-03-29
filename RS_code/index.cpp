#include "RS_head.h"
void index(int m,int * Gal,int * index_Gal)
{
	for(int i=0;i<pow(2.0,m)-1;i++)
		index_Gal[i]=0;
for(int i=0;i<pow(2.0,m)-1;i++)
   index_Gal[Gal[i]-1]=i;
}