/******************************************************************************

                  版权所有 (C), 上海银商资讯有限公司

 ******************************************************************************
  @file    cul_std_string.c
  @version 初稿
  @author  绿皮蛙
  @date    2016年10月26日
  @email   wangly@upcard.com.cn
  @brief   标准C语言内存操作函数的一个子集实现
  函数列表   :
              cul_abs
              cul_atoi
              cul_free
              cul_malloc
              cul_memcmp
              cul_memcpy
              cul_memset
              cul_sprintf
              cul_strcat
              cul_strchr
              cul_strcmp
              cul_strcpy
              cul_stricmp
              cul_strlen
              cul_strncmp
              cul_strncpy
              cul_strstr
  修改历史   :
  1.日    期   : 2016年10月26日
    作    者   : 绿皮蛙
    修改内容   : 创建文件

******************************************************************************/

/*----------------------------------------------*
 * 包含头文件                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部变量说明                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 外部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 内部函数原型说明                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 全局变量                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 模块级变量                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 常量定义                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * 宏定义                                       *
 *----------------------------------------------*/

#include "cul_std_string.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"
#include "string.h"

S32 cul_memcmp(S8 *pBuffer1, S8 *pBuffer2, U32 nCount)
{
#ifdef ANSI_C_SUPPORT
    U8 charOne, charTwo;
    U32 i=0;

    if(PNULL == pBuffer1 || PNULL == pBuffer2) return -1;
    if(0 == nCount) return 0;
    while(1)
    {
        charOne=pBuffer1[i];
        charTwo=pBuffer2[i];
        if(charOne > charTwo) return 1;
        else if(charOne < charTwo) return -1;

        i ++;
        if(i == nCount) break;
    }

    return 0;
#else
    return memcmp(pBuffer1,pBuffer2,nCount);
#endif
}


void cul_memcpy(S8 *pTarget, S8 *pSrc, U32 nSize)
{
#ifdef ANSI_C_SUPPORT
    U32 i = 0;
    U32 lAddress_Target = (U32)pTarget;
    U32 lAddress_Source = (U32)pSrc;

    if(PNULL == pTarget || PNULL == pSrc) return;

    if(nSize > 0)
    {
        /*in case address overlaps*/
        if(lAddress_Target > lAddress_Source)
        {
            i = nSize - 1;
            while(1)
            {
                pTarget[i] = pSrc[i];
                if(0 == i) break;
                i --;
            }
        }
        else
        {
            for(i=0; i<nSize; i++)pTarget[i] = pSrc[i];
        }
    }
#else
    memcpy(pTarget,pSrc,nSize);
#endif
}

void cul_memset(void *pBuffer, S8 ch, U32 nSize)
{
#ifdef ANSI_C_SUPPORT
    S8 *pBuf = (S8 *)pBuffer;
    U32 i = 0;

    if(PNULL == pBuffer) return;
    for(i=0; i<nSize; i++)pBuf[i] = ch;
#else
    memset(pBuffer,ch,nSize);
#endif
}

S32 cul_strcmp(S8 *strOne, S8 *strTwo)
{
#ifdef ANSI_C_SUPPORT
    U8 charOne, charTwo;
    U32 i=0;
    if(PNULL == strOne || PNULL == strTwo) return -1;

    while(1)
    {
        charOne=strOne[i];
        charTwo=strTwo[i];
        if(charOne > charTwo) return 1;
        else if(charOne < charTwo) return -1;

        i ++;
        if('\0' == charOne || '\0' == charTwo) break;
    }

    return 0;
#else
    return strcmp(strOne,strTwo);
#endif
}


U32 cul_strlen(U8 *strString)
{
#ifdef ANSI_C_SUPPORT
    U32 nLen = 0;
    U8 charOne;
    if(PNULL == strString) return 0;
    while(1)
    {
        charOne = strString[nLen];
        if('\0' == charOne) break;
        nLen ++;
    }
    return nLen;
#else
    return strlen(strString);
#endif
}

