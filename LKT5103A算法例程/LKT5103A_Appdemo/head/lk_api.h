#ifndef _Lingkes_API_head_
#define _Lingkes_API_head_
#include "DEF_Type.h"

#define GPIO_BASE     0x000F3000 
#define     __O       volatile  
typedef struct
{  
   __O  u32 GPIODATA;
   __O  u32 GPIODIR;
  
} GPIO_TypeDef;
#define GPIO             ((GPIO_TypeDef    *) GPIO_BASE )

 extern void LK_WriteNvm  (unsigned short addr, unsigned char * buf , unsigned char len);
 extern void LK_ReadNvm 	( unsigned short addr, unsigned char * buf , unsigned char len);
 extern void LK_GetRandom (unsigned char * buf, unsigned char len);
 extern void LK_GetChipID (unsigned char *sn);


 extern void LK_DESEncrypt( unsigned char   *plain, unsigned char  *key,unsigned char   *cipher);
 extern void LK_DESDecrypt( unsigned char   *plain, unsigned char  *key,unsigned char   *cipher);
 extern void LK_AESEncrypt( unsigned char   *plain, unsigned char  *key,unsigned char   *cipher);
 extern void LK_AESDecrypt( unsigned char   *plain, unsigned char  *key,unsigned char   *cipher);


 extern void LK_DesSetKey(unsigned char  ByteLenOfKey,unsigned char  *pKey);
 extern void LK_DesEncode(unsigned char  *pIn, unsigned char  *pOut);
 extern void LK_DesDecode(unsigned char  *pIn, unsigned char  *pOut);

 extern void LK_AesSetKeyEnc(unsigned char  ByteLenOfKey, unsigned char  *pKey,unsigned char  *pRoundKey);
 extern void LK_AesSetKeyDec(unsigned char  ByteLenOfKey, unsigned char  *pKey,unsigned char  *pRoundKey);

 extern void LK_AesEncode(unsigned char  *pIn, unsigned char  *pOut);
 extern void LK_AesDecode(unsigned char  *pIn, unsigned char  *pOut);

 extern void LK_HashInit(unsigned char  HashType);
 extern void LK_HashUpdate(unsigned char  HashType,unsigned char  * buf,unsigned char  len);
 extern void LK_HashLastUpdate(unsigned char  HashType,unsigned char  * buf,unsigned char  len);
 extern void LK_HashGetDigest(unsigned char  HashType,unsigned char  * digest);

 extern u16 RSA_DecryptPubKeyFile(u8 * buf,u16 dat_len,u16 * ret_len, u16 ef_addr);
 extern u16 RSA_DecryptPrivateKeyFile(u8 * datBuf,u16 dat_len,u16 * ret_len, u16 ef_addr);


#endif
