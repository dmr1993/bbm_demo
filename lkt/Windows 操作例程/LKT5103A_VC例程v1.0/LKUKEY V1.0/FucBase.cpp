/*********************************************************
    文件名： FucBase.cpp             作者：LKT                           
    日期：   2014.07.03              版本：        
    功能：   实现常用的函数
    函数列表：   
    1. DelStr
    2. Hex2Byte
    修改记录：         
          <作者>   <时间>   <版本>   <修改目的>
***********************************************************/

#include "stdafx.h"
#include "FucBase.h"

/*************************************************
    函数名称：   DelStr     
    功能：       删除输入字符串中的一些字符       
    调用函数：   NULL    
    被调用函数： Hex2Byte    
    输入参数：   strIn                
    输出参数：   NULL    
    返回值：     strOut    
    其他：           
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
    函数名称：   Hex2Byte     
    功能：       将字符串转换为16进制    
    调用函数：   NULL    
    被调用函数：    
    输入参数：   strIn                
    输出参数：   datOut    
    返回值：     lenth, 输入字符串的长度    
    其他：           
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

