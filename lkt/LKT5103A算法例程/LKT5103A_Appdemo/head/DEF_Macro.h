/*
LKT4302A
 */

/**
 * @file    DEF_Macro.h
 *
 * $Revision$
 * $Date$
 * $Author$
 */



/*** Header define ************************************************************/
#ifndef __DEF_MACRO_H__
#define __DEF_MACRO_H__


/*** SFR access ***************************************************************/
#define BIT(bit)					(0x1u << (bit))

#define	BIT_CLR(val, bit)			(val) &= (~(unsigned int)(bit))
#define BIT_SET(val, bit)			(val) |= ((unsigned int)(bit))

#define SFR_SET(sfr, val)			(sfr) = (val)
#define	SFR_BIT_CLR(sfr, bit)		BIT_CLR(sfr, bit)
#define SFR_BIT_SET(sfr, bit)		BIT_SET(sfr, bit)

#define WAIT_SFR_BIT_CLR(sfr, bit)	while((sfr) & (bit))	///<wait until bit is set
#define WAIT_SFR_BIT_SET(sfr, bit)	while(!((sfr) & (bit)))	///<wait until bit is cleared

/*** Misc utility *************************************************************/
// opcode
#define	NOP							__asm { nop} 	
#define	NOP2						NOP;NOP
#define	NOP3						NOP;NOP;NOP
#define	NOP5						NOP;NOP;NOP;NOP;NOP
#define	NOP10						NOP5;NOP5
#define	NOP15						NOP10;NOP5
#define	NOP30						NOP10;NOP10;NOP10

#define SYMBOL_OFFSET(from, to)		(((u32)to > (u32)from) ? ((u32)to - (u32)from) : -1*((u32)from - (u32)to))
#define BRANCH(offset)				(u32)(0xEA000000 | (0xFFFFFF & ((offset - 8) >> 2)))		///< Make Branch instruction

#define MIN_VAL(a,b)				(((a) < (b)) ? (a) : (b))
#define MAX_VAL(a,b)				(((a) < (b)) ? (b) : (a))
#define MOD_VAL(a,b)				((a) & ((b) - 1))
#define SQUARE(a)					((a) * ((a))

#define ALIGN(size, align)			(((size) + ((align) - 1)) & ~((align) - 1))
#define IS_ALIGN(size, align)		((size) == ALIGN((size), (align)))

/*** Endian utility *************************************************************/
#define SWAP16(s)							\
	(u16)(									\
		(((s) & 0xff) << 8) |				\
		(((s) & 0xff00) >> 8)				\
	)
#define SWAP32(l)							\
	(u32)(									\
		(((l) & 0xff) << 24) |				\
		(((l) & 0xff00) << 8) |				\
		(((l) & 0xff0000) >> 8) |			\
		(((l) & 0xff000000) >> 24)			\
	)

#ifdef CONFIG_LITTLE_ENDIAN
#define htons(s)						SWAP16(s)
#define htonl(l)						SWAP32(l)
#define ntohs(s)						SWAP16(s)
#define ntohl(l)						SWAP32(l)
#else
#define htons(s)						(s)
#define htonl(l)						(l)
#define ntohs(s)						(s)
#define ntohl(l)						(l)
#endif

// get numberic data
#define DWORD_HI_WORD(l)				((u16)((((u32)(l)) >> 16) & 0xFFFF))
#define DWORD_LO_WORD(l)				((u16)(u32)(l))
#define WORD_HI_BYTE(w)					((u8)(((u16)(w) >> 8) & 0xFF))
#define WORD_LO_BYTE(w)					((u8)(w))

#define	DWORD_LSB_BYTE(l)				((u8)(l))
#define	DWORD_2ND_BYTE(l)				((u8)((l) >> 8))
#define	DWORD_3RD_BYTE(l)				((u8)((l) >> 16))
#define	DWORD_MSB_BYTE(l)				((u8)((l) >> 24))

#define MAKE_WORD(lsb, msb)					\
	(u16)(									\
		((lsb))					|			\
		((msb) << 8)						\
	)

#define MAKE_DWORD(lsb, b2, b3, msb)		\
	(u32)(									\
		((lsb))					|			\
		((b2) << 8)				|			\
		((b3) << 16)			|			\
		((msb) << 24)						\
	)

// access to little buffer
#define SET_WORD_TO_LBUF(buf, word)			\
	((u8 *)(buf))[0] = ((u8)((word) >> 0));	\
	((u8 *)(buf))[1] = ((u8)((word) >> 8));	\

#define SET_DWORD_TO_LBUF(buf, dword)			\
	((u8 *)(buf))[0] = ((u8)((dword) >> 0));	\
	((u8 *)(buf))[1] = ((u8)((dword) >> 8));	\
	((u8 *)(buf))[2] = ((u8)((dword) >> 16));	\
	((u8 *)(buf))[3] = ((u8)((dword) >> 24));

#define GET_WORD_FROM_LBUF(buf)				\
	(u16)(									\
		((((u8 *)(buf))[0]) << 0)	|		\
		((((u8 *)(buf))[1]) << 8))			\

#define GET_DWORD_FROM_LBUF(buf)			\
	(u32)(									\
		((((u8 *)(buf))[0]) << 0)	|		\
		((((u8 *)(buf))[1]) << 8)	|		\
		((((u8 *)(buf))[2]) << 16)	|		\
		((((u8 *)(buf))[3]) << 24))

// access to big buffer
#define SET_DWORD_TO_BBUF(buf, dword)			\
	((u8 *)(buf))[3] = ((u8)((dword) >> 0));	\
	((u8 *)(buf))[2] = ((u8)((dword) >> 8));	\
	((u8 *)(buf))[1] = ((u8)((dword) >> 16));	\
	((u8 *)(buf))[0] = ((u8)((dword) >> 24));

#define GET_DWORD_FROM_BBUF(buf)			\
	(u32)(									\
		((((u8 *)(buf))[3]) << 0)	|		\
		((((u8 *)(buf))[2]) << 8)	|		\
		((((u8 *)(buf))[1]) << 16)	|		\
		((((u8 *)(buf))[0]) << 24))

/*** Debug utility **************************************************************/
#ifdef CONFIG_DEBUG_SEMIHOST
//	#define DBG_PRINTF(args...)		printf(args)			// CONFIG_TOOL == GCC, GNU CPP
	#define DBG_PRINTF(...)			printf(__VA_ARGS__)		// CONFIG_TOOL == ADS/RVDS, C99
#else
	#define DBG_PRINTF(...)
#endif

#ifdef CONFIG_DEBUG
#define DBG_ASSERT(expr) {				\
	if(!(expr))							\
	{									\
		DBG_PRINTF("[%s] Asserted on file %s line %s\n",	\
			CONFIG_PRJ_NAME, __FILE__, __LINE__);			\
		SYS_Error();										\
	}									\
}
#define DBG_ABORT(expr)		DBG_ASSERT(!(expr))
#else
#define DBG_ASSERT(expr)
#define DBG_ABORT(expr)
#endif

#endif	///< __DEF_MACRO_H__
