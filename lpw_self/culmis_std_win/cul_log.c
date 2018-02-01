#include "cul_macro.h"
#include "cul_std_string.h"
#include "cul_log.h"
#include "time.h"
#include "stdio.h"
#include "direct.h"
#include "cul_common.h"
#include "windows.h"

static CulLogST* sp_log_st = PNULL;

const S8* mod_string[]=
{
    "mod_interface",
    "mod_config",
    "mod_pinpad",
    "mod_socket",
    "mod_lua_c",
    "mod_lua_lua",
    "mod_8583"
};

#define LOG_RECORD_FILE "log_record"
/*----------------------------------------------*
 * 文件读写相关函数                                  *
 *----------------------------------------------*/
static S32 cul_file_is_exist(S8* file_name)
{
    FILE *file_handle = 0;
    S8 file_path_name[260];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    file_handle = fopen(file_path_name, "rb");
    if(file_handle != 0)
    {
        fclose(file_handle);
        return 0;
    }
    return -1;
    
}

static S32 cul_file_delete(S8* file_name)
{
    S8 file_path_name[260];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    return remove(file_path_name);
}

static U32 cul_file_get_length(S8* file_name)
{
    U32 len = 0;
    FILE *file_handle = 0;
    S8 file_path_name[260];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    file_handle = fopen(file_path_name, "rb");
    if(file_handle == 0)
    {
        return 0;
    }
    fseek(file_handle,0,SEEK_END);
    len = ftell(file_handle);
    fclose(file_handle);
    return len;
}

static S32 cul_file_read_data(S8* file_name, S8* str, S32 offset,S32 len)
{
    S32 result = 0;
    FILE *file_handle = 0;
    S8 file_path_name[260];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    file_handle = fopen(file_path_name, "rb");
    if (file_handle != 0)
    {
        fseek(file_handle, offset, SEEK_SET);
        if(fread(str, len, 1, file_handle)==0)
        {
            fclose(file_handle);
            return -2;
        }
        fclose(file_handle);
        return 0;
    }
    return -1;
    
}

static S32 cul_file_write_data(S8* file_name, S8* str, S32 offset, S32 len)
{
    S32 result = 0;
    FILE *file_handle = 0;
    S8 file_path_name[260];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    file_handle = fopen(file_path_name, "wb");
    if (file_handle != 0)
    {
        fseek(file_handle, offset, SEEK_SET);
        fwrite(str, len, 1, file_handle);
        fclose(file_handle);
        return 0;
    }
    return -1;
}

static S32 cul_file_write_data_append(S8* file_name, S8* str, S32 len)
{
    S32 result = 0;
    S32 file_len = 0;
    FILE *file_handle = 0;
    S8 file_path_name[90];
    memset(file_path_name,0x00,sizeof(file_path_name));
    sprintf(file_path_name,"%s%s",sp_log_st->path,file_name);
    cul_log_debug_string("cul write data append is %s",file_path_name);
    file_handle = fopen(file_path_name, "ab+");
    if (file_handle != 0)
    {
        fwrite(str, len, 1, file_handle);
        fclose(file_handle);
    }
    return 0;
}

/*----------------------------------------------*
 * 系统辅助函数                              *
 *----------------------------------------------*/
S32 get_current_yyyymmdd(S8 *strTime )
{
    time_t cur_time = time(NULL);

    struct tm* t = localtime(&cur_time);

    if (t == NULL)
    {
        return -1;
    }

    if (strftime(strTime, 9, "%Y%m%d", t) == 0)
    {
        return -2;
    }

    return 0;
}

S32 get_current_time(S8 *strTime )
{
    time_t cur_time = time(NULL);

    struct tm* t = localtime(&cur_time);

    if (t == NULL)
    {
        return -1;
    }

    if (strftime(strTime, 9, "%H:%M:%S", t) == 0)
    {
        return -2;
    }

    return 0;
}

/*----------------------------------------------*
 * log记录文件操作                            *
 *----------------------------------------------*/

static S32 cul_log_get_cur_file(S8* IN log_record,S8* OUT file_name)
{
    S32 offset = 0;
    S8* p_cur_file = PNULL;
    offset = (S32)*log_record;
    if(offset == -1)
    {
        return -1;
    }
    p_cur_file = log_record + 4 + offset*16;
    memcpy(file_name,p_cur_file,16);
    return 0;    
}

static S32 cul_log_offset_ins(S8* IN log_record,S8* IN file_name)
{
    U32 offset = 0;
    S8* p_cur_file = PNULL;
    S8 cur_file_name[17]={0x00};
    
    offset = (U32)*log_record;
    offset = offset + 1;
    if(offset >= sp_log_st->max_file_number)
    {
        offset = 0;
    }
    memcpy(log_record,(S8*)&offset,4);
    p_cur_file = log_record + 4 + offset*16;
    memcpy(cur_file_name,p_cur_file,16);
    if(cur_file_name[0]!=0x00)
    {
        cul_file_delete(cur_file_name);
    }
    p_cur_file = log_record + 4 + offset*16;
    memcpy(p_cur_file,file_name,16);
    return 0;
}

