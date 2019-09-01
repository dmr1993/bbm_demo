#include "DEF_Type.h"
#include "lk_api.h"
#include "string.h"
#include "math.h"

#define ADDR_OF_DES_KEY   0x0100 												//ÃÜÔ¿µØÖ·
#define ADDR_OF_DATA      0x0000												//Êý¾ÝµØÖ·

/***************************************************************************************************************
Des_encrypt ,DES »òTripDES ¼ÓÃÜÔËËã
LenOfKey----±ØÐëÎª 8 »ò 16 
LenOfIn ----±ØÐëÎª8 µÄÕûÊý±¶
***************************************************************************************************************/
void Des_encrypt(u8 LenOfKey, u8 LenOfIn, u8  * pKey, u8  * pIn, u8   * pOut )
{
	 u16 i;
	 u16 blk_num;
	 
	 blk_num = LenOfIn / 8;

	 LK_DesSetKey(LenOfKey, pKey);
	 
	 for(i=0;i<blk_num;i++)
	 {
	  LK_DesEncode(pIn, pOut);
	  pIn  +=8;
	  pOut +=8;
	 }
}

/***************************************************************************************************************
Des_decrypt ,DES »òTripDES ½âÃÜÔËËã
LenOfKey ----±ØÐëÎª 8 »ò 16 
LenOfIn -----±ØÐëÎª8 µÄÕûÊý±¶
***************************************************************************************************************/
void Des_decrypt(u8 LenOfKey, u8 LenOfIn, u8  * pKey, u8  * pIn, u8  * pOut )
{
	 u16 i;
	 u16 blk_num;
	 
	 blk_num = LenOfIn / 8;

	 LK_DesSetKey(LenOfKey, pKey);
	 
	 for(i=0;i<blk_num;i++)
	 {
	  LK_DesDecode(pIn, pOut);
	  pIn  +=8;
	  pOut +=8;
	 }
}
/*************************************************************************************************************
	Aes_encrypt ,AES ¼ÓÃÜÔËËã
	LenOfKey ---------±ØÐëÎª 16 or 24 or 32
	LenOfIn ----------±ØÐëÎª16 µÄÕûÊý±¶
*************************************************************************************************************/
void Aes_encrypt(u8 LenOfKey, u8 LenOfIn, u8 * pKey, u8 * pIn, u8 * pOut )
{
	 u16 i;
	 u16 blk_num;
	 u8 roundkey[240]; // ÐèÒªÎªAES ÔËËãÉêÇë240 ×Ö½ÚµÄ roundkey ¿Õ¼ä
	 
	 blk_num = LenOfIn / 16;

	 LK_AesSetKeyEnc(LenOfKey,pKey,roundkey) ;
	 
	 for(i=0;i<blk_num;i++)
	 {
	  LK_AesEncode(pIn, pOut);
	  pIn  +=16;
	  pOut +=16;
	 }
}

/*********************************************************************************************************
	Aes_decrypt ,AES ½âÃÜÔËËã
	LenOfKey ----------±ØÐëÎª 16 or 24 or 32
	LenOfIn -----------±ØÐëÎª16 µÄÕûÊý±¶
**********************************************************************************************************/
void Aes_decrypt(u8 LenOfKey, u8 LenOfIn, u8 * pKey, u8 * pIn, u8 * pOut )
{
	 u16 i;
	 u16 blk_num;
	 u8 roundkey[240]; // ÐèÒªÎªAES ÔËËãÉêÇë240 ×Ö½ÚµÄ roundkey ¿Õ¼ä
	 
	 blk_num = LenOfIn / 16;

	 LK_AesSetKeyDec(LenOfKey,pKey,roundkey);
	 
	 for(i=0;i<blk_num;i++)
	 {
	  LK_AesDecode(pIn, pOut);
	  pIn  +=16;
	  pOut +=16;
	 }
}

void GPIO_IN(u8 GPIO_Pin)
{  
  int i=GPIO_Pin-1;	
	GPIO->GPIODIR &= ~(1<<i);//0ÊÇÊäÈë
}
u8 READ_GPIO(u8 GPIO_Pin)
{  
  int i=GPIO_Pin-1;	
  return ((u8)(GPIO->GPIODATA>>i)&0x01);
}

void GPIO_OUT(u8 GPIO_Pin)
{
  int i=GPIO_Pin-1;  	
	GPIO->GPIODIR |= (1<<i);	//1ÊÇÊä³ö
}

