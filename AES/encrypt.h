#ifndef _ENCRYPT_H
#define _ENCRYPT_H
/********************加密函数***********************************/
void Encrypt(unsigned char state[4][4], unsigned char cipherkey[16]);
/********************加密部分所用到的函数***********************/
void KeyExpansion( unsigned char cipherkey[16],unsigned char enpandedkey[176]);
void RotSub(unsigned char temp[4]);
void ByteSub(unsigned char state[4][4]);
void ShiftRow(unsigned char state[4][4]);	
void MixColumn(unsigned char state[4][4]);
unsigned char Xtime(unsigned char,unsigned char);
void RoundKeyAddition(unsigned char [4][4],unsigned char [4][4]);
#endif //for #ifndef _ENCRYPT_H
