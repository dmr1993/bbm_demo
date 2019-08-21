#include "des.h" 
#include <string.h>

unsigned char outbuf[255],outbuf1[255];
unsigned char outbuf2[255];

        unsigned char S[4][4][16] =//S1  
	            {{{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},  
	              {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},  
	              {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},  
	              {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},  
	                //S2  
	              {{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},  
	              {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},  
	              {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},  
	              {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},  
	              //S3  
	              {{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},  
	               {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},  
	               {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},  
	               {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},  
	              //S4  
	              {{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},  
	               {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},  
	               {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},  
	               {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}}} ;
	              //S5  
	     uint8_t S1[4][4][16]=
		 		{{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},  
	              {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},  
	              {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},  
	              {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},  
	              //S6  
	              {{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},  
	               {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},  
	               {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},  
	               {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},  
	              //S7  
	              {{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},  
	               {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},  
	               {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},  
	               {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},  
	              //S8  
	              {{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},  
	               {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},  
	               {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},  
	               {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}}}; 


/*void *memcpy(void *dest, const void *src, size_t n)
{
      void *ret=dest;
      while(n--){
         *(char *)dest = *(char *)src; 
         dest = (char *)dest + 1; 
         src = (char *)src + 1; 
      }   
      return(ret); 
}	*/



//½«³¤¶ÈÎª8µÄ×Ö·û´®×ªÎª¶þ½øÖÆÎ»´®  
uint8_t Char8ToBit64(uint8_t ch[8],uint8_t *bit_a){  
	    uint8_t cnt,cnt1;  
	    for(cnt = 0; cnt < 8; cnt++){    
		     
			 for(cnt1 = 0;cnt1 < 8; cnt1++){  
	         if((ch[cnt]& 0x80) == 0x80)
			 	*bit_a = 0x01;
			 else
				*bit_a = 0x00;
				bit_a++;
				ch[cnt]=ch[cnt]<<1;
			} 
	    }    
		return 1;
	}  
	  
//½«¶þ½øÖÆÎ»´®×ªÎª³¤¶ÈÎª8µÄ×Ö·û´®  
void Bit64ToChar8(uint8_t bit_a[64],uint8_t ch[8]){  
    	char cnt,cnt1;  
    	memset(ch,0,8);  
	    for(cnt = 0; cnt < 8; cnt++){
		  
	         for(cnt1 = 0;cnt1 < 8; cnt1++){  
			 ch[cnt]=ch[cnt]<<1;
			 ch[cnt]|= *bit_a;
			 bit_a++ ;		       
	    	}   
	    } 
		  
    } 

//ÃÜÔ¿ÖÃ»»1  
void DES_PC1_Transform(uint8_t key[64],uint8_t tempbts[56]){  
	     uint8_t cnt; 
	     uint8_t PC_1[56] = {
		 						56,48,40,32,24,16,8,  
	              			 	0,57,49,41,33,25,17,  
	              				9,1,58,50,42,34,26,  
	              				18,10,2,59,51,43,35,  
	              				62,54,46,38,30,22,14,  
	              				6,61,53,45,37,29,21,  
	              				13,5,60,52,44,36,28,  
	              				20,12,4,27,19,11,3  };  

	    for(cnt = 0; cnt < 56; cnt++){  
	        tempbts[cnt] = key[PC_1[cnt]];  
	    }  
	}  
	  
//ÃÜÔ¿ÖÃ»»2  
void DES_PC2_Transform(uint8_t key[56], uint8_t tempbts[48]){  
	    uint8_t cnt;  
	    uint8_t PC_2[48] = {
								13,16,10,23,0,4,2,27,  
	              				14,5,20,9,22,18,11,3,  
	              				25,7,15,6,26,19,12,1,  
	              				40,51,30,36,46,54,29,39,  
                  				50,44,32,47,43,48,38,55,  
	              				33,52,45,41,49,35,28,31}; 
	
	    for(cnt = 0; cnt < 48; cnt++){  
	        tempbts[cnt] = key[PC_2[cnt]];  
	    }  
	    
	}  
	  
//Ñ­»·×óÒÆ  
void DES_ROL(uint8_t *data_a,uint8_t time){     
	    uint8_t temp[56],i;  
	  
	    //±£´æ½«ÒªÑ­»·ÒÆ¶¯µ½×ó±ßµÄÎ»  
		for(i=0;i<time;i++)
		{
			temp[i] = *(data_a+i);
			temp[time+i] = *(data_a+28+i);
		}
	    
		for(i=0;i<=28-time;i++)
		{
			*(data_a+i) =  *(data_a+time+i) ;
			*(data_a+28+i) =  *(data_a+28+time+i);
		}
	    
		for(i=0;i<time;i++)
		{
			*(data_a+28-time+i) = temp[i];
			*(data_a+56-time+i) = temp[i+time];
		}
	   
	}
	 
//Ñ­»·ÓÒÒÆ 
void DES_ROR(uint8_t *data_a,uint8_t time){     
	    uint8_t temp[56],i;  

		//±£´æ½«ÒªÑ­»·ÒÆ¶¯µ½ÓÒ±ßµÄÎ»  
		for(i=0;i<time;i++)
		{
			temp[time-1-i] = *(data_a+28-1-i);
			temp[time+1-i] = *(data_a+56-1-i);
		}
	     
		for(i=0;i<=28-time;i++)
		{
			*(data_a+27-i) =  *(data_a+27-time-i) ;
			*(data_a+55-i) =  *(data_a+55-time-i);
		}
	    
		for(i=0;i<time;i++)
		{
			*(data_a+i) = temp[i];
			*(data_a+28+i) = temp[i+2];
		}	   
	}

//IPÖÃ»» 
void DES_IP_Transform(uint8_t data_a[64]){  
	    uint8_t cnt;  
	    uint8_t temp[64]; 
	  	uint8_t IP_Table[64] = {  
									57,49,41,33,25,17,9,1,  
	                      			59,51,43,35,27,19,11,3,  
	                      			61,53,45,37,29,21,13,5,  
	                      			63,55,47,39,31,23,15,7,  
	                      			56,48,40,32,24,16,8,0,  
	                      			58,50,42,34,26,18,10,2,  
	                      			60,52,44,36,28,20,12,4,  
	                      			62,54,46,38,30,22,14,6 }; 
	  					
	    for(cnt = 0; cnt < 64; cnt++){  
	        temp[cnt] = data_a[IP_Table[cnt]];  
	    }  
	    memcpy(data_a,temp,64);  
	    
	}  
	  
//IPÄæÖÃ»»  
void DES_IP_1_Transform(uint8_t data_a[64]){  
		 uint8_t cnt;  
		 uint8_t temp[64]; 
		  	
		 uint8_t IP_1_Table[64] = {
										39,7,47,15,55,23,63,31,  
		                       			38,6,46,14,54,22,62,30,  
		                       			37,5,45,13,53,21,61,29,  
		                       			36,4,44,12,52,20,60,28,  
		                       			35,3,43,11,51,19,59,27,  
		                       			34,2,42,10,50,18,58,26,  
		                       			33,1,41,9,49,17,57,25,  
		                       			32,0,40,8,48,16,56,24  }; 
		 for(cnt = 0; cnt < 64; cnt++){  
		     temp[cnt] = data_a[IP_1_Table[cnt]];  
		    }  
		 memcpy(data_a,temp,64);  	 
	}  
	  
//À©Õ¹ÖÃ»»  
void DES_E_Transform(uint8_t data_a[48]){  
	    uint8_t cnt;  
	    uint8_t temp[48]; 
 		uint8_t E_Table[48] = {
									31,0,1,2,3,4,
	                   				3,4,5,6,7,8,
	                   				7,8,9,10,11,12,  
	                   				11,12,13,14,15,16,  
	                   				15,16,17,18,19,20,  
	                   				19,20,21,22,23,24,  
	                   				23,24,25,26,27,28,  
	                   				27,28,29,30,31,0}; 
	  
	    for(cnt = 0; cnt < 48; cnt++){  
	        temp[cnt] = data_a[E_Table[cnt]];  
	    }     

	    memcpy(data_a,temp,48);  

	}  
  
//PÖÃ»»  
void DES_P_Transform(uint8_t data_a[32]){  
	    uint8_t cnt;  
	    uint8_t temp[32]; 
		uint8_t P_Table[32] = {
									15,6,19,20,28,11,27,16,  
	                  				0,14,22,25,4,17,30,9,  
	                  				1,7,23,13,31,26,2,8,  
	                  				18,12,29,5,21,10,3,24};
									  
	    for(cnt = 0; cnt < 32; cnt++){  
	        temp[cnt] = data_a[P_Table[cnt]];  
	    }     
	    memcpy(data_a,temp,32);  

	}  
	  
//Òì»ò  
void DES_XOR(uint8_t R[48], uint8_t L[48] ,uint8_t count){  
	   uint8_t cnt;  
	    for(cnt = 0; cnt < count; cnt++){  
	        R[cnt] ^= L[cnt];  
	    }  

	}  
	  
//SºÐÖÃ»»  
				   
void DES_SBOX(uint8_t data_a[48]){  
	    		 		
		uint8_t cnt;  
	    uint8_t lines,row;  
	    uint8_t cur1,cur2;
		uint8_t output ;
		//Äæ³õÊ¼ÖÃ»»±íIP^-1  
  
	    for(cnt = 0; cnt < 8; cnt++){  
	        cur1 = cnt*6;  
	        cur2 = cnt<<2;  
	          
	        //¼ÆËãÔÚSºÐÖÐµÄÐÐÓëÁÐ  
	        lines = (data_a[cur1]<<1) + data_a[cur1+5];  
	        row = (data_a[cur1+1]<<3) + (data_a[cur1+2]<<2)  
	            + (data_a[cur1+3]<<1) + data_a[cur1+4];
			if(cnt<4)	  
	        	output = S[cnt][lines][row];
			else
			{
				
				output = S1[cnt-4][lines][row];  
	  		}
        //»¯Îª2½øÖÆ  
	        data_a[cur2] = (output&0X08)>>3;  
	        data_a[cur2+1] = (output&0X04)>>2;  
	        data_a[cur2+2] = (output&0X02)>>1;  
	        data_a[cur2+3] = output&0x01;  
	    }     
	 
	}  
	  
//½»»»  
void DES_Swap(uint8_t left[32], uint8_t right[32]){  
	    uint8_t temp[32];  
	    memcpy(temp,left,32);     
	    memcpy(left,right,32);    
	    memcpy(right,temp,32);  
 
	}  	
	

  	  
//¼ÓÃÜµ¥¸ö·Ö×é  
void encrypt_des(uint8_t *inoutdata ,uint8_t *keyStr){  

	    uint8_t plainBits[64];  
	    uint8_t copyRight[48]; 
		uint8_t keyBlock[8];  
	    uint8_t bKey[64];  
	    uint8_t subKeys[48];  
		uint8_t temp[56]; 
	    uint8_t cnt;  
	  	uint8_t MOVE_TIMES[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

	    memcpy(keyBlock,keyStr,8);  
	    //½«ÃÜÔ¿×ª»»Îª¶þ½øÖÆÁ÷  
	    Char8ToBit64(keyBlock,bKey);  
	    
 
	    DES_PC1_Transform(bKey,temp);//PC1ÖÃ»»  	 
	    	    
	    Char8ToBit64(inoutdata,plainBits);       
	    //³õÊ¼ÖÃ»»£¨IPÖÃ»»£©  
	    DES_IP_Transform(plainBits);  
  															    
	    
	    for(cnt = 0; cnt < 16; cnt++){     
		
			DES_ROL(temp,MOVE_TIMES[cnt]);		//×óÒÆ
			DES_PC2_Transform(temp,subKeys);	//Éú³É×ÓÃÜÔ¿  
		//	DES_MakeSubKeys(subKeys,cnt);    
	        memcpy(copyRight,plainBits+32,32);  
	        //½«ÓÒ°ë²¿·Ö½øÐÐÀ©Õ¹ÖÃ»»£¬´Ó32Î»À©Õ¹µ½48Î»  
	        DES_E_Transform(copyRight);  
	        //½«ÓÒ°ë²¿·ÖÓë×ÓÃÜÔ¿½øÐÐÒì»ò²Ù×÷  
			  
        	DES_XOR(copyRight,subKeys,48);   
	        //Òì»ò½á¹û½øÈëSºÐ£¬Êä³ö32Î»½á¹û  

	        DES_SBOX(copyRight);  
	        //PÖÃ»»  
	        DES_P_Transform(copyRight);  
	        //½«Ã÷ÎÄ×ó°ë²¿·ÖÓëÓÒ°ë²¿·Ö½øÐÐÒì»ò  
	        DES_XOR(plainBits,copyRight,32);  
	        if(cnt != 15){  
	            //×îÖÕÍê³É×óÓÒ²¿µÄ½»»»  
	            DES_Swap(plainBits,plainBits+32);  
	        }  
	    }  
	    //Äæ³õÊ¼ÖÃ»»£¨IP^1ÖÃ»»£©  
	    DES_IP_1_Transform(plainBits);  
	    Bit64ToChar8(plainBits,inoutdata);  
 
	}  

	
//½âÃÜµ¥¸ö·Ö×é  
void decrypt_des(uint8_t *inoutdata,uint8_t *keyStr){  
	    uint8_t cipherBits[64];  
	    uint8_t copyRight[48];  
		uint8_t keyBlock[8];  
	    uint8_t bKey[64];  
		uint8_t temp[56];
		uint8_t subKeys[48];	  
	    uint8_t cnt;  			   
	 	uint8_t MOVE_TIMES[16] = {0,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
		memcpy(keyBlock,keyStr,8);   
	    //½«ÃÜÔ¿×ª»»Îª¶þ½øÖÆÁ÷  
	    Char8ToBit64(keyBlock,bKey);		
		DES_PC1_Transform(bKey,temp);	 //PC1ÖÃ»»
	    Char8ToBit64(inoutdata,cipherBits);         
	    //³õÊ¼ÖÃ»»£¨IPÖÃ»»£©  
	    DES_IP_Transform(cipherBits);  
	      
	    //16ÂÖµü´ú  
	    for(cnt = 0; cnt <16; cnt++){   
		    
			if(cnt !=0) 
			{ 
				DES_ROR(temp,MOVE_TIMES[cnt]);	 //ÓÒÒÆ
			}
			DES_PC2_Transform(temp,subKeys);	 //Éú³É×ÓÃÜÔ¿ 

	        memcpy(copyRight,cipherBits+32,32);  
	        //½«ÓÒ°ë²¿·Ö½øÐÐÀ©Õ¹ÖÃ»»£¬´Ó32Î»À©Õ¹µ½48Î»  
	        DES_E_Transform(copyRight);  
	        //½«ÓÒ°ë²¿·ÖÓë×ÓÃÜÔ¿½øÐÐÒì»ò²Ù×÷  
        	DES_XOR(copyRight,subKeys,48);       
	        //Òì»ò½á¹û½øÈëSºÐ£¬Êä³ö32Î»½á¹û  
	        DES_SBOX(copyRight);  
	        //PÖÃ»»  
	        DES_P_Transform(copyRight);       
	        //½«Ã÷ÎÄ×ó°ë²¿·ÖÓëÓÒ°ë²¿·Ö½øÐÐÒì»ò  
	        DES_XOR(cipherBits,copyRight,32);  
	        if(cnt != 15){  
	            //×îÖÕÍê³É×óÓÒ²¿µÄ½»»»  
	            DES_Swap(cipherBits,cipherBits+32);  
	        }  
	    }  
	    //Äæ³õÊ¼ÖÃ»»£¨IP^1ÖÃ»»£©  
	    DES_IP_1_Transform(cipherBits);  
	    Bit64ToChar8(cipherBits,inoutdata);  
	}  		  
	    



 /*void CbcDes_encrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key)
{
	unsigned char i , j,time , k=0 ,k1=0;
	
	time = MsgIn[0] / 8;
	for(i=0; i<time; i++)
	{
		if(i==0)
		{
			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+1]^iv[j];
			encrypt_des(MsgIn+1,Key);					
			for(j=0;j<8;j++)
				outbuf2[j]= MsgIn[j+1];
	   }
	   else
	   {
			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+k+1]^outbuf2[j+k1]; 
			encrypt_des(MsgIn+1,Key);
			for(j=0;j<8;j++)
				outbuf2[j+k]= MsgIn[j+1];
				k1+=8;
		}
		k+=8;
	}
	memcpy(MsgIn+1,outbuf2,time*8); 
	
}



void CbcDes_decrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key)
{
	unsigned char i , j,time , k=0 ,k1=0;
	 
	time = MsgIn[0] / 8;
	for(i=0; i<time; i++)
	{
		if(i==0)
		{
			memcpy(outbuf1,MsgIn+1,8);
			decrypt_des(MsgIn+1,Key);	
			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+1]^iv[j];				
			for(j=0;j<8;j++)
				outbuf[j]= MsgIn[j+1];
	   }
	   else
	   {
			memcpy(outbuf1+k,MsgIn+k+1,8);
			decrypt_des(MsgIn+k+1,Key);
			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+k+1]^outbuf1[j+k1]; 
			for(j=0;j<8;j++)
				outbuf[j+k]= MsgIn[j+1];
				k1+=8;
		}
		k+=8;
	}
		memcpy(MsgIn+1,outbuf,time*8); 
} */

 /**********CBCÄ£Ê½DES¼ÓÃÜ**********/
 void CbcDes_encrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key)
{
	unsigned char  j;


			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+1]^iv[j];
			encrypt_des(MsgIn+1,Key);					
			for(j=0;j<8;j++)
				outbuf2[j]= MsgIn[j+1];
	 
	memcpy(MsgIn+1,outbuf2,8); 
	
}


 /**********CBCÄ£Ê½DES½âÃÜ**********/
void CbcDes_decrypt(unsigned char *iv,unsigned char *MsgIn, unsigned char *Key)
{
	unsigned char  j;
	 


			memcpy(outbuf1,MsgIn+1,8);
			decrypt_des(MsgIn+1,Key);	
			for(j=0;j<8;j++)
				MsgIn[j+1]= MsgIn[j+1]^iv[j];				
			for(j=0;j<8;j++)
				outbuf[j]= MsgIn[j+1];
	  
	
		memcpy(MsgIn+1,outbuf,8); 
}

  /**********CBCÄ£Ê½3DES¼ÓÃÜ**********
  µÚÒ»¸ö²ÎÊý*ivÎª³õÊ¼ÏòÁ¿³¤¶ÈÎª8×Ö½Ú
  µÚ¶þ¸ö²ÎÊý*inoutdata±íÊ¾Ã÷ÎÄºÍÃÜÎÄÊý¾Ý£¬×¢ÒâÊý¾ÝÇ°ÃæÒª¼ÓÉÏ³¤¶È£¬¼ÓÃÜºóµÄÊý¾ÝÒ²»á´æµ½*inoutdataÀï
  µÚÈý¸ö²ÎÊý*keyStrÎª16×Ö½Ú¼ÓÃÜÃÜÔ¿
  ***/

void Cbcencrypt_3des(unsigned char *iv,uint8_t *inoutdata,uint8_t *keyStr){
	
	uint8_t uszkeytmp[8] , time;
	uint8_t iv1[8];
	unsigned char i , k=0 ,k1=0;

	time = inoutdata[0] / 8; 
	for(i=0; i<time; i++)
	{
		if(i==0)
		{
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_encrypt(iv,inoutdata,uszkeytmp);
	
			memcpy(uszkeytmp,keyStr+8,8);
			CbcDes_decrypt(iv,inoutdata,uszkeytmp);
		
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_encrypt(iv,inoutdata,uszkeytmp);	
	   }
	 else
	   {
			memcpy(iv1,inoutdata+1+k1,8);
	
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_encrypt(iv1,inoutdata+k,uszkeytmp);
	
			memcpy(uszkeytmp,keyStr+8,8);
			CbcDes_decrypt(iv1,inoutdata+k,uszkeytmp);
		
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_encrypt(iv1,inoutdata+k,uszkeytmp);
			k1+=8;
		}
		k+=8;
	}

		return;
} 
/**********CBCÄ£Ê½3DES½âÃÜ***********
  µÚÒ»¸ö²ÎÊý*ivÎª³õÊ¼ÏòÁ¿³¤¶ÈÎª8×Ö½Ú
  µÚ¶þ¸ö²ÎÊý*inoutdata±íÊ¾ÃÜÎÄºÍÃ÷ÎÄÊý¾Ý£¬×¢ÒâÊý¾ÝÇ°ÃæÒª¼ÓÉÏ³¤¶È£¬½âÃÜºóµÄÊý¾ÝÒ²»á´æµ½*inoutdataÀï
  µÚÈý¸ö²ÎÊý*keyStrÎª16×Ö½Ú¼ÓÃÜÃÜÔ¿
  ***/
void Cbcdecrypt_3des(unsigned char *iv,uint8_t *inoutdata ,uint8_t *keyStr){
		
	uint8_t uszkeytmp[8] , time;
	uint8_t iv2[8];
	uint8_t iv1[8];
	unsigned char i , k=0 , k1=0;

	time = inoutdata[0] / 8; 	
	for(i=0; i<time; i++)
	{
		if(i==0)
		{
			memcpy(iv1,inoutdata+1,8);
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_decrypt(iv,inoutdata,uszkeytmp);
	
			memcpy(uszkeytmp,keyStr+8,8);
			CbcDes_encrypt(iv,inoutdata,uszkeytmp);
		
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_decrypt(iv,inoutdata,uszkeytmp);
	   }
	   else
	   {
			memcpy(iv2,inoutdata+1+k,8);				
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_decrypt(iv1,inoutdata+k,uszkeytmp);
	
			memcpy(uszkeytmp,keyStr+8,8);
			CbcDes_encrypt(iv1,inoutdata+k,uszkeytmp);
		
			memcpy(uszkeytmp,keyStr,8);
			CbcDes_decrypt(iv1,inoutdata+k,uszkeytmp);
			k1+=8;	    
			memcpy(iv1,iv2,8);	
		}
		k+=8;
	}	 
		return;
} 

 /**********3DES¼ÓÃÜ*************
  µÚÒ»¸ö²ÎÊýinoutdata±íÊ¾Ã÷ÎÄºÍÃÜÎÄÊý¾Ý£¬×¢ÒâÊý¾ÝÇ°ÃæÒª¼ÓÉÏ³¤¶È£¬¼ÓÃÜºóµÄÊý¾ÝÒ²»á´æµ½*inoutdataÀï
  µÚ¶þ¸ö²ÎÊýý*keyStrÎª16×Ö½Ú¼ÓÃÜÃÜÔ¿
  ***/
void encrypt_3des(uint8_t *inoutdata,uint8_t *keyStr){
	
		/*uint8_t  uszkeytmp[8];
		//16×Ö½Ú×ó°ë²¿·ÖDES½âÃÜ
		memcpy(uszkeytmp,keyStr,8);
		encrypt_des(inoutdata,uszkeytmp);
		//16×Ö½ÚÓÒ°ë²¿·Ödes¼ÓÃÜ
		memcpy(uszkeytmp,keyStr+8,8);
		decrypt_des(inoutdata,uszkeytmp);
		//16×Ö½Ú×ó°ë²¿·Ödes½âÃÜ
		memcpy(uszkeytmp,keyStr,8);
		encrypt_des(inoutdata,uszkeytmp);
		return;	  */

		uint8_t  uszkeytmp[8];
		uint8_t  uszkeytmp1[8];
		uint8_t i,j;
		int k=1;
		i=inoutdata[0];
		memcpy(uszkeytmp,keyStr,8);
		memcpy(uszkeytmp1,keyStr+8,8);
		 
		if((i%8)!=0)
		{
			inoutdata[i+1]=0x80;
			for(j=0;j<(i/8)+1;j++)		
			{
				//16×Ö½Ú×ó°ë²¿·ÖDES¼ÓÃÜ		
				encrypt_des(inoutdata+k,uszkeytmp);
				//16×Ö½ÚÓÒ°ë²¿·ÖDES½âÃÜ
				decrypt_des(inoutdata+k,uszkeytmp1);
				//16×Ö½Ú×ó°ë²¿·ÖDES¼ÓÃÜ
				encrypt_des(inoutdata+k,uszkeytmp);
				k+=8;
			}
		}
		else
		{
			for(j=0;j<i/8;j++)		
			{
				//16×Ö½Ú×ó°ë²¿·ÖDES¼ÓÃÜ		
				encrypt_des(inoutdata+k,uszkeytmp);
				//16×Ö½ÚÓÒ°ë²¿·ÖDES½âÃÜ
				decrypt_des(inoutdata+k,uszkeytmp1);
				//16×Ö½Ú×ó°ë²¿·ÖDES¼ÓÃÜ
				encrypt_des(inoutdata+k,uszkeytmp);
				k+=8;
			}
		}
		return;


} 
/**********3DES½âÃÜ*******************
  µÚÒ»¸ö²ÎÊýinoutdata±íÊ¾Ã÷ÎÄºÍÃÜÎÄÊý¾Ý£¬×¢ÒâÊý¾ÝÇ°ÃæÒª¼ÓÉÏ³¤¶È£¬¼ÓÃÜºóµÄÊý¾ÝÒ²»á´æµ½*inoutdataÀï
  µÚ¶þ¸ö²ÎÊýkeyStrÎª16×Ö½Ú½âÃÜÃÜÔ¿
  ***/
void decrypt_3des(uint8_t *inoutdata ,uint8_t *keyStr){
		
		uint8_t  uszkeytmp[8];
		uint8_t  uszkeytmp1[8];
		uint8_t i,j;
		int k=1;
		memcpy(uszkeytmp,keyStr,8);
		memcpy(uszkeytmp1,keyStr+8,8);

		i=inoutdata[0];
		if((i%8)!=0)
			i=((i/8)+1)*8;
			for(j=0;j<i/8;j++)		
			{
				//16×Ö½Ú×ó°ë²¿·ÖDES½âÃÜ		
				decrypt_des(inoutdata+k,uszkeytmp);
				//16×Ö½ÚÓÒ°ë²¿·Ödes¼ÓÃÜ
				encrypt_des(inoutdata+k,uszkeytmp1);
				//16×Ö½Ú×ó°ë²¿·Ödes½âÃÜ
				decrypt_des(inoutdata+k,uszkeytmp);
				k+=8;
			}
		
		return;
} 
