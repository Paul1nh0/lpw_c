/******************************************************************************

                  版权所有 (C), 上海银商资讯有限公司

 ******************************************************************************
  @file    cul_lua.h
  @version 初稿
  @author  绿皮蛙
  @date    2016年11月4日
  @email   wangly@upcard.com.cn
  @brief  cul_lua.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2016年11月4日
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
