#include <stdio.h>
#include <windows.h>
#if (defined UNICODE)||(defined _UNICODE)
#define DebugMsg DebugMsgW
#else
#define DebugMsgA DebugMsgW
#endif
void DebugMsgA(char* str,...){
	char szBuffer[500];
	va_list Argv;
	va_start(Argv,str);
	_vsnprintf_s(szBuffer, 500, str, Argv); 
  va_end(Argv);
	OutputDebugString(szBuffer);
}
void DebugMsgW(wchar_t* str,...){
	wchar_t szBuffer[500];
	va_list Argv;
	va_start(Argv,str);
	_vsnwprintf_s(szBuffer, 500, str, Argv); 
  va_end(Argv);
	OutputDebugStringW(szBuffer);
}
