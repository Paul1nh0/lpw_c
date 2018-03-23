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
         佛祖保佑       永无BUG
*/

#ifndef __CULMACRO_H__
#define __CULMACRO_H__

/*宏开关放到makefile中 版本v0.6.0.0 绿皮蛙修改*/
/*#include "culSwitch.h"  版本开关 控制编译成哪个平台的版本以及内存方式等 */
/*include头文件的方式修改 使之更合理 版本v0.6.0.0 绿皮蛙修改*/
/*#include "culHeader.h"  需要包含的系统的文件以及各模块头文件*/
/*#include "cul_string.h" 一些常量字符串的定义*/

/*版本说明 Version+大版本号+商户名称个性化(如果有)*/
#define VERSION_V00600 "v0600"
#define MCHT_STD  "mcht_std"

#define CURRENT_VERSION VERSION_V00600
#define CURRENT_MCHT MCHT_STD

/*64位系统指针需要64位,现在都编译成32位系统可以运行的程序,不对64位做专门的优化*/
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


/*windows平台兼容*/
#ifndef size_t
typedef unsigned int size_t;
#endif

#ifdef CL
#define STDCALL __stdcall /*编译器调用约定*/
#elif defined GCC
#define STDCALL _stacall 
#endif

/*宏函数定义*/
#define STRUCT_COPY(dst,src) cul_memcpy(dst,src,sizeof(dst))

#define DELETE_POINTER(p)       \
    do                          \
    {                           \
        if(NULL != p)           \
        	free(p);           \
        p = NULL;               \
    }while(0)  

#endif