S32 cul_strncmp(S8 *strOne, S8 *strTwo, U32 nCount)
{
#ifdef ANSI_C_SUPPORT
    U8 charOne, charTwo;
    U32 i=0;

    if(PNULL == strOne || PNULL == strTwo) return -1;
    if(0 == nCount) return 0;
    while(1)
    {
        charOne=strOne[i];
        charTwo=strTwo[i];
        if(charOne > charTwo) return 1;
        else if(charOne < charTwo) return -1;

        i ++;
        if(i == nCount) break;
        if('\0' == charOne && '\0' == charTwo) break;
    }

    return 0;
#else
    return strncmp(strOne,strTwo,nCount);
#endif
}



S32 cul_stricmp(S8 *strOne, S8 *strTwo)
{
    U8 charOne, charTwo;
    U32 i=0;

    if(PNULL == strOne || PNULL == strTwo) return -1;
    while(1)
    {
        charOne=strOne[i];
        charTwo=strTwo[i];

        if(charOne <= 'Z' && charOne >= 'A') charOne += 0x20;
        if(charTwo <= 'Z' && charTwo >= 'A') charTwo += 0x20;

        if('\0' == charOne || '\0' == charTwo) break;
        if(charOne != charTwo) break;

        i ++;

    }

    if(charOne > charTwo) return 1;
    if(charOne < charTwo) return -1;

    return 0;

}


void cul_strcpy(U8 *strTarget, U8 *strSource)
{
#ifdef ANSI_C_SUPPORT
    U32 lAddress_Target = (U32)strTarget;
    U32 lAddress_Source = (U32)strSource;

    U32 i=0;
    U32 nLen;

    if(PNULL == strTarget || PNULL == strSource) return;

    nLen = cul_strlen(strSource);
    if(nLen > 0)
    {
        /*in case address overlaps*/
        if(lAddress_Target > lAddress_Source)
        {
            i = nLen - 1;
            while(1)
            {
                strTarget[i] = strSource[i];
                if(0 == i) break;
                i --;
            }
        }
        else
        {
            for(i=0; i<nLen; i++)strTarget[i] = strSource[i];
        }
    }
    strTarget[nLen] = '\0';
#else
    strcpy(strTarget,strSource);
#endif
}



void cul_strncpy(S8 *strTarget, S8 *strSource, U32 nSize)
{
#ifdef ANSI_C_SUPPORT
    U32 lAddress_Target = (U32)strTarget;
    U32 lAddress_Source = (U32)strSource;
    U32 i=0;

    if(PNULL == strTarget || PNULL == strSource) return;
    if(nSize > 0)
    {
        if(lAddress_Target > lAddress_Source)
        {
            i = nSize - 1;
            while(1)
            {
                strTarget[i] = strSource[i];
                if(0 == i) break;
                i --;
            }
        }
        else
        {
            for(i=0; i<nSize; i++)strTarget[i] = strSource[i];
        }
    }

    strTarget[nSize] = '\0';
#else
    strncpy(strTarget,strSource,nSize);
#endif
}
 

void cul_strcat(U8 *strTarget, U8 *strSource)
{
#ifdef ANSI_C_SUPPORT
    U32 i=0, j = 0, nLen_Src, nLen_Target;
    U32 lAddress_Target = (U32)strTarget;
    U32 lAddress_Source = (U32)strSource;

    if(PNULL == strTarget || PNULL == strSource) return;


     nLen_Src = cul_strlen(strSource);
     nLen_Target = cul_strlen(strTarget);

     /*in case address overlaps...*/
     if(lAddress_Target > lAddress_Source)
     {
        if(nLen_Src > 0)
        {
            j = nLen_Target+nLen_Src-1;
            i = nLen_Src-1;
            while(1)
            {
                strTarget[j] = strSource[i];
                if(0 == i) break;
                j --;
                i --;
            }

        }
     }
     else
     {
         j = nLen_Target;
         for(i=0; i<nLen_Src; i++)strTarget[j++] = strSource[i];
     }


    strTarget[nLen_Target+nLen_Src] = '\0';
#else
    strcat(strTarget,strSource);
#endif
}

S8* cul_strchr(S8 *strString, U8 ch)
{
#ifdef ANSI_C_SUPPORT
    U8 charOne;
    U32 i;

    if(PNULL == strString) return PNULL;

    i = 0;
    while(1)
    {
        charOne = strString[i];
        if('\0' == charOne) break;
        if(ch == charOne) return (S8*)&strString[i];
        i++;
    }

    return PNULL;
#else
    return strchr(strString,ch);
#endif
}