void GPIO_SetBits(u8 GPIO_Pin)
{  
  int i=GPIO_Pin-1;  		
	GPIO->GPIODATA |= (1<<i); // À­¸ß		
}

void GPIO_ResetBits(u8 GPIO_Pin)
{
  int i=GPIO_Pin-1;
	GPIO->GPIODATA &= ~(1<<i);// À­µÍ
}

/********************************************************************************************************
	Hash_Digest : ¼ÆËãHASH
	hashType =0 -------±íÊ¾ SHA-1 Ëã·¨, 
	hashType =1 -------±íÊ¾ SHA-256 Ëã·¨
*********************************************************************************************************/
void Hash_Digest(u8 hashType, u16 LenOfMsg, u8 * pMsg, u8 * pDigest)
{
 	LK_HashInit(hashType);
	LK_HashLastUpdate(hashType , pMsg, LenOfMsg );
	LK_HashGetDigest(hashType, pDigest );
}















/**************************************************************************************************************
º¯ÊýÃû³Æ£ºCommunication_Test
º¯Êý²ÎÊý£ºu8  *in ------- ÊäÈëÊý¾Ý
          u8  *out------- Êä³öÊý¾Ý
          u8 len-------------- ÊäÈëÊý¾Ý³¤¶È
º¯Êý¹¦ÄÜ£º²âÊÔÍ¨Ñ¶ÊÇ·ñÕý³£
º¯ÊýÊä³ö£º½«ÊäÈëÊý¾ÝÈ¡·´ºó Êä
***************************************************************************************************************/
void Communication_Test(u8  *in,u8 *out,u8 len)
{
  u8 i;
    
  for(i=0;i < len;i++)
   out[i]= ~in[i]; 
			   	
}




/***************************************************************************************************************
º¯ÊýÃû³Æ: Write_Key
º¯Êý²ÎÊý£ºu8  *buf --- Ð´ÈëÃÜÔ¿µÄÖµ  £¨ ¸ñÊ½ £ºÃÜÔ¿³¤¶È + ÃÜÔ¿Öµ £©
º¯Êý¹¦ÄÜ£ºÐ´ÈëÃÜÔ¿º
º¯ÊýÊä³ö£ºÎÞ

×¢Ã÷£º´ËÐ´ÈëÃÜÔ¿º¯Êý ¿É¹© ¶Ô±ÈÈÏÖ¤¡¢²ÎÊý±£»¤¡¢Ëã·¨ÒÆÖ² Ð´ÃÜÔ¿Ê¹ÓÃ

Ö¸Áî¸ñÊ½Ê¾Àý£º 8008 0000 12 02 10 000102030405060708090A0B0C0D0E0F
****************************************************************************************************************/
void Write_Key(u8 *buf)
{  
  u16 key_addr;
  key_addr = ADDR_OF_DES_KEY;
  LK_WriteNvm(key_addr,buf,buf[0]+1);
  return;
}









/************************************************ ¶Ô±ÈÈÏÖ¤·½°¸ ************************************************/
/***************************************************************************************************************
º¯ÊýÃû³Æ£ºContrast_Authentication 
º¯Êý²ÎÊý£ºu8  *pIn------------- ÊäÈëÊý¾Ý
					u8  *pIn------------- Êä³öÊý¾Ý

º¯Êý¹¦ÄÜ£º ¶Ô±ÈÈÏÖ¤º¯Êý
º¯ÊýÊä³ö£º 8×Ö½ÚËæ»úÊý + 8×Ö½ÚµÄ¼ÓÃÜ½á¹û

Ö¸Áî¸ñÊ½Ê¾Àý £º8008 0000 09 03 1122334455667788
***************************************************************************************************************/
int Contrast_Authentication(u8 *pIn,u8 *pOut)
{
	 u8 i=0;
	 u8 RandBuf[0x20];
	 u8 CompBuf[0x20];
	 u8 KeyBuf[0x20];

	 memmove(CompBuf,pIn,0x08);      														// ½«¼ÓÃÜÊý¾Ý ´æ·Åµ½ CompBuf Êý×éÖÐ
   LK_GetRandom( RandBuf,0x08);    														// »ñÈ¡8×Ö½ÚËæ»úÊý
	 memmove( pOut,RandBuf,0x08);    														// pOut µØÖ·¿ªÊ¼´æÈë 8×Ö½ÚËæ»úÊý
   for(i=0;i < 8;i++)
   {
        CompBuf[i] ^=RandBuf[i]; 															//Ëæ»úÊýÓë´«ÈëÊý¾ÝÒì»ò²Ù×÷
	 }	
 
	 
  
	LK_ReadNvm(ADDR_OF_DES_KEY,KeyBuf,0x11);										//NVMÇøÖÐ¶ÁÈ¡ÃÜÔ¿ //Èç¹ûKEY µÄ³¤¶È´íÎó,ÔòÎÞ·¨Íê³É¼ÓÃÜÔËËã 
  if ((KeyBuf[0] != 8) && (KeyBuf[0] != 16 ) )
  {  
			return 0;
  }
  Des_encrypt(KeyBuf[0],8,KeyBuf+1,CompBuf,pOut+8);  					// pOut+8 µØÖ·¿ªÊ¼ ´æ·Å¼ÓÃÜµÄÊý¾Ý

  return 1;

}












