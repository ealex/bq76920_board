/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2011     */
/*------------------------------------------------------------------------*/

#ifndef _STRFUNC
#define _STRFUNC

#define _USE_XFUNC_OUT	1	/* 1: Use output functions */


#if _USE_XFUNC_OUT
	void xputc (char c);
	void xputs ( const char* str );
	void xsprintf (char* buff, const char* fmt, ...);
	#define DW_CHAR		sizeof(char)
	#define DW_SHORT	sizeof(short)
	#define DW_LONG		sizeof(long)
#endif

#endif
