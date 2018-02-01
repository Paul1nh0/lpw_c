#include "cul_macro.h"
#include "cul_log.h"
#include "cul_lua.h"
#include "cul_config.h"
#include "cul_std_string.h"

S32 cul_config_log_get(CulLogST* p_log_st)
{
    cul_memset(p_log_st,0x00,sizeof(CulLogST));
    if(cul_lua_read_table_integer("DEBUG_CONFIG","MaxMem",&(p_log_st->str_len)))
    {
        return -1;
    }
    cul_log_debug_string("MaxMem is %d",p_log_st->str_len);
    
    if(cul_lua_read_table_integer("DEBUG_CONFIG","MaxSize",&(p_log_st->max_file_size)))
    {
        return -1;
    }
    cul_log_debug_string("MaxFileSize is %d",p_log_st->max_file_size);
    
    if(cul_lua_read_table_integer("DEBUG_CONFIG","MaxFiles",&(p_log_st->max_file_number)))
    {
        return -1;
    }
    cul_log_debug_string("MaxFiles is %d",p_log_st->max_file_number);
    
    if(cul_lua_read_table_integer("DEBUG_CONFIG","Filter",&(p_log_st->filter)))
    {
        return -1;
    }
    cul_log_debug_string("filter is %d",p_log_st->filter);

    if(cul_lua_read_table_integer("DEBUG_CONFIG","OutputMethod",&(p_log_st->output_method)))
    {
        return -1;
    }
    cul_log_debug_string("OutputMethod is %d",p_log_st->output_method); 

    if(cul_lua_read_table_integer("DEBUG_CONFIG","EncryptMethod",&(p_log_st->encrypt_method)))
    {
        return -1;
    }
    cul_log_debug_string("EncryptMethod is %d",p_log_st->encrypt_method);    
    return 0;
}

S32 cul_config_8583_len(void)
{
    int len = 0;
    if(cul_lua_get_integer("ISO_8583_LEN",&len))
    {
        return 0;
    }
    return len;
}
