/******************************************************************************

                  ��Ȩ���� (C), �Ϻ�������Ѷ���޹�˾

 ******************************************************************************
  @file    cul_lua.h
  @version ����
  @author  ��Ƥ��
  @date    2016��11��4��
  @email   wangly@upcard.com.cn
  @brief  cul_lua.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��11��4��
    ��    ��   : ��Ƥ��
    �޸�����   : �����ļ�

******************************************************************************/

/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

#ifndef __CUL_LUA_H__
#define __CUL_LUA_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern S32 cul_lua_exit(void);
extern S32 cul_lua_get_integer(const S8* IN var,S32* OUT integer);
extern S32 cul_lua_get_string(const S8* IN var,S8* OUT string);
extern S32 cul_lua_init(S8* IN file_name);
extern S32 cul_lua_read_table_integer(const S8* strTableName, 
                                        const S8* strTableItem,
                                        S32* nValue);
extern S32 cul_lua_read_table_lstring(const S8* strTableName, 
                                        const S8* strTableItem,
                                        S8* arrValue,
                                        S32 nLen);
extern S32 cul_lua_read_table_string(const S8* strTableName, 
                                       const S8* strTableItem,
                                       S8* strValue);
extern S32 cul_lua_write_table_integer(const S8* strTableName, 
                                         const S8* strTableItem, 
                                         S32 nValue);
extern S32 cul_lua_write_table_lstring(const S8* strTableName, 
                                         const S8* strTableItem, 
                                         const S8* arrValue,
                                         S32 nLen);
extern S32 cul_lua_write_table_string(const S8* strTableName, 
                                        const S8* strTableItem, 
                                        const S8* strValue);
extern S32 cul_lua_do_func(S8* IN func_name,S8* IN str,S32 mode,S8* OUT dst_str);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CUL_LUA_H__ */
