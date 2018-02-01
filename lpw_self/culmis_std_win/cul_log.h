#ifndef __CULLOG_H__
#define __CULLOG_H__

#include "cul_macro.h"

#define MOD_INTERFACE 0
#define MOD_CONFIG 1
#define MOD_PINPAD 2
#define MOD_SOCKET 3
#define MOD_LUA_C 4
#define MOD_LUA_LUA 5
#define MOD_ISO8583 6

#define LOG_INTERFACE MOD_INTERFACE,__FILE__,__LINE__
#define LOG_CONFIG MOD_CONFIG,__FILE__,__LINE__
#define LOG_LUA MOD_LUA_C,__FILE__,__LINE__
#define LOG_8583 MOD_ISO8583,__FILE__,__LINE__
#define LOG_SOCKET MOD_SOCKET,__FILE__,__LINE__
#define LOG_PINPAD MOD_PINPAD,__FILE__,__LINE__


typedef struct
{
    S8* path; /*log如果需要输出到文件,这个表示文件的路径*/
    S8* str; /*log输出时的字符内存*/
    S8* encrypt_str;
    U32 str_len; /*字符内存最大长度*/
    U32 max_file_size;/*输出到文件时每个文件最大长度*/
    U32 max_file_number;/*输出到文件时文件最多个数*/
    U32 filter; /*log过滤,根据不同模块过滤log*/
    U32 output_method; /*log输出方式 如文件方式,OutputDebugString,printf等*/
    U32 encrypt_method; /*log加密方式*/
    S8* output_custom_func; /*output_method中指示需要自定义log输出方式,这个就是函数指针*/
    S8* encrypt_custom_func;/*如果指定为自定义加密方式,这个就是函数指针*/
}CulLogST;

extern S32 cul_log_init(CulLogST* IN p_log_st);
extern S32 cul_log_exit(void);
extern S32 cul_log_string(U32 log_mod,S8* IN file, S32 line,const S8* IN x_format,...);
extern S32 cul_log_dump_out(U32 log_mod,U8* IN data,S32 len);


extern S32 cul_log_debug_string(const S8* IN x_format,...);


#endif
