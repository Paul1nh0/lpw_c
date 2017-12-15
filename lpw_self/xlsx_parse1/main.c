#include "windows.h"
#include "windowsx.h"
#include "main.h"
#include "dialogs.h"
#include "resource.h"
#include "ShellApi.h"
#include "opc/opc.h"
#include "stdio.h"
#include "time.h"

#include "encoder.h"
#include "gbk_string.h"

static opcContainer *c;
static HWND s_hwnd;
void Main_OnDropFiles(HWND hwnd, HDROP wParam);
int deal_xlsx(unsigned char* input_file,unsigned char* output_file);
int xlsx_init(unsigned char* input_file);

int get_current_yyyymmdd(char *strTime )
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

int get_current_time(char *strTime )
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


int cul_log_debug_string(const char* IN x_format,...)
{
    va_list args;
    int buf_len = 0;
    FILE *file_handle = 0;
    unsigned char cur_day[9]={0x00};
    unsigned char cur_time[9]={0x00};
    char log_string[8096]={0x00};
    va_start(args, x_format);
    buf_len = vsprintf(log_string, x_format, args);
    va_end(args);
    get_current_yyyymmdd(cur_day);
    get_current_time(cur_time);
    strcat(log_string,"[");
    strcat(log_string,cur_day);
    strcat(log_string," ");
    strcat(log_string,cur_time);
    strcat(log_string,"]");
    strcat(log_string,"\n");
    file_handle = fopen("just_only_for_debug.txt", "ab+");
    if (file_handle != 0)
    {
        fwrite(log_string, strlen(log_string), 1, file_handle);
        fclose(file_handle);
    }
    return 0;
}

int cul_open_file_dlg(HWND hwnd)
{
	OPENFILENAME ofn;  
	static char szFile[256];  
	static char szFileTitle[256];  
	memset(&ofn,0,sizeof(ofn));  
	ofn.lStructSize=sizeof(ofn);  
	ofn.hwndOwner=hwnd;  
	ofn.lpstrFilter="Dll File(*.xlsx)\0*.xlsx;\0\0";  
	ofn.nFilterIndex=1;  
	ofn.lpstrFile=szFile;  
	ofn.nMaxFile=sizeof(szFile);  
	ofn.lpstrFileTitle=szFileTitle;  
	ofn.nMaxFileTitle=sizeof(szFileTitle);  
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER;
	
	if(GetOpenFileName(&ofn))  
	{
		SetWindowText(GetDlgItem(hwnd,IDC_EDIT2),szFile);
		strcat(szFile,"-output");
		SetWindowText(GetDlgItem(hwnd,IDC_EDIT3),szFile);
	}  
	else  
	{
		
	}
	return 0;
}

int cul_save_file_dlg(HWND hwnd)
{
	OPENFILENAME ofn;  
	static char szFile[256];  
	static char szFileTitle[256];  
	memset(&ofn,0,sizeof(ofn));  
	ofn.lStructSize=sizeof(ofn);  
	ofn.hwndOwner=hwnd;  
	ofn.lpstrFilter="Dll File(*.xlsx)\0*.xlsx;\0\0";  
	ofn.nFilterIndex=1;  
	ofn.lpstrFile=szFile;  
	ofn.nMaxFile=sizeof(szFile);  
	ofn.lpstrFileTitle=szFileTitle;  
	ofn.nMaxFileTitle=sizeof(szFileTitle);  
	ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER;
	
	if(GetSaveFileName(&ofn))  
	{
		SetWindowText(GetDlgItem(hwnd,IDC_EDIT3),szFile);
	}  
	else  
	{
		
	}
	return 0;
}

BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        /* BEGIN MESSAGE CRACK */
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
        HANDLE_MSG(hWnd,WM_DROPFILES,Main_OnDropFiles);
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
    DragAcceptFiles(hwnd, TRUE);
    return TRUE;
}

void Main_OnDropFiles(HWND hwnd, HDROP wParam)
{
    char strFileName[MAX_PATH];
    HDROP hDrop = (HDROP)wParam;  
    UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
    if(nFileNum!=1)
    {
        MessageBox(hwnd,gbk_dropfile_error,gbk_error,MB_OK);
    }
    DragQueryFile(hDrop, 0, strFileName, MAX_PATH);  
    SetWindowText(GetDlgItem(hwnd,IDC_EDIT2),strFileName);
    strcat(strFileName,"-output");
    SetWindowText(GetDlgItem(hwnd,IDC_EDIT3),strFileName);
    DragFinish(hDrop);
    InvalidateRect(hwnd, NULL, TRUE);
}

