#include "cul_macro.h"
#include "cul_error.h"
#include "cul_lua.h"
#include "cul_log.h"
#include "cul_config.h"
#include "cul_iso8583.h"
#include "cul_std_string.h"
#include "cul_pinpad.h"
#include "cul_dump.h"
#include "windows.h"



#define INTERFACE_MODE_JSON 0
#define INTERFACE_MODE_XML 1
#define INTERFACE_MODE_STRUCT 2

char g_file_path[260]={0x00};
char g_log_file_path[260]={0x00};
static CulLogST cul_log_st;
IsoData cul_8583_data;


#ifdef CUL_WINDOWS
int STDCALL DllMain (HINSTANCE hInst     /* Library instance handle. */ ,
                       DWORD reason        /* Reason this function is being called. */ ,
                       LPVOID reserved     /* Not used. */ )
{	
    switch (reason)
    {
    	/*进程调用DLL*/
    	case DLL_PROCESS_ATTACH:
        GetModuleFileName(hInst, g_file_path, MAX_PATH);
        *(strrchr(g_file_path,'\\')+1)=0;
        cul_dump_start();
        break;
    	
    	/*进程卸载DLL*/
    	case DLL_PROCESS_DETACH:
        break;

    	/*线程调用DLL*/
    	case DLL_THREAD_ATTACH:
        GetModuleFileName(hInst, g_file_path, MAX_PATH);
        *(strrchr(g_file_path,'\\')+1)=0;
        break;

    	/*线程卸载DLL*/
    	case DLL_THREAD_DETACH:
        break;
    }

    /* Returns TRUE on success, FALSE on failure */
    return TRUE;
}
#endif


#ifdef JNI_SUPPORT
#include "jni.h"
jstring JNICALL Java_com_culmis_zero_culmis_JniInterface_CulInterface(JNIEnv *env, jobject obj, jstring in_str,jint mode)
{
    return PNULL;
}
#endif


static S32 cul_init(void)
{
    S32 result;
    S32 iso8583_len = 0;
    S8 file_name[MAX_PATH]={0x00};
    
    cul_sprintf(file_name,"%scul_mis.wjj",g_file_path);
    cul_log_debug_string("culmis.wjj:%s",file_name);
    result = cul_lua_init(file_name);
    cul_log_debug_string("cul_lua_init:%d",result);
    if(result)
    {
        return result;
    }
    result = cul_config_log_get(&cul_log_st);
    cul_log_debug_string("cul_config_log_get:%d",result);
    if(result)
    {
        return result;
    }

    /*log模块初始化*/
    cul_sprintf(g_log_file_path,"%scul_log\\",g_file_path);
    cul_log_debug_string("g_log_file_path:%s",g_log_file_path);
    cul_log_st.path = g_log_file_path;
    result = cul_log_init(&cul_log_st);
    if(result)
    {
        return result;
    }
    iso8583_len = cul_config_8583_len();
    cul_log_string(LOG_INTERFACE,"iso8583 buf is %d",iso8583_len);
    if(iso8583_len == 0)
    {
        return ERROR_LUA_CONFIG;
    }
    result =cul_iso8583_init(&cul_8583_data,iso8583_len);
    if(result)
    {
        return result;
    }
    
    cul_log_string(LOG_INTERFACE,"cul_init success");
    return SUCCESS;
}

S32 cul_exit()
{
    cul_log_exit();
    cul_iso8583_exit(&cul_8583_data);
    return 0;
}

S32 STDCALL cul_interface(S8* in_str,S8* out_str,S32 mode)
{   

    S32 result;
#if 0
    HANDLE hMutex = CreateMutex(PNULL, FALSE, TEXT("culmisdll"));
    if (hMutex != PNULL && GetLastError() == ERROR_ALREADY_EXISTS) 
    {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return ERROR_MULTITHREAD;
    }
#endif
    #if 0//def _DEBUG
    __asm
    {
        int 3
    }
    #endif
    cul_log_debug_string("interface begin");
    result = cul_init();
    if(result)
    {
        cul_exit();
        return result;
    }
    if(cul_lua_do_func("lua_do_fields",in_str,mode,out_str))
    {
        return ERROR_LUA_FUNC;
    }
#if 0    
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
#endif
    cul_exit();
    cul_log_debug_string("interface end3");
    return SUCCESS;
}