/*---------------------------------------------------------
 |strstr_yt(...)
 |PURPOSE
 |    This API intends to implement the ANSI API strstr(...)
 |    based on the classical Boyer-Moore-Horspool algorithm.
 |
 |INPUT
 |    strString_IN: the string to search
 |    strPattern_IN: the pattern(sub-string), we assume its length does NOT
 |                    exceed 32767 to reduce stack size
 |
 |OUTPUT
 |    none
 |
 |RETURN VALUE
 |    It will returns a pointer if found; else PNULL;
 *----------------------------------------------------------*/
S8* cul_strstr(U8* strString_IN,U8* strPattern_IN)
{
#ifdef ANSI_C_SUPPORT
    /*Boyer-Moore-Horspool algorithm for searching pattern in a string...*/
    U8 YT_UCHAR_MAX = 255;
    S16 bad_char_skip[256]; /* bad character shift*/
    U32 nStrLen,nPatLen;
    U32 last, scan;

    U8 *strString, *strPattern;

    strString = (U8 *)strString_IN;
    strPattern = (U8 *)strPattern_IN;

    nStrLen = cul_strlen(strString);
    nPatLen = cul_strlen(strPattern);
    if(nPatLen > 32760) return PNULL;
    last = nPatLen - 1;

    /*Sanity checks on the parameters*/
    if (0 == nPatLen  || PNULL == strString || PNULL == strPattern)return PNULL;


    /* STEP 1 ---- Preprocess on pattern */
    for (scan = 0; scan <= YT_UCHAR_MAX; scan++ )bad_char_skip[scan] = (short)nPatLen;


    /*  C arrays have the first byte at [0], therefore:
       [nPatLen - 1] is the last byte of the array.

       Then populate it with the analysis of the strPattern */
    for (scan = 0; scan < last; scan ++)bad_char_skip[strPattern[scan]] = (short)(last - scan);

    /* Search the strString, while the strPattern can still be within it.*/
    while (nStrLen >= nPatLen)
    {
        /* scan from the end of the strPattern */
        for (scan = last; strString[scan] == strPattern[scan]; scan --)
            if (0 == scan)return (S8*)strString; /* If the first byte matches, we've found it.*/

        /* otherwise, we need to skip some bytes and start again.
        //   Note that here we are getting the skip value based on the last byte
        //   of strPattern, no matter where we didn't match. So if strPattern is: "abcd"
        //   then we are skipping based on 'd' and that value will be 4, and
        //   for "abcdd" we again skip on 'd' but the value will be only 1.
        //   The alternative of pretending that the mismatched character was
        //   the last character is slower in the normal case (Eg. finding
        //   "abcd" in "...azcd..." gives 4 by using 'd' but only
        //   4-2==2 using 'z'.  */
        nStrLen   -=  bad_char_skip[strString[last]];
        strString +=  bad_char_skip[strString[last]];
    }

    return PNULL;
#else
    return strstr(strString_IN,strPattern_IN);
#endif
}

S32 cul_atoi(S8 *strString)
{
#ifdef ANSI_C_SUPPORT
    U32 nShift = 0, i;
    U8 charOne;
    S32 nValue = 0;

    if(PNULL == strString) return 0;

    if('+' == strString[0] || '-' == strString[0])nShift = 1;
    i = nShift;
    while(1)
    {
        charOne = strString[i++];
        if('\0' == charOne) break;
        if(charOne <='9'&&charOne >= '0')
        {
            nValue *= 10;
            nValue += charOne - 0x30;
        }
    }

    if('-' == strString[0]) return (0 - nValue);
    return nValue;
#else
    return atoi(strString);
#endif
}

S32 cul_abs(S32 nInt)
{
#ifdef ANSI_C_SUPPORT
    if(nInt >= 0) return nInt;
    else return (0 - nInt);
#else
    return abs(nInt);
#endif

}

S32 cul_sprintf( S8 *pBuffer, const S8 *format, ...)
{
    va_list ap;
    S32 n;
    va_start(ap,format);
    n = vsprintf(pBuffer,format,ap);
    va_end(ap);
    return n;
}



void* cul_malloc(U32 nSize)
{
#ifdef ANSI_C_SUPPORT

#else
    return malloc(nSize);
#endif

}
    
void cul_free(void* p)
{
#ifdef ANSI_C_SUPPORT
    
#else
    free(p);
#endif
}






