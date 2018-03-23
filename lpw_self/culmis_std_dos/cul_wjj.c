#include "windows.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "cul_macro.h"
#include "cul_error.h"
#include "cul_lua.h"
#include "cul_std_string.h"
#include "cul_log.h"
#include "cul_iso8583.h"
#include "cul_socket.h"
#include "cul_pinpad.h"

extern char g_file_path[260];
extern IsoData cul_8583_data;

static lua_State* L = PNULL;
char* p_iso_stream = NULL;

/*
in:mk_index
in:pin_key
in:card_no
in:pwd
out:pinblock
*/
static S32 cul_lua_soft_pin(lua_State *L)
{
    const char* mk_index = NULL;
    const char* pin_key = NULL;
    const char* card_no = NULL;
    const char* pass_word = NULL;
    S32 len = 0;
    S8 master_key[8]={0x00};
    S8 pin_block[8]={0x00};
    S32 n = lua_gettop(L);
    if(n!=4)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_check_value with %d params",n);
        /*lua_pushstring(L,"call function with error params");*/
        lua_error(L);
        return 1;
    }
    mk_index = lua_tostring(L,1);
    pin_key = lua_tolstring(L,2,&len);
    card_no = lua_tostring(L,3);
    pass_word = lua_tostring(L,4);
    
    cul_get_masterkey(master_key,(S8*)mk_index);
    soft_get_pin(master_key,(S8*)pin_key,(S8*)card_no,(S8*)pass_word,pin_block);
    lua_pushlstring(L,pin_block,8);
    return 1;
}


static S32 cul_lua_soft_mac(lua_State *L)
{
    const char* mk_index = NULL;
    const char* mac_key = NULL;
    const char* stream = NULL;
    S32 len = 0;
    S8 master_key[8]={0x00};
    S8 out_mac[8]={0x00};
    S32 n = lua_gettop(L);
    if(n!=4)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_check_value with %d params",n);
        /*lua_pushstring(L,"call function with error params");*/
        lua_error(L);
        return 1;
    }
    mk_index = lua_tostring(L,1);
    mac_key = lua_tolstring(L,2,&len);
    stream = lua_tostring(L,3);
    len = (S32)lua_tointeger(L,4);
    
    cul_get_masterkey(master_key,(S8*)mk_index);
    soft_calc_mac((S8*)master_key,(S8*)mac_key,(S8*)stream,len,out_mac);
    lua_pushlstring(L,out_mac,8);
    return 1;   
}

/*lua function
in:mk_index,密钥索引
in:field62 62域
out:返回码
out:错误信息*/
static S32 cul_lua_check_value(lua_State *L)
{
    const char* mk_index = NULL;
    const char* field62 = NULL;
    S8 master_key[8]={0x00};
    S32 len = 0;
    S32 n = lua_gettop(L);
    if(n!=2)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_check_value with %d params",n);
        lua_pushstring(L,"EP");
        lua_pushstring(L,"参数个数错误");
        return 2;
    }
    mk_index = lua_tostring(L,1);
    cul_log_string(LOG_LUA,"mk_index %s",mk_index);
    field62 = lua_tolstring(L,2,&len);
    cul_get_masterkey(master_key,(S8*)mk_index);
    if(soft_check_key(master_key,(S8*)field62))
    {
        lua_pushstring(L,"ZA");
        lua_pushstring(L,"密钥校验错");
        return 2;
    }
    lua_pushstring(L,"00");
    lua_pushstring(L,"成功");
    return 2;
}

static S32 cul_debug(lua_State *L)  
{
    S32 n = lua_gettop(L);
    if(n!=3)
    {
        cul_log_string(LOG_LUA,"call function cul_debug with %d params",n);
        return 0;
    }
    cul_log_string(MOD_LUA_LUA,(S8*)lua_tostring(L,1),(S32)lua_tointeger(L,2),lua_tostring(L,3));
    return 0;  
}

static S32 cul_lua_iso8583_pack(lua_State *L)
{    
    int i = 0;
    int buf_len = 0;
    int len = 0;
    S8 field[1024]={0x00};
    S8 field_name[10]={0x00};
    S32 n = lua_gettop(L);
    if(n!=1)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_iso8583_pack with %d params",n);
        return 1;
    }
    buf_len = (S32)lua_tointeger(L,1);
    cul_log_string(LOG_LUA,"buf len is %d",buf_len);
    if(buf_len<=3072)
    {
        return 1;
    }
    cul_lua_read_table_string("req_fields","tpdu",cul_8583_data.pos_tpdu);
    cul_lua_read_table_string("req_fields","package_head",cul_8583_data.package_head);
    cul_lua_read_table_string("req_fields","message_type",cul_8583_data.msg_type);
    for(i=2;i<64;i++)
    {
        cul_sprintf(field_name,"field%d",i);
        if(len = cul_lua_read_table_lstring("req_fields",field_name,field,0))
        {
            cul_iso8583_set_field(&cul_8583_data,i,field,len);
            memset(field,0x00,1024);
        }
    }
    p_iso_stream = (char*)malloc(buf_len);
    if(p_iso_stream == PNULL)
    {
        return 1;
    }
    /*预留两个字节长度*/
    cul_iso8583_pack(&cul_8583_data,p_iso_stream,&n);
