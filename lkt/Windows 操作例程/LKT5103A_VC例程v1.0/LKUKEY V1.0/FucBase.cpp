/*********************************************************
    �ļ����� FucBase.cpp             ���ߣ�LKT                           
    ���ڣ�   2014.07.03              �汾��        
    ���ܣ�   ʵ�ֳ��õĺ���
    �����б�   
    1. DelStr
    2. Hex2Byte
    �޸ļ�¼��         
          <����>   <ʱ��>   <�汾>   <�޸�Ŀ��>
***********************************************************/

#include "stdafx.h"
#include "FucBase.h"

/*************************************************
    �������ƣ�   DelStr     
    ���ܣ�       ɾ�������ַ����е�һЩ�ַ�       
    ���ú�����   NULL    
    �����ú����� Hex2Byte    
    ���������   strIn                
    ���������   NULL    
    ����ֵ��     strOut    
    ������           
*************************************************/
CString DelStr(CString strIn)
{
	CString strOut;
	strOut = strIn;	
    strOut.Remove(' ');   
	strOut.Remove(',');
	strOut.Remove('h');
	strOut.Remove('H');
	strOut.Remove(';');
    strOut.Remove('S');
	strOut.Remove('W');
	strOut.Remove('=');
	return strOut;	
}

/*************************************************
    �������ƣ�   Hex2Byte     
    ���ܣ�       ���ַ���ת��Ϊ16����    
    ���ú�����   NULL    
    �����ú�����    
    ���������   strIn                
    ���������   datOut    
    ����ֵ��     lenth, �����ַ����ĳ���    
    ������           
*************************************************/
int  Hex2Byte(CString strIn, byte *datOut)
{
	int i, j, k, leth;
	char charEven, charOdd;

	strIn = DelStr(strIn);
	strIn.MakeUpper();
	
	leth = strIn.GetLength();
	if ((leth >>= 1) == 0x00)
	{
		return 0;
	}

	if ((strIn[0] == 'F') && ((strIn[1] == '0') || (strIn[1] == '4')))
	{
		leth = leth - 2;
	}

	for (k = 0; k < leth; k++)
	{
		charEven = strIn.GetAt(2 * k);
		charOdd = strIn.GetAt(2 * k + 1);
		i = 16;
		j = 16;
		
		if ((charEven <= '9') && (charEven >= '0')) 
		{
			i = (charEven - '0');
		}
		else if ((charEven <= 'F') && (charEven >= 'A'))  
		{
			i = (charEven - 'A' + 10);
		}
		else 
		{
			return 0;
		}
		
		if ((charOdd <= '9') && (charOdd >= '0'))
		{
			j = (charOdd - '0');
		}
		else if ((charOdd <= 'F') && (charOdd >= 'A'))
		{
			j = (charOdd - 'A' + 10);
		}
		else
		{
			return 0;
		}

       	datOut[k] = (i << 4) + j;		
	} //end of for

	return (leth); 
}

