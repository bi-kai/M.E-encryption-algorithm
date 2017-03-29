#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<iostream>
#include "encrypt.h"
unsigned char state[4][4];
using namespace std;
int main(void)
{
	register int i = 0;
	unsigned char state[4][4]={{50,136,49,224},{67,90,49,55},{246,48,152,7},{168,141,162,52}};	//³õÊ¼Ã÷ÎÄ

	clock_t tick1 = clock();
	for(i = 0; i != 50000; ++i)
		Encrypt(state,cipherkey);
	clock_t tick2 = clock();
	cout << (tick2 - tick1) / CLOCKS_PER_SEC << endl;
	return 0;
}