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
    S8* path; /*log�����Ҫ������ļ�,�����ʾ�ļ���·��*/
    S8* str; /*log���ʱ���ַ��ڴ�*/
    S8* encrypt_str;
    U32 str_len; /*�ַ��ڴ���󳤶�*/
    U32 max_file_size;/*������ļ�ʱÿ���ļ���󳤶�*/
    U32 max_file_number;/*������ļ�ʱ�ļ�������*/
    U32 filter; /*log����,���ݲ�ͬģ�����log*/
    U32 output_method; /*log�����ʽ ���ļ���ʽ,OutputDebugString,printf��*/
    U32 encrypt_method; /*log���ܷ�ʽ*/
    S8* output_custom_func; /*output_method��ָʾ��Ҫ�Զ���log�����ʽ,������Ǻ���ָ��*/
    S8* encrypt_custom_func;/*���ָ��Ϊ�Զ�����ܷ�ʽ,������Ǻ���ָ��*/
}CulLogST;

extern S32 cul_log_init(CulLogST* IN p_log_st);
extern S32 cul_log_exit(void);
extern S32 cul_log_string(U32 log_mod,S8* IN file, S32 line,const S8* IN x_format,...);
extern S32 cul_log_dump_out(U32 log_mod,U8* IN data,S32 len);


extern S32 cul_log_debug_string(const S8* IN x_format,...);


#endif
