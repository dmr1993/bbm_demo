#include "DEF_Type.h"
#include "lk_api.h"
#include "string.h"
#include "math.h"

#define ADDR_OF_DES_KEY   0x0100 												//密钥地址
#define ADDR_OF_DATA      0x0000												//数据地址

/***************************************************************************************************************
Des_encrypt ,DES 或TripDES 加密运算
LenOfKey----必须为 8 或 16 
LenOfIn ----必须为8 的整数倍
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
Des_decrypt ,DES 或TripDES 解密运算
LenOfKey ----必须为 8 或 16 
LenOfIn -----必须为8 的整数倍
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
	Aes_encrypt ,AES 加密运算
	LenOfKey ---------必须为 16 or 24 or 32
	LenOfIn ----------必须为16 的整数倍
*************************************************************************************************************/
void Aes_encrypt(u8 LenOfKey, u8 LenOfIn, u8 * pKey, u8 * pIn, u8 * pOut )
{
	 u16 i;
	 u16 blk_num;
	 u8 roundkey[240]; // 需要为AES 运算申请240 字节的 roundkey 空间
	 
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
	Aes_decrypt ,AES 解密运算
	LenOfKey ----------必须为 16 or 24 or 32
	LenOfIn -----------必须为16 的整数倍
**********************************************************************************************************/
void Aes_decrypt(u8 LenOfKey, u8 LenOfIn, u8 * pKey, u8 * pIn, u8 * pOut )
{
	 u16 i;
	 u16 blk_num;
	 u8 roundkey[240]; // 需要为AES 运算申请240 字节的 roundkey 空间
	 
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
	GPIO->GPIODIR &= ~(1<<i);//0是输入
}
u8 READ_GPIO(u8 GPIO_Pin)
{  
  int i=GPIO_Pin-1;	
  return ((u8)(GPIO->GPIODATA>>i)&0x01);
}

void GPIO_OUT(u8 GPIO_Pin)
{
  int i=GPIO_Pin-1;  	
	GPIO->GPIODIR |= (1<<i);	//1是输出
}

void GPIO_SetBits(u8 GPIO_Pin)
{  
  int i=GPIO_Pin-1;  		
	GPIO->GPIODATA |= (1<<i); // 拉高		
}

void GPIO_ResetBits(u8 GPIO_Pin)
{
  int i=GPIO_Pin-1;
	GPIO->GPIODATA &= ~(1<<i);// 拉低
}

/********************************************************************************************************
	Hash_Digest : 计算HASH
	hashType =0 -------表示 SHA-1 算法, 
	hashType =1 -------表示 SHA-256 算法
*********************************************************************************************************/
void Hash_Digest(u8 hashType, u16 LenOfMsg, u8 * pMsg, u8 * pDigest)
{
 	LK_HashInit(hashType);
	LK_HashLastUpdate(hashType , pMsg, LenOfMsg );
	LK_HashGetDigest(hashType, pDigest );
}















/**************************************************************************************************************
函数名称：Communication_Test
函数参数：u8  *in ------- 输入数据
          u8  *out------- 输出数据
          u8 len-------------- 输入数据长度
函数功能：测试通讯是否正常
函数输出：将输入数据取反后 输
***************************************************************************************************************/
void Communication_Test(u8  *in,u8 *out,u8 len)
{
  u8 i;
    
  for(i=0;i < len;i++)
   out[i]= ~in[i]; 
			   	
}




/***************************************************************************************************************
函数名称: Write_Key
函数参数：u8  *buf --- 写入密钥的值  （ 格式 ：密钥长度 + 密钥值 ）
函数功能：写入密钥�
函数输出：无

注明：此写入密钥函数 可供 对比认证、参数保护、算法移植 写密钥使用

指令格式示例： 8008 0000 12 02 10 000102030405060708090A0B0C0D0E0F
****************************************************************************************************************/
void Write_Key(u8 *buf)
{  
  u16 key_addr;
  key_addr = ADDR_OF_DES_KEY;
  LK_WriteNvm(key_addr,buf,buf[0]+1);
  return;
}









/************************************************ 对比认证方案 ************************************************/
/***************************************************************************************************************
函数名称：Contrast_Authentication 
函数参数：u8  *pIn------------- 输入数据
					u8  *pIn------------- 输出数据

函数功能： 对比认证函数
函数输出： 8字节随机数 + 8字节的加密结果

指令格式示例 ：8008 0000 09 03 1122334455667788
***************************************************************************************************************/
int Contrast_Authentication(u8 *pIn,u8 *pOut)
{
	 u8 i=0;
	 u8 RandBuf[0x20];
	 u8 CompBuf[0x20];
	 u8 KeyBuf[0x20];

	 memmove(CompBuf,pIn,0x08);      														// 将加密数据 存放到 CompBuf 数组中
   LK_GetRandom( RandBuf,0x08);    														// 获取8字节随机数
	 memmove( pOut,RandBuf,0x08);    														// pOut 地址开始存入 8字节随机数
   for(i=0;i < 8;i++)
   {
        CompBuf[i] ^=RandBuf[i]; 															//随机数与传入数据异或操作
	 }	
 
	 
  
	LK_ReadNvm(ADDR_OF_DES_KEY,KeyBuf,0x11);										//NVM区中读取密钥 //如果KEY 的长度错误,则无法完成加密运算 
  if ((KeyBuf[0] != 8) && (KeyBuf[0] != 16 ) )
  {  
			return 0;
  }
  Des_encrypt(KeyBuf[0],8,KeyBuf+1,CompBuf,pOut+8);  					// pOut+8 地址开始 存放加密的数据

  return 1;

}












/************************************************** 参数保护方案 ***********************************************/
/****************************************************************************************************************
函数名称：Write_Important_Data
函数参数：u8  *pIn --------输入数据
函数功能：发行阶段写入重要数据
函数输出：无

指令格式示例: 8008 0000 09 04 0102030405060708
****************************************************************************************************************/
void Write_Important_Data(u8  *pIn)
{
	u16 Important_Data_Addr;
	
  Important_Data_Addr = ADDR_OF_DATA ;
  LK_WriteNvm(Important_Data_Addr,pIn,8);  														//固定传入参数 8字节 
}



/***************************************************************************************************************
函数名称：Read_Important_Data
函数参数：u8  *pIn ---------输入数据
					u8  *pOut---------输出数据

函数功能：使用阶段重要参数输出函数
函数输出：8字节 随机数 + 8字节的密文

指令格式示例：8008 0000 09 05 1122334455667788
****************************************************************************************************************/
int Read_Important_Data(u8  *pIn,u8  *pOut)
{
	u8 i=0;
	u8 RandBuf_1[0x20];
	u8 RandBuf_2[0x20];
	u8 ParaBuf[0x20];
	u8 KeyBuf[0x20];
  memmove(RandBuf_1,pIn,0x08); 																		  //将MCU 发来的8字节随机数存储在 RandBuf_1中
	
	LK_GetRandom(RandBuf_2,0x08);   																  // 获取8字节随机数
  memmove( pOut,RandBuf_2,0x08);                                    // pOut 地址开始存入 8字节随机数
	
  for(i=0;i < 8;i++)
  {
        RandBuf_2[i] ^=RandBuf_1[i]; 																//随机数与传入随机数做异或操作
	}	
  
  LK_ReadNvm((u16)ADDR_OF_DATA,ParaBuf,8);   										    // 读取 传入的8 字节重要参数
	
	for(i=0;i < 8;i++)
  {
        ParaBuf[i] ^=RandBuf_2[i]; 																	//随机数与 总要参数做异或
	}	

	
	LK_ReadNvm(ADDR_OF_DES_KEY,KeyBuf,0x11);													//NVM区中读取密钥 //如果KEY 的长度错误,则无法完成加密运算 
  if ((KeyBuf[0] != 8) && (KeyBuf[0] != 16 ) )
  {  
			return 0;
  }
  Des_encrypt(KeyBuf[0],8,KeyBuf+1,ParaBuf,pOut+8);  								// pOut+8 地址开始 存放加密的数据
	
	return 1;
	
}

// CBC 实现方式 参数保护输出












/************************************************ 算法移植方案*************************************************/
/**************************************************************************************************************

函数名称：Algorithm_Transplantation
函数参数：u8  *pIn ---------输入数据
					u8  *pOut --------输出数据

函数功能：算法移植例程
函数输出：算法运算结果

注明： 此移植函数仅供参考

   x          0<=x <2
y= x*x+1       2<= x <6
   sqrt(x+1)  6<=x<10
   1/(x+1)    10<x <=20
	 

指令格式示例：8008 0000 02 06 xx
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


















