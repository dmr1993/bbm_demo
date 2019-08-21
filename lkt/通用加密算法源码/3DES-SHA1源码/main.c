
/**************LPC1768 使用12MHZ晶振    加密芯片使用3.579MHZ的晶振*******************/
#include "DES.h"
#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "sha1.h"


 u8 inoutdata[128];
 u8 keyStr[128];
 u8 keyStr1[128];		
u16 SW=0;
 unsigned char iv[8];
/*
 *  ??????
 */

long int repeatcount[4] = { 1, 1, 1000000, 10 };
char *resultarray[4] =
{
    "A9 99 3E 36 47 06 81 6A BA 3E 25 71 78 50 C2 6C 9C D0 D8 9D",
    "84 98 3E 44 1C 3B D2 6E BA AE 4A A1 F9 51 29 E5 E5 46 70 F1",
    "34 AA 97 3C D4 C4 DA A4 F6 1E EB 2B DB AD 27 31 65 34 01 6F",
    "DE A3 56 A2 CD DD 90 C7 A7 EC ED C5 EB B5 63 93 4F 46 04 52"
};
const unsigned char testarray[]={0x01,0x02,0x03,0x04,0x05};

int main (void)
{  	
	 /*SHA1Context sha;
   uint8_t Message_Digest[20];
	 SystemInit();
	 //SHA-1演示:
	 SHA1Result_init(&sha,testarray,0x5,Message_Digest);
	 //CC-3DES加解密演示：
	 memcpy(iv,"\xAF\x3F\x8D\xBB\xA8\xF7\x09\x86",8);        	       
   memcpy(inoutdata,"\x18\x11\x22\x33\x44\x55\x66\x77\x88\x99\xaa\xBB\xCC\xDD\xEE\xFF\x00\x11\x11\x11\x11\x11\x11\x22\x22",0x19);
	 memcpy(keyStr,"\x11\x52\x51\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11\x11",0x10);*/

	 /*CBC_DES加密函数*/
	 //Cbcencrypt_3des(iv,inoutdata,keyStr);
	 /*CBC_DES解密函数*/
	 //Cbcdecrypt_3des(iv,inoutdata,keyStr);
	
	 //3DES加解密演示：                      
   memset(inoutdata,0,0x20);
	 memcpy(inoutdata,"\x10\x11\x22\x33\x44\x55\x66\x77\x88\x12\x11\x13\x32\x45\x56\x58\x94",0x11); //注意第一个字节为加密明文长度		       
   memcpy(keyStr,"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",0x10);
	 //3DES加密	
	 encrypt_3des(inoutdata,keyStr);	
   memset(inoutdata,0,0x20);          		        
   memcpy(inoutdata,"\x10\xCD\x72\xDF\xC6\xE6\xD0\x40\xA4\xc8\xd7\xc1\x1c\x36\x1a\x37\xb6",0x11); //注意第一个字节为解密密文长度		       
   memcpy(keyStr,"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",0x10);
	 //3DES解密
	 decrypt_3des(inoutdata,keyStr);		 	 

	 while(1);

}
