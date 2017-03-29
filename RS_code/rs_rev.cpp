#include "RS_head.h"
int rs_rev(int a,int m, int * Gal, int * ind)
{
	return Gal[((int)pow(2.0,m)-1-ind[a-1])%(int)(pow(2.0,m)-1)];
}