//    p_iso_stream[0]=n>>8;
//    p_iso_stream[1]=n;
    lua_pushlstring(L,p_iso_stream,n);
    DELETE_POINTER(p_iso_stream);
    /*单独处理密码相关*/
    return 1;
}

static S32 cul_lua_iso8583_unpack(lua_State *L)
{
    int buf_len = 0;
    int i = 0;
    int field_len = 0;
    const char* cp_iso_stream =NULL;
    S8 field[1024]={0x00};
    S8 field_name[10]={0x00};
    S32 n = lua_gettop(L);
    if(n!=1)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_iso8583_unpack with %d params",n);
        return 1;
    }
    cp_iso_stream = lua_tolstring(L,1,&buf_len);
    memset(cul_8583_data.iso_field,0x00,sizeof(IsoData)-sizeof(char*));
    cul_iso8583_unpack(&cul_8583_data,cp_iso_stream);
    cul_lua_write_table_string("rsp_fields","tpdu",cul_8583_data.pos_tpdu);
    cul_lua_write_table_string("rsp_fields","package_head",cul_8583_data.package_head);
    cul_lua_write_table_string("rsp_fields","message_type",cul_8583_data.msg_type);
    for(i=2;i<64;i++)
    {
        field_len = cul_iso8583_get_field(&cul_8583_data,i,field);
        if(field_len != 0)
        {
            cul_sprintf(field_name,"field%d",i);
            cul_lua_write_table_lstring("rsp_fields",field_name,field,field_len);
            memset(field,0x00,1024);
        }
    }   
    lua_pushstring(L,"00");
    return 1;
}

static S32 cul_get_path(lua_State *L)
{
    S32 n = lua_gettop(L);
    if(n!=0)
    {
        cul_log_string(LOG_LUA,"call function cul_get_path with %d params",n);
        return 1;
    }
    lua_pushstring(L,g_file_path);
    return 1;
}

static S32 socket_id;
static S32 cul_lua_socket_send(lua_State *L)
{
    S32 n = lua_gettop(L);
    if(n!=4)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_socket_send with %d params",n);
        return 1;
    }
    socket_id = 0;
    socket_id = cul_socket_init((S8*)lua_tostring(L,1),(S32)lua_tointeger(L,2));
    	if(socket_id==0)
	{
         lua_pushinteger(L,-1);
		cul_socket_close(socket_id);
		return 1;
	}
    if(cul_socket_send(socket_id,(S8*)lua_tostring(L,3),(S32)lua_tointeger(L,4)))
    {
        lua_pushinteger(L,-1);
        cul_socket_close(socket_id);
        return 1;
    }
    lua_pushinteger(L,0);
    return 1;
}

static S32 cul_lua_socket_recv(lua_State *L)
{
    U8* buf = PNULL;
    U32 len = 0;
    S32 n = lua_gettop(L);
    if(n!=2)
    {
        cul_log_string(LOG_LUA,"call function cul_lua_socket_send with %d params",n);
        cul_socket_close(socket_id);
        return 1;
    }
    if(socket_id == 0)
    {
        lua_pushnil(L);
        return 1;
    }
    len = (S32)lua_tointeger(L,1);
    buf = (S8*)malloc(len);
    if(buf==PNULL)
    {
        lua_pushnil(L);
        return 1;
    }
    if(cul_socket_recv(socket_id,buf,len,(S32)lua_tointeger(L,2)))
    {
        cul_socket_close(socket_id);
        lua_pushnil(L);
        return 1;
    }
    len = buf[0] * 256 + buf[1];
    cul_log_string(LOG_LUA,"socket recv len %d",len);
    lua_pushlstring(L,buf+2,len);
    DELETE_POINTER(buf);
    cul_socket_close(socket_id);
    return 1;
}

S32 cul_lua_init(S8* file_name)
{
    L = luaL_newstate();
    if(L == PNULL)
    {
        return ERROR_LUA_CREATE;
    }
    luaL_openlibs(L);
    /*扩大lua堆栈*/
    lua_checkstack(L, 1024);
    /*注册lua函数*/
    lua_register(L, "cul_debug", cul_debug);
    lua_register(L, "cul_iso8583_pack", cul_lua_iso8583_pack);
    lua_register(L, "cul_iso8583_unpack", cul_lua_iso8583_unpack);
    lua_register(L, "cul_get_path", cul_get_path);
    lua_register(L, "cul_socket_send", cul_lua_socket_send);
    lua_register(L, "cul_socket_recv", cul_lua_socket_recv);
    lua_register(L, "cul_check_value", cul_lua_check_value);
     lua_register(L, "cul_soft_pin", cul_lua_soft_pin);
    lua_register(L, "cul_soft_mac", cul_lua_soft_mac);
    
    if(luaL_loadfile(L,file_name)||lua_pcall(L,0,0,0))
    {
        cul_log_debug_string(lua_tostring(L,-1));
        return ERROR_LUA_LOAD;
    }
    return 0;
}