/************************************************** ²ÎÊý±£»¤·½°¸ ***********************************************/
/****************************************************************************************************************
º¯ÊýÃû³Æ£ºWrite_Important_Data
º¯Êý²ÎÊý£ºu8  *pIn --------ÊäÈëÊý¾Ý
º¯Êý¹¦ÄÜ£º·¢ÐÐ½×¶ÎÐ´ÈëÖØÒªÊý¾Ý
º¯ÊýÊä³ö£ºÎÞ

Ö¸Áî¸ñÊ½Ê¾Àý: 8008 0000 09 04 0102030405060708
****************************************************************************************************************/
void Write_Important_Data(u8  *pIn)
{
	u16 Important_Data_Addr;
	
  Important_Data_Addr = ADDR_OF_DATA ;
  LK_WriteNvm(Important_Data_Addr,pIn,8);  														//¹Ì¶¨´«Èë²ÎÊý 8×Ö½Ú 
}



/***************************************************************************************************************
º¯ÊýÃû³Æ£ºRead_Important_Data
º¯Êý²ÎÊý£ºu8  *pIn ---------ÊäÈëÊý¾Ý
					u8  *pOut---------Êä³öÊý¾Ý

º¯Êý¹¦ÄÜ£ºÊ¹ÓÃ½×¶ÎÖØÒª²ÎÊýÊä³öº¯Êý
º¯ÊýÊä³ö£º8×Ö½Ú Ëæ»úÊý + 8×Ö½ÚµÄÃÜÎÄ

Ö¸Áî¸ñÊ½Ê¾Àý£º8008 0000 09 05 1122334455667788
****************************************************************************************************************/
int Read_Important_Data(u8  *pIn,u8  *pOut)
{
	u8 i=0;
	u8 RandBuf_1[0x20];
	u8 RandBuf_2[0x20];
	u8 ParaBuf[0x20];
	u8 KeyBuf[0x20];
  memmove(RandBuf_1,pIn,0x08); 																		  //½«MCU ·¢À´µÄ8×Ö½ÚËæ»úÊý´æ´¢ÔÚ RandBuf_1ÖÐ
	
	LK_GetRandom(RandBuf_2,0x08);   																  // »ñÈ¡8×Ö½ÚËæ»úÊý
  memmove( pOut,RandBuf_2,0x08);                                    // pOut µØÖ·¿ªÊ¼´æÈë 8×Ö½ÚËæ»úÊý
	
  for(i=0;i < 8;i++)
  {
        RandBuf_2[i] ^=RandBuf_1[i]; 																//Ëæ»úÊýÓë´«ÈëËæ»úÊý×öÒì»ò²Ù×÷
	}	
  
  LK_ReadNvm((u16)ADDR_OF_DATA,ParaBuf,8);   										    // ¶ÁÈ¡ ´«ÈëµÄ8 ×Ö½ÚÖØÒª²ÎÊý
	
	for(i=0;i < 8;i++)
  {
        ParaBuf[i] ^=RandBuf_2[i]; 																	//Ëæ»úÊýÓë ×ÜÒª²ÎÊý×öÒì»ò
	}	

	
	LK_ReadNvm(ADDR_OF_DES_KEY,KeyBuf,0x11);													//NVMÇøÖÐ¶ÁÈ¡ÃÜÔ¿ //Èç¹ûKEY µÄ³¤¶È´íÎó,ÔòÎÞ·¨Íê³É¼ÓÃÜÔËËã 
  if ((KeyBuf[0] != 8) && (KeyBuf[0] != 16 ) )
  {  
			return 0;
  }
  Des_encrypt(KeyBuf[0],8,KeyBuf+1,ParaBuf,pOut+8);  								// pOut+8 µØÖ·¿ªÊ¼ ´æ·Å¼ÓÃÜµÄÊý¾Ý
	
	return 1;
	
}

