#ifndef __CULSTD_H__
#define __CULSTD_H__
#include "cul_macro.h"

S32 cul_memcmp(S8 *pBuffer1, S8 *pBuffer2, U32 nCount);
void cul_memcpy(S8 *pTarget, S8 *pSrc, U32 nSize);
void cul_memset(void *pBuffer, S8 ch, U32 nSize);
S32 cul_strcmp(S8 *strOne, S8 *strTwo);
U32 cul_strlen(U8 *strString);
S32 cul_strncmp(S8 *strOne, S8 *strTwo, U32 nCount);
S32 cul_stricmp(S8 *strOne, S8 *strTwo);
void cul_strcpy(U8 *strTarget, U8 *strSource);
void cul_strncpy(S8 *strTarget, S8 *strSource, U32 nSize);
void cul_strcat(U8 *strTarget, U8 *strSource);
S8* cul_strchr(S8 *strString, U8 ch);
S8* cul_strstr(U8* strString_IN,U8* strPattern_IN);
S32 cul_atoi(S8 *strString);
S32 cul_abs(S32 nInt);
S32 cul_sprintf( S8 *pBuffer, const S8 *format, ...);

void* cul_malloc(U32 nSize);
void cul_free(void* p);



#endif
