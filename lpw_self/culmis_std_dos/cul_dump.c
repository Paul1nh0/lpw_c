#include "windows.h"
#include "dbghelp.h"
#include "tchar.h"
#include "cul_std_string.h"
#include "cul_dump.h"

#define USER_DATA_BUFFER_SIZE 4096

extern char g_file_path[260];

typedef BOOL (WINAPI *MINIDUMPWRITEDUMP)(HANDLE hProcess,  
                                         DWORD dwPid,  
                                         HANDLE hFile,  
                                         MINIDUMP_TYPE DumpType,  
                                         CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,  
                                         CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,  
                                         CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam);



LONG WINAPI cul_unhandled_exception_handler(PEXCEPTION_POINTERS p_exception_info); 
void disable_set_unception_handle();
void cul_invalid_handler(const wchar_t* expression,  
                                            const wchar_t* function,   
                                            const wchar_t* file,   
                                            unsigned int line,   
                                            uintptr_t pReserved);
void cul_purecall_handler(void);


unsigned char old_code[16];

CRITICAL_SECTION section;

int cul_dump_start()
{
    
    InitializeCriticalSection( &section ); 
    SetUnhandledExceptionFilter(cul_unhandled_exception_handler);

    _set_abort_behavior(0, _CALL_REPORTFAULT);  
    _set_invalid_parameter_handler(cul_invalid_handler);  
    _set_purecall_handler(cul_purecall_handler); 

    disable_set_unception_handle();
    return 0;
}

int cul_dump_exit()
{
    return 0;
}

void cul_invalid_handler(const wchar_t* expression,  
                                            const wchar_t* function,   
                                            const wchar_t* file,   
                                            unsigned int line,   
                                            uintptr_t pReserved)
{
    RaiseException(1, 0, 0, NULL);
}

void cul_purecall_handler(void)
{
    RaiseException(1, 0, 0, NULL);
}


int cul_enable_privilege(LPCTSTR pszPriv, HANDLE hToken, TOKEN_PRIVILEGES* ptpOld)
{
    TOKEN_PRIVILEGES tp;  
    BOOL bOk = FALSE; 
    tp.PrivilegeCount = 1;  
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
    bOk = LookupPrivilegeValue( 0, pszPriv, &tp.Privileges[0].Luid );  
  
    if( bOk )  
    {  
        DWORD cbOld = sizeof(*ptpOld);  
        bOk = AdjustTokenPrivileges( hToken, FALSE, &tp, cbOld, ptpOld, &cbOld );  
    }  
  
    return (bOk && (ERROR_NOT_ALL_ASSIGNED != GetLastError()));  

}

int cul_get_impersonation_token(HANDLE* phToken)
{
    *phToken = NULL;  
  
    if( !OpenThreadToken( GetCurrentThread(),  
                          TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,  
                          TRUE,  
                          phToken) )  
    {  
        if( GetLastError() == ERROR_NO_TOKEN )  
        {  
            // No impersonation token for the current thread is available.   
            // Let's go for the process token instead.  
            if( !OpenProcessToken( GetCurrentProcess(),  
                                   TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES,  
                                   phToken) )  
                return 0;  
        }  
        else  
            return 0;  
    }  
  
    return 1;  
}

//让SetUnhandledExceptionFilter直接返回,因为在你程序运行过程中,
//系统可能会执行SetUnhandledExceptionFilter,让你的set无效,因此在调用之后我们让这个函数直接返回
void disable_set_unception_handle()
{
    void *addr = (void*)GetProcAddress(LoadLibrary(TEXT("kernel32.dll")),  
                "SetUnhandledExceptionFilter");  
    if (addr)   
    {  
        unsigned char code[16];  
        int size = 0; 
        DWORD dwOldFlag, dwTempFlag;  
        
        code[size++] = 0x33;  
        code[size++] = 0xC0;  
        code[size++] = 0xC2;  
        code[size++] = 0x04;  
        code[size++] = 0x00;  
          
        VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);  
        WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);  
        VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);  
    }  
}

int cul_restore_privilege( HANDLE hToken, TOKEN_PRIVILEGES* ptpOld )
{
    BOOL bOk = AdjustTokenPrivileges(hToken, FALSE, ptpOld, 0, NULL, NULL);  
    return ( bOk && (ERROR_NOT_ALL_ASSIGNED != GetLastError()) );  
}

LONG WINAPI cul_unhandled_exception_handler(PEXCEPTION_POINTERS  p_exception_info) 
{
    HMODULE hDll = NULL;  
    LPCTSTR szResult = NULL; 
    LONG retval = EXCEPTION_CONTINUE_SEARCH;
    HANDLE hImpersonationToken = NULL;  
    if( !cul_get_impersonation_token( &hImpersonationToken ) )  
        return FALSE;  
    
        // If we haven't found it yet - try one more time.  
    hDll = LoadLibrary(TEXT("DBGHELP.DLL"));  
    if( hDll )  
    {  
        // Get the address of the MiniDumpWriteDump function, which writes   
        // user-mode mini-dump information to a specified file.  
        MINIDUMPWRITEDUMP MiniDumpWriteDump =   
            (MINIDUMPWRITEDUMP)GetProcAddress( hDll, "MiniDumpWriteDump" );  
  
        if( MiniDumpWriteDump != NULL )  
        {  
            HANDLE hFile;
            char dump_file[260]={0x00};
            cul_sprintf(dump_file,"%sculdump.dmp",g_file_path);
            // Create the mini-dump file...  
            hFile = CreateFile( TEXT(dump_file),   
                                            GENERIC_WRITE,   
                                            FILE_SHARE_WRITE,   
                                            NULL,   
                                            CREATE_ALWAYS,   
                                            FILE_ATTRIBUTE_NORMAL,   
                                            NULL );  
  
            if( hFile != INVALID_HANDLE_VALUE )  
            {  
                MINIDUMP_EXCEPTION_INFORMATION ExInfo; 
                TOKEN_PRIVILEGES tp;  
                BOOL bPrivilegeEnabled; 
                BOOL bOk;
                ExInfo.ThreadId          = GetCurrentThreadId();  
                ExInfo.ExceptionPointers = p_exception_info;  
                ExInfo.ClientPointers    = 0;  
  
                // We need the SeDebugPrivilege to be able to run MiniDumpWriteDump  
                
                bPrivilegeEnabled = cul_enable_privilege( SE_DEBUG_NAME, hImpersonationToken, &tp );  
  
                  
  
                // DBGHELP.dll is not thread-safe, so we need to restrict access...  
                EnterCriticalSection( &section );  
                {  
                    // Write out the mini-dump data to the file...  
                    bOk = MiniDumpWriteDump( GetCurrentProcess(),  
                                                GetCurrentProcessId(),  
                                                hFile,  
                                                MiniDumpNormal,  
                                                &ExInfo,  
                                                NULL,  
                                                NULL );  
                }  
                LeaveCriticalSection( &section );  
  
                // Restore the privileges when done  
                if( bPrivilegeEnabled )  
                    cul_restore_privilege( hImpersonationToken, &tp );  
  
                if( bOk )  
                {  
                 
                    retval = EXCEPTION_EXECUTE_HANDLER;           
                }  
                else  
                { 
  
                   
                }  
  
                CloseHandle( hFile );  
            }  
            else  
            {  

            }  
        }  
        else  
        {  

        }  
    }  
    else  
    {  

    }  
  
    TerminateProcess( GetCurrentProcess(), 0 );  
  
    return retval;  
}


