#include "LKT.h"

#ifndef __DES_h
#define __DES_h
#endif



#ifdef 	__DES_h


unsigned char Char8ToBit64(unsigned char *ch,unsigned char *bit_a); 
void Bit64ToChar8(unsigned char bit_a[64],unsigned char ch[8]);
void DES_PC1_Transfrom(unsigned char key[64],unsigned char tempbts[56]); 
void DES_PC2_Transfrom(unsigned char key[56],unsigned char tempbts[48]);  
void DES_ROL(unsigned char *data_a,unsigned char time);
void DES_ROR(unsigned char *data_a,unsigned char time);
void DES_IP_Transform(unsigned char data_a[64]);
void DES_IP_1_Transform(unsigned char data_a[64]);
void DES_E_Transform(unsigned char data_a[48]); 
void DES_P_Transform(unsigned char data_a[32]);
void DES_SBOX(unsigned char data_a[48]);
void DES_XOR(unsigned char R[48],unsigned char L[48],unsigned char count);
void DES_Swap(unsigned char left[32],unsigned char right[32]);
void encrypt_des(unsigned char *inoutdata,unsigned char *keyStr); 
void decrypt_des(unsigned char *inoutdata, unsigned char *keyStr);

void CbcDes_encrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key);
void CbcDes_decrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key);

void encrypt_3des(uint8_t *inoutdata,uint8_t *keyStr);
void decrypt_3des(uint8_t *inoutdata ,uint8_t *keyStr);

/*CBC_DES���ܺ���*/
/* iv ��ʼ����8�ֽڣ�    inoutdata ����ʱΪ�������ݣ����ʱΪ�������ݣ�ע����һ�ֽ�Ϊ���ȣ���   keyStr  ������Կ   */
void Cbcencrypt_3des(unsigned char *iv,uint8_t *inoutdata,uint8_t *keyStr);

/*CBC_DES���ܺ���*/
void Cbcdecrypt_3des(unsigned char *iv,uint8_t *inoutdata ,uint8_t *keyStr);
/*iv ��ʼ����8�ֽڣ�    inoutdata ����ʱΪ�������ݣ����ʱΪ�������ݣ�ע����һ�ֽ�Ϊ���ȣ���   keyStr  ������Կ   */

#endif
