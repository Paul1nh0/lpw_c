#ifndef _MAIN_H
#define _MAIN_H

#include "windows.h"

/*采用什么接口模式*/
#define JSON_MODE 0
#define XML_MODE 1
#define CSTRUCT_MODE 2



BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Main_OnDropFiles(HWND hwnd, HDROP wParam);
void Main_OnClose(HWND hwnd);


#endif