/*******************************************************************************
*  Main_OnCommand
*/
void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
#if 1
    char input_name[256]={0x00};
    char output_name[256]={0x00};

    switch(id)
    {

        case IDC_BUTTON1:
             GetWindowText(GetDlgItem(hwnd,IDC_EDIT2),input_name,256);
             GetWindowText(GetDlgItem(hwnd,IDC_EDIT3),output_name,256);
             deal_xlsx(input_name,output_name);
        break;

        case IDC_BUTTON2:
             cul_open_file_dlg(hwnd);
        break;

        case IDC_BUTTON3:
             cul_save_file_dlg(hwnd);
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

static void dumpElement(mceTextReader_t *reader) {
    xmlChar *ln=xmlStrdup(xmlTextReaderLocalName(reader->reader));
    cul_log_debug_string("<%s>", ln);
    mce_skip_attributes(reader);

    mce_start_children(reader) 
    {
        mce_start_element(reader, NULL, NULL) 
        {
            dumpElement(reader);
        } 
        mce_end_element(reader);
        mce_start_text(reader) 
        {
            cul_log_debug_string("%s", xmlTextReaderConstValue(reader->reader,NULL));
        } mce_end_text(reader);
    } 
    mce_end_children(reader);
    cul_log_debug_string("</%s>", ln);
    xmlFree(ln);
}


int deal_xlsx(unsigned char* input_file,unsigned char* output_file)
{
    cul_log_debug_string("start deal with xlsx");
    cul_log_debug_string("input file is %s",input_file);
    cul_log_debug_string("ouput file is %s",output_file);
    if(xlsx_init(input_file))
    {
        return -1;
    }
    return 0;
}

int xlsx_init(unsigned char* input_file)
{
    FILE *dump = NULL;
    unsigned char* type = NULL;
    unsigned char* target = NULL;
    unsigned char* part = NULL;
    opc_uint8_t buf[100];
    opc_uint32_t len=0;
    mceTextReader_t reader;
    opcContainerInputStream *stream = NULL;
    c = NULL;
    if(OPC_ERROR_NONE!=opcInitLibrary())
    {
        cul_log_debug_string("init library failed");
        MessageBox(NULL,"init library failed",gbk_error,MB_OK);
    }
    c =opcContainerOpen(input_file, OPC_OPEN_READ_ONLY, NULL, NULL);
    if(c==NULL)
    {
        cul_log_debug_string("open xlsx file failed");
        MessageBox(NULL,gbk_file_error,gbk_error,MB_OK);
        return -1;
    }
    dump = fopen("dump.log","w");
    opcContainerDump(c, dump);
    fclose(dump);

    //some test code
    cul_log_debug_string("a list of all content types of the OPC container.");
    for(type=opcContentTypeFirst(c);NULL!=type;type=opcContentTypeNext(c, type)) 
    {
        cul_log_debug_string("%s", type);
    }
    cul_log_debug_string("a list of all relation types being used on the container.");
    for(type=opcContentTypeFirst(c);NULL!=type;type=opcContentTypeNext(c, type)) 
    {
        cul_log_debug_string("%s", type);
    }
    cul_log_debug_string("list relations targets");
    for(target=opcExternalTargetFirst(c);NULL!=target;type=opcExternalTargetNext(c, type)) 
    {
        
        cul_log_debug_string("%s", target);
    }
    cul_log_debug_string("a list of all parts in the OPC package.");
    for(part=opcPartGetFirst(c);OPC_PART_INVALID!=part;part=opcPartGetNext(c, part)) 
    {
        
        cul_log_debug_string("%s;", part, opcPartGetType(c, part));
    }
    cul_log_debug_string("all relations are dumped");
    if(OPC_ERROR_NONE != opcXmlReaderOpen(c,&reader, _X("xl/sharedStrings.xml"), NULL,0, 0))
    {
        cul_log_debug_string("sheet1 is not exsit");
    }

    mce_start_document(&reader) 
    {
         mce_start_element(&reader, NULL, NULL) 
         {
              dumpElement(&reader);
         } 
         mce_end_element(&reader);
    } mce_end_document(&reader);
    mceTextReaderCleanup(&reader);

    part=opcPartFind(c, _X("xl/sharedStrings.xml"), NULL, 0);
    stream=opcContainerOpenInputStream(c, part);

    while((len=opcContainerReadInputStream(stream, buf, sizeof(buf)))>0) 
    {
        cul_log_debug_string("%.*s", len, buf);
    }
    opcContainerCloseInputStream(stream);
    opcContainerClose(c, OPC_CLOSE_NOW);
    return 0;
}



#if 0
#include "stdafx.h"
#include <opc/opc.h>
#include <stdio.h>
// basic file operations 
#include <iostream> 
#include <fstream> 

using namespace std;

FILE* pFile;

static void dumpSharedrows(mceTextReader_t *reader)
{
#if 0
    xmlChar *ln = xmlStrdup(xmlTextReaderLocalName(reader->reader));
    const char * lnvalue = (const char*)ln;
    if ((strcmp(lnvalue, "si")) == 0) {
        //id3++; 
    }
#endif
    mce_skip_attributes(reader);
    //mce_start_attributes(reader){ }
    //mce_end_attributes(reader);

    mce_start_children(reader)
    {
        mce_start_element(reader, NULL, NULL)
        {
            dumpSharedrows(reader);
        }
        mce_end_element(reader);

        mce_start_text(reader)
        {

            for (const xmlChar *txt = xmlTextReaderConstValue(reader->reader); 0 != *txt; txt++)
            {
                putc(*txt, pFile);
            }
            putc(',', pFile);
            //  putc(*txt, stdout);
            //putc('\n', stdout);
            //remove((const char *)xmlTextReaderConstValue(reader->reader));

            //LOGI("%s", xmlTextReaderConstValue(reader->reader));

        }
        mce_end_text(reader);
    }
    mce_end_children(reader);

}






int _tmain(int argc, _TCHAR* argv[])
{

    const char *filename = "template.csv";
        const char *mode = "w+";
        fopen_s(&pFile, filename, mode);
    opcInitLibrary();
    opcContainer *c = opcContainerOpen(_X("template.xlsx"), OPC_OPEN_READ_ONLY, NULL, NULL);
    if (NULL != c) {
        mceTextReader_t reader;

        if (OPC_ERROR_NONE == opcXmlReaderOpen(c, &reader, _X("xl/sharedStrings.xml"), NULL, 0, 0))
        {
            mce_start_document(&reader)
            {
                mce_start_element(&reader, NULL, NULL)
                {
                    dumpSharedrows(&reader);
                                }
                mce_end_element(&reader);
            }
            mce_end_document(&reader); 
                        mceTextReaderCleanup(&reader);
        }
        opcContainerClose(c, OPC_CLOSE_NOW);
    }
    opcFreeLibrary();
    fclose(pFile);
    return 0;
}

#endif

