/*
                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
         ���汣��       ����BUG
*/

#ifndef __CULMACRO_H__
#define __CULMACRO_H__

/*�꿪�طŵ�makefile�� �汾v0.6.0.0 ��Ƥ���޸�*/
/*#include "culSwitch.h"  �汾���� ���Ʊ�����ĸ�ƽ̨�İ汾�Լ��ڴ淽ʽ�� */
/*includeͷ�ļ��ķ�ʽ�޸� ʹ֮������ �汾v0.6.0.0 ��Ƥ���޸�*/
/*#include "culHeader.h"  ��Ҫ������ϵͳ���ļ��Լ���ģ��ͷ�ļ�*/
/*#include "cul_string.h" һЩ�����ַ����Ķ���*/

/*�汾˵�� Version+��汾��+�̻����Ƹ��Ի�(�����)*/
#define VERSION_V00600 "v0600"
#define MCHT_STD  "mcht_std"

#define CURRENT_VERSION VERSION_V00600
#define CURRENT_MCHT MCHT_STD

/*64λϵͳָ����Ҫ64λ,���ڶ������32λϵͳ�������еĳ���,����64λ��ר�ŵ��Ż�*/
typedef unsigned char U8;
typedef char S8;
typedef unsigned short U16;
typedef short S16;
typedef unsigned int U32;
typedef int S32;
typedef void* PVOID;

#ifndef NULL
#define NULL 0
#endif

#ifndef PNULL
#define PNULL ((void*)0)
#endif

#define IN
#define OUT


/*windowsƽ̨����*/
#ifndef size_t
typedef unsigned int size_t;
#endif

#ifdef CL
#define STDCALL __stdcall /*����������Լ��*/
#elif defined GCC
#define STDCALL _stacall 
#endif

/*�꺯������*/
#define STRUCT_COPY(dst,src) cul_memcpy(dst,src,sizeof(dst))

#define DELETE_POINTER(p)       \
    do                          \
    {                           \
        if(NULL != p)           \
        	free(p);           \
        p = NULL;               \
    }while(0)  

#endif