static S32 cul_log_get_record(S8* OUT log_record,U32 len)
{
    S32 file_size = 0;
    
    file_size = cul_file_get_length(LOG_RECORD_FILE);
    cul_log_debug_string("log_record file size is %d",file_size);
    if(file_size==len)
    {
        cul_file_read_data("log_record",log_record,0,len);
    }
    else
    {
        memset(log_record,0x00,len);
        memset(log_record,0xff,4);
        if(file_size != 0)
        {
            /*参数改变,删除所有log文件,遍历原先的log_record文件*/
            /*有问题,特殊情况先不考虑*/
            
        }
    }
    return 0;
}



S32 cul_log_init(CulLogST* IN p_log_st)
{
    if(p_log_st == PNULL)
    {
        return -1;
    }
    if(sp_log_st != PNULL)
    {
        return -1;
    }
    sp_log_st = p_log_st;
    sp_log_st->str = (S8*)malloc(sp_log_st->str_len);
    sp_log_st->encrypt_str = (S8*)malloc(sp_log_st->str_len);
    if(sp_log_st->str == PNULL ||sp_log_st->encrypt_str == PNULL)
    {
        return -1;
    }
#ifdef CUL_WINDOWS
    _mkdir(p_log_st->path);
#else
    mkdir(p_log_st->path,0777);
#endif
    return 0;
}

S32 cul_log_exit(void)
{
    if(sp_log_st == PNULL)
    {
        return -1;
    }
    DELETE_POINTER(sp_log_st->str);
    DELETE_POINTER(sp_log_st->encrypt_str);
    sp_log_st = PNULL;
    return 0;
}

S32 cul_log_debug_string(const S8* IN x_format,...)
{
#ifdef _DEBUG
    va_list args;
    S32 buf_len = 0;
    FILE *file_handle = 0;
    S8 log_string[8096]={0x00};
    va_start(args, x_format);
    buf_len = vsprintf(log_string, x_format, args);
    va_end(args);
    strcat(log_string,"[culmis]\n");
    OutputDebugString(log_string);
    
    file_handle = fopen("C:\\cul_only_for_debug.txt", "ab+");
    if (file_handle != 0)
    {
        fwrite(log_string, strlen(log_string), 1, file_handle);
        fclose(file_handle);
    }
#endif
    return 0;
}

S32 cul_log_string(U32 log_mod,S8* IN file,S32 line,const S8* IN x_format,...)
{
    va_list args;
    S32 buf_len = 0;
    S32 len = 0;
    S32 file_order = 0;
    S8* tmp_file_name=NULL;
    S8* log_record = PNULL;
    S8* p_cur_file = PNULL;
    U32 record_len = 0;
    S8 cur_file_name[17]={0x00};
    S8 cur_date[9]={0x00};
    S8 cur_time[9]={0x00};
    S8 str_file_order[4]={0x00};
#ifdef _DEBUG
    memset(sp_log_st->str,0x00,sp_log_st->str_len); 
    va_start(args, x_format);
    buf_len = vsprintf(sp_log_st->str, x_format, args);
    va_end(args);
    strcat(sp_log_st->str,"[culmis]\n");
    OutputDebugString(sp_log_st->str);
#endif
    
    if(!((sp_log_st->filter) & 0x01<<log_mod))
    {
        return -1;
    }
    record_len = 4+sp_log_st->max_file_number * 16;
    /*这里的申请和这个内存的释放很容易造成内存碎片和空洞问题,还好申请空间不大,暂时放着*/
    log_record = (S8*)malloc(record_len);
    if(log_record == PNULL)
    {
        return -1;
    }
    cul_log_get_record(log_record,record_len);
    cul_log_get_cur_file(log_record,cur_file_name);
    get_current_yyyymmdd(cur_date);
    /*上次写入的文件前8个字节和目前的日期做比较,相同则往下判断大小,不同则使用新建文件*/
    if(0==memcmp(cur_file_name,cur_date,8))
    {
        if(cul_file_get_length(cur_file_name)>sp_log_st->max_file_size)
        {
            memcpy(str_file_order,cur_file_name+9,3);
            file_order = atoi(str_file_order);
            file_order++;
            sprintf(str_file_order,"%03d",file_order);
            memcpy(cur_file_name+9,str_file_order,3);
            cul_log_offset_ins(log_record,cur_file_name);
        }      
    }
    else
    {
        sprintf(cur_file_name,"%s_001.log",cur_date);
        cul_log_offset_ins(log_record,cur_file_name);
    }
    cul_log_debug_string("file to write is %s",cur_file_name);
    get_current_time(cur_time);
    tmp_file_name = strrchr(file,'\\');
    if(tmp_file_name == PNULL)
    {
        tmp_file_name = file;
    }
    else
    {
        tmp_file_name += 1;
    }
    memset(sp_log_st->str,0x00,sp_log_st->str_len);
    sprintf(sp_log_st->str,"[%s][%s][L%d][%s]",cur_time,tmp_file_name,line,mod_string[log_mod]);
    len = strlen(sp_log_st->str);
    va_start(args, x_format);
    buf_len = vsprintf(sp_log_st->str+len, x_format, args);
    va_end(args);
    strcat(sp_log_st->str,"\n");    
    cul_file_write_data_append(cur_file_name,sp_log_st->str,strlen(sp_log_st->str));
    cul_file_write_data(LOG_RECORD_FILE,log_record,0,record_len);
    DELETE_POINTER(log_record);
    return 0;
}

