#include "windows.h"
#include "windowsx.h"
#include "main.h"
#include "dialogs.h"
#include "resource.h"
#include "opc/opc.h"
#include "stdio.h"

#include "encoder.h"

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        /* BEGIN MESSAGE CRACK */
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
        HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
        /* END MESSAGE CRACK */
    }

    return FALSE;
}

/*******************************************************************************
*  Main_OnInitDialog
*/
BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    /* Set app icons */
    HICON hIcon = LoadIcon((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE) ,MAKEINTRESOURCE(IDI_ICONAPP));
    SendMessage(hwnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)hIcon);
    
    /*
    * Add initializing code here
    */
    
    return TRUE;
}

/*******************************************************************************
*  Main_OnCommand
*/
void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
#if 1
    opcContainer *c = NULL;
    FILE *dump = NULL;
    unsigned char uft8_name[15]={0xE8,0xBE,0x93,0xE5,0x85,0xA5,0xE8,0xA1,0xA8,0x2E,0x78,0x6C,0x73,0x78,0x00};
    switch(id)
    {

        case IDC_BUTTON1:
             c =opcContainerOpen("输入表.xlsx", 
                                    OPC_OPEN_READ_ONLY, 
                                    NULL, NULL);
             dump = fopen("dump.log","a+");
             opcContainerDump(c, dump);
             fclose(dump);
             opcContainerClose(c, OPC_CLOSE_NOW);
        break;
        
        default:break;
    }
#endif
}

/*******************************************************************************
*  Main_OnClose
*/
void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}