// CBC ÊµÏÖ·½Ê½ ²ÎÊý±£»¤Êä³ö












/************************************************ Ëã·¨ÒÆÖ²·½°¸*************************************************/
/**************************************************************************************************************

º¯ÊýÃû³Æ£ºAlgorithm_Transplantation
º¯Êý²ÎÊý£ºu8  *pIn ---------ÊäÈëÊý¾Ý
					u8  *pOut --------Êä³öÊý¾Ý

º¯Êý¹¦ÄÜ£ºËã·¨ÒÆÖ²Àý³Ì
º¯ÊýÊä³ö£ºËã·¨ÔËËã½á¹û

×¢Ã÷£º ´ËÒÆÖ²º¯Êý½ö¹©²Î¿¼

   x          0<=x <2
y= x*x+1       2<= x <6
   sqrt(x+1)  6<=x<10
   1/(x+1)    10<x <=20
	 

Ö¸Áî¸ñÊ½Ê¾Àý£º8008 0000 02 06 xx
***************************************************************************************************************/
int Algorithm_Transplantation(u8 *pIn,u8 *pOut)
{

	  float num=0.0;
    if( pIn[0]>=0.0 && pIn[0]<2)
		{
				num=pIn[0];
		}
	  else if( pIn[0]>=2 && pIn[0]<6 )
		{
				num=pIn[0]*pIn[0]+1;
		}
	  else if( pIn[0]>=6 && pIn[0]<10)
		{
			  num=sqrt(pIn[0]+1);
		}
		else if( pIn[0]>=10 )
		{
				num= 1.0/(pIn[0]+1);
		}
		
		memmove(pOut,&num,0x04);
		
		return 4;
}




int My_Algorithm(u8 *pIn,u8 *pOut) //5103AÖ§³Öµ¥¾«¶È¸¡µãÊý£¬ÇÒÎªÐ¡¶ËÄ£Ê½
{

	  //float num=0.0;
   	u8 i,j;
		float d=4.5;
   	float fdata[10];              //´´½¨¸¡µãÊýÊý×é
   	unsigned char *ptr;           //
		unsigned char *ptr1;  
	//	double d0 = 1.2;
   	
	  for(j=0;j<10;j++)
	  {
			ptr=(unsigned char *)&fdata[j];  //È¡¸¡µãÊýµÄ´æ´¢µØÖ·
   	  for(i=0;i<4;i++)
     		*((volatile unsigned char *)ptr++)=*(pIn+4*j+i);
		}
	        		
		for(i=0;i<10;i++)			
	     fdata[i]  =  fdata[i]*d;
   
	  for(j=0;j<10;j++)
    {
			ptr1=(unsigned char *)&fdata[j];    //¹¹Ôìµ¥×Ö½ÚÖ¸Õë
      for(i=0;i<4;i++)
     		*(pOut+4*j+i)=*((volatile unsigned char *)ptr1++);  
		}
		
		//memmove(pOut,&num,0x04);
		
		return 40;   //10¸ö¸¡µãÊýÊÇ40¸ö×Ö½Ú
}

/**
	8008 0000 33 08 FFC0 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F 0000803F
3F800000
*/
int Algorithm(u8 *pIn,u8 *pOut) //5103AÖ§³Öµ¥¾«¶È¸¡µãÊý£¬ÇÒÎªÐ¡¶ËÄ£Ê½
{
	int keys[12];
	int i = 0;
	int j = 0;
	int l = 0;
	// int h = 0;
	int start = 0;
	int indx = 0;
	u8 k = 1;
	float params[10];
	float *point;
	u8 *uP;
	u8 p[4];
	
	for(; i<2; i++){
		start = 8 *i;
		for(j =0; j<8; j++){
			if(i*8+j+l>12){
				break;
			}
			indx = start + j;
			keys[indx] = (pIn[i] >> (8 - (j+1)))&k;
		}
	}
	for(i = 0; i< 48/4; i++){
		if(keys[i] != 1){
			continue;
		}
		for(j = 0; j<4; j++){
			p[j] = pIn[i*4+j+2];
		}
		point = (float *)p;
		
		params[l] = *point;
		l++;
	}
	for(i = 0; i<10; i++){
		params[i]++;
		uP = (u8 *)&params[i];
		for(j = 0; j<4; j++){
			pOut[i*4 +j] = uP[j];
		}
	}
	
	
	return 40;
}










