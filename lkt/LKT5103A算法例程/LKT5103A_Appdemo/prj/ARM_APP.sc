;=========================================================================
;* LKT4208
;=========================================================================
;* @file    *.sc
;* @brief   scatter file for armlink.exe
;=========================================================================
   
ROM 0x030000 
{
	ER_RO 0x30000 0x10000 
	{
 		* (RESET, +FIRST)	
        *.o (+RO)	
	}

	ER_RM 0x0D4000 
	{
		* (+RW)
	} 

	ER_ZI +0x00 
	{
		* (+ZI)
	}
}