S32 cul_lua_exit(void)
{
    lua_close(L);
    L=PNULL;
    return 0;
}

S32 cul_lua_get_integer(const S8* IN var,S32* OUT integer)
{
    lua_getglobal(L,var);
    *integer = (S32)lua_tointeger(L,-1);
    return 0;
}

S32 cul_lua_get_string(const S8* IN var,S8* OUT string)
{
    lua_getglobal(L,var);
    cul_strcpy((U8*)string,(U8*)lua_tostring(L,-1));
    return 0;
}

S32 cul_lua_write_table_integer(const S8* strTableName, 
                                const S8* strTableItem, 
                                S32 nValue)
{
    lua_getglobal(L, strTableName);
    lua_pushinteger(L, nValue);
    lua_setfield(L, -2, strTableItem);
    lua_pop(L, 1);
    return 0;
}

S32 cul_lua_write_table_string(const S8* strTableName, 
                               const S8* strTableItem, 
                               const S8* strValue)

{
    lua_getglobal(L, strTableName);
    lua_pushstring(L, strValue);
    lua_setfield(L, -2, strTableItem);
    lua_pop(L, 1);
    return 0;
}
 
S32 cul_lua_write_table_lstring(const S8* strTableName, 
                                const S8* strTableItem, 
                                const S8* arrValue,
                                S32 nLen)
{
    lua_getglobal(L, strTableName);
    lua_pushlstring(L, arrValue,nLen);
    lua_setfield(L, -2, strTableItem);
    lua_pop(L, 1);
    return 0;

}

S32 cul_lua_read_table_string(const S8* strTableName, 
                              const S8* strTableItem,
                              S8* strValue)
{
    lua_getglobal(L, strTableName);
    if(!lua_istable(L,-1))
    {
        return -1;
    }
    lua_pushstring(L, strTableItem);
    if(!lua_gettable(L, -2))
    {
        cul_log_debug_string("%s is not a table member",strTableItem);
        return -1;
    }
    cul_strcpy((U8*)strValue,(U8*)lua_tostring(L,-1));
    lua_pop(L, 2);
    return 0;
}


S32 cul_lua_read_table_lstring(const S8* strTableName, 
                               const S8* strTableItem,
                               S8* arrValue,
                               S32 nLen)

{
    int len = 0;
    const char* tmp = PNULL;
    lua_getglobal(L, strTableName);
    if(!lua_istable(L,-1))
    {
        return 0;
    }
    lua_pushstring(L, strTableItem);
    if(!lua_gettable(L, -2))
    {
        cul_log_debug_string("%s is not a table member",strTableItem);
        return 0;
    }
    tmp = lua_tolstring(L,-1,&len);
    cul_memcpy(arrValue,(S8*)tmp,(U32)len);
    lua_pop(L, 2);
    return len;

}

S32 cul_lua_read_table_integer(const S8* strTableName, 
                               const S8* strTableItem,
                               S32* nValue)
{
    lua_getglobal(L, strTableName);
    if(!lua_istable(L,-1))
    {
        cul_log_debug_string("%s is not a table",strTableName);
        return -1;
    }
    lua_pushstring(L, strTableItem);
    if(!lua_gettable(L, -2))
    {
        cul_log_debug_string("%s is not a table member",strTableItem);
        return -1;
    }
    *nValue = (S32)lua_tointeger(L,-1);
    lua_pop(L, 2);
    return 0;
}
    
S32 cul_lua_do_func(S8* IN func_name,S8* IN str,S32 mode,S8* OUT dst_str)
{
    const S8* tmp = PNULL;
    int result = 0;
    lua_getglobal(L,func_name);
    if(!lua_isfunction(L,-1))
    {
        cul_log_string(LOG_LUA,"call func %s failed",func_name);
        return -1;
    }
    lua_pushstring(L,str);
    lua_pushinteger(L,mode);
    /*需要检查堆栈,确保lua执行代码中的代码不会栈溢出*/
    /*lua状态机,参数个数,返回值个数,错误处理函数,0表示无(表示错误处理函数在栈中的索引)*/
    if(lua_pcall(L,2,1,0)!=0)
    {
        cul_log_string(LOG_LUA,"error running function %s",lua_tostring(L,-1));
        return -1;
    }
    tmp = lua_tostring(L,-1);
    strcpy(dst_str,tmp);
    cul_log_string(LOG_LUA,"result is %s",dst_str);
    return result;
}


