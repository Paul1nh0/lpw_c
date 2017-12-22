#include "windows.h"
#include "windowsx.h"
#include "main.h"
#include "dialogs.h"
#include "resource.h"
#include "ShellApi.h"
#include "stdio.h"
#include "time.h"
#include "libxl.h"
#include "enum.h"
#include "encoder.h"
#include "gbk_string.h"

typedef struct
{
    double date;
    char org_id[256];
    char name[20];
    char id[30];
    char phone_no[20];
    char bank[30];
    char card_no[30];
    double amount;
    double periods;
    double total_amount;
    double balance_amount;
    char cuishou[256];
    char status[256];
}Sheet0Data;

typedef struct
{
    char id[30];
}Sheet2Data;


static HWND s_hwnd=NULL;
static BookHandle book=NULL;
static BookHandle book2 = NULL;
Sheet2Data* p_sheet2=NULL;
Sheet0Data* p_sheet0=NULL;
Sheet0Data* p_sheet3=NULL;

int sheet2_len = 0;
int sheet0_len = 0;
int sheet3_len = 0;

void Main_OnDropFiles(HWND hwnd, HDROP wParam);
int deal_xlsx(unsigned char* input_file,unsigned char* output_file);
int xlsx_init(unsigned char* input_file);
int xlsx_get_sheet_0();
int xlsx_get_sheet_1();
int xlsx_get_sheet_2();
int xlsx_get_sheet_3();
int xlsx_get_sheet_4();
int xlsx_get_sheet_5();
int xlsx_get_sheet_6();

int xlsx_set_sheet_0();
int xlsx_set_sheet_1();
int xlsx_set_sheet_2();
int xlsx_set_sheet_3();



int xlsx_close();


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

void str_to_hex(char *pbDest, char *pbSrc, int nLen)
{
    char	ddl,ddh;
    int i;
    
    for (i=0; i<nLen; i++)
    {
        ddh = 48 + ((unsigned char)pbSrc[i] >>4);
        ddl = 48 + ((unsigned char)pbSrc[i] & 0x0f);
        if (ddh > 57) ddh = ddh + 7;
        if (ddl > 57) ddl = ddl + 7;
        pbDest[i*3] = ddh;
        pbDest[i*3+1] = ddl;
        pbDest[i*3+2] = 0x20;
    }

    pbDest[nLen*3] = '\0';
}


int cul_log_debug_dump(const char* data,int len)
{
    char log_string[8096*2]={0x00};
    str_to_hex(log_string,data,len);
    return cul_log_debug_string(log_string);
}

int cul_log_debug_string(const char* IN x_format,...)
{
#if 1
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
#endif
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
		*(strrchr(szFile,'.'))=0;
        strcat(szFile,"_out.xlsx");
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
    *(strrchr(strFileName,'.'))=0;
    strcat(strFileName,"_out.xlsx");
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
             if(deal_xlsx(input_name,output_name))
             {
                 xlsx_close();
             }
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

int is_in_sheet2(char* in_id)
{
    int i = 0;
    Sheet2Data* sheet2 = p_sheet2;
    for(i=0;i<sheet2_len;i++)
    {
        cul_log_debug_string("%d %s,%s",i,in_id,sheet2->id);
        if(_strcmpi(in_id,sheet2->id)==0)
            return 0;
        sheet2++;
    }
    return -1;
}

int deal_xlsx(unsigned char* input_file,unsigned char* output_file)
{
    cul_log_debug_string("start deal with xlsx");
    cul_log_debug_string("input file is %s",input_file);
    cul_log_debug_string("ouput file is %s",output_file);
    if(xlsx_init(input_file))
    {
        MessageBox(NULL,"init failed","error",MB_OK);
        return -1;
    }
    if(xlsx_get_sheet_2())
    {
        MessageBox(NULL,"sheet 2 process failed","error",MB_OK);
        return -1;
    }
    if(xlsx_get_sheet_0())
    {
        MessageBox(NULL,"sheet 0 process failed","error",MB_OK);
        return -1;
    }
    if(xlsx_get_sheet_1())
    {
        MessageBox(NULL,"sheet 1 process failed","error",MB_OK);
        return -1;
    }
    if(xlsx_get_sheet_3())
    {
        MessageBox(NULL,"sheet 3 set failed","error",MB_OK);
        return -1;
    }
    
    if(xlsx_get_sheet_4())
    {
        MessageBox(NULL,"sheet 4 set failed","error",MB_OK);
        return -1;
    }
    if(xlsx_get_sheet_5())
    {
        MessageBox(NULL,"sheet 5 set failed","error",MB_OK);
        return -1;
    }
    if(xlsx_set_sheet_0())
    {
        MessageBox(NULL,"sheet 0 set failed","error",MB_OK);
        return -1;
    }

    if(xlsx_set_sheet_1())
    {
        MessageBox(NULL,"sheet 1 set failed","error",MB_OK);
        return -1;
    }
    if(xlsx_set_sheet_2())
    {
        MessageBox(NULL,"sheet 2 set failed","error",MB_OK);
        return -1;
    }
    xlBookSave(book2,output_file);
    xlsx_close();
    return 0;
}

int xlsx_init(unsigned char* input_file)
{
	book = xlCreateXMLBook();
	if(!book) 
	{
	    cul_log_debug_string("create xml book failed");
	    return -1;
	}
	if(!xlBookLoad(book, input_file)) 
	{
		cul_log_debug_string("load file failed");
		return -1;
	}
	book2 = xlCreateXMLBook();
	if(!book2) 
	{
		cul_log_debug_string("create xml book2 failed");
		return -1;
	}

    return 0;
}


int xlsx_close()
{
    if(!book)
    {
        xlBookRelease(book);
    }
    if(!book2)
    {
        xlBookRelease(book2);
    }
    return 0;
}

int xlsx_get_sheet_0()
{
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int first_col1 = 0;
    int first_row1 = 0;
    int last_col1 = 0;
    int last_row1 = 0;
    int i = 0;
    int j = 0;
    int cell_type = -1;
    unsigned char* s = NULL;
    Sheet0Data* sheet0 = NULL;
    char* temp_id = NULL;
    SheetHandle sheet = xlBookGetSheet(book, 0);
    SheetHandle sheet1 = xlBookGetSheet(book,1);
    if(!sheet)
    {
        cul_log_debug_string("sheet 0 is not exsit");
        return -1;
    }
    if(!sheet1)
    {
        cul_log_debug_string("sheet 1 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 0 %s",xlSheetName(sheet));
    cul_log_debug_string("sheet 1 %s",xlSheetName(sheet1));
    first_col = xlSheetFirstCol(sheet);
    first_row = xlSheetFirstRow(sheet);
    last_col = xlSheetLastCol(sheet);
    last_row = xlSheetLastRow(sheet);
    cul_log_debug_string("sheet 0 layout %d %d %d %d",first_col,first_row,last_col,last_row);
    first_col1 = xlSheetFirstCol(sheet1);
    first_row1 = xlSheetFirstRow(sheet1);
    last_col1 = xlSheetLastCol(sheet1);
    last_row1 = xlSheetLastRow(sheet1);
    cul_log_debug_string("sheet 1 layout %d %d %d %d",first_col1,first_row1,last_col1,last_row1);
    if(first_col!=0 ||first_row!=0)
    {
        cul_log_debug_string("sheet 0 init data failed");
        return -1;
    }
    if(last_col != 15)
    {
        cul_log_debug_string("sheet 0 col is not 15 failed");
        return -1;
    }
    if(first_col1!=0 ||first_row1!=0)
    {
        cul_log_debug_string("sheet 1 init data failed");
        return -1;
    }
    if(last_col1 != 15)
    {
        cul_log_debug_string("sheet 1 col is not 15 failed");
        return -1;
    }
    while(1)
    {
        cell_type= xlSheetCellType(sheet,last_row-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row--;
        }
        else
        {
             break;
        }
        if(last_row == 1 ||last_row == 0)
        {
            cul_log_debug_string("sheet 0 have not data ");
            return -1;;
        }
    }
    cul_log_debug_string("after relocate last_row is %d",last_row);
    while(1)
    {
        cell_type= xlSheetCellType(sheet1,last_row1-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row1--;
        }
        else
        {
             break;
        }
        if(last_row1 == 1 ||last_row1 == 0)
        {
            cul_log_debug_string("sheet 1 have not data ");
            return -1;;
        }
    }
    cul_log_debug_string("after relocate last_row1 is %d",last_row1);
    p_sheet0=(Sheet0Data*)malloc((last_row+last_row1-2)*sizeof(Sheet0Data));
    if(!p_sheet0)
    {
        cul_log_debug_string("sheet 0 malloc mem failed");
    }
    sheet0 = p_sheet0;
    memset(p_sheet0,0x00,(last_row+last_row1-2)*sizeof(Sheet0Data));
    for(i=1;i<last_row;i++)
    {
        cul_log_debug_string("row %d start p_sheet0 row %d",i,j);
        cell_type= xlSheetCellType(sheet,i,14);
        if(cell_type != CELLTYPE_BLANK && cell_type != CELLTYPE_EMPTY)
        {
            cul_log_debug_string("%d row has pay back %f",i,xlSheetReadNum(sheet,i,14,0));
            continue;
        }

        cell_type= xlSheetCellType(sheet,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            temp_id = xlSheetReadStr(sheet,i,3,0);
            cul_log_debug_string("row %d id=%s",i,temp_id);
            if(is_in_sheet2(temp_id)==0)
            {
                cul_log_debug_string("%d row is in sheet2",i);
                continue;
            }
            else
            {
                if(strlen(temp_id)>29)
                {
                     cul_log_debug_string("%s is over 255 len",temp_id);
                }
                strcpy(sheet0->id,temp_id);
            }
        }
        else
        {
            cul_log_debug_string("sheet0 %d 3 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,0);
        if(cell_type == CELLTYPE_NUMBER)
        {
            sheet0->date = xlSheetReadNum(sheet,i,0,0);
            cul_log_debug_string("%f",sheet0->date);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 0 data is not num",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,1);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,1,0);
            if(strlen(s)>255)
            {
                cul_log_debug_string("%s is over 255 len",s);
            }
            strcpy(sheet0->org_id,s);
            cul_log_debug_string("%s",sheet0->org_id);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 1 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,2);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,2,0);
            if(strlen(s)>19)
            {
                cul_log_debug_string("%s is over 19 len",s);
            }
            strcpy(sheet0->name,s);
            cul_log_debug_string("%s",sheet0->name);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 2 data is not string",i);
            return -1;
        }
        


        cell_type= xlSheetCellType(sheet,i,4);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,4,0);
            if(strlen(s)>19)
            {
                cul_log_debug_string("%s is over 19 len",s);
            }
            strcpy(sheet0->phone_no,s);
            cul_log_debug_string("%s",sheet0->phone_no);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 4 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,5);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,5,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 29 len",s);
            }
            strcpy(sheet0->bank,s);
            cul_log_debug_string("%s",sheet0->bank);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 5 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,6);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,6,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 29 len",s);
            }
            strcpy(sheet0->card_no,s);
            cul_log_debug_string("%s",sheet0->card_no);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 6 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,7);
        if(cell_type == CELLTYPE_NUMBER)
        {
            sheet0->amount = xlSheetReadNum(sheet,i,7,0);
            cul_log_debug_string("%f",sheet0->amount);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 7 data is not num",i);
            return -1;
        }
        sheet0++;
        j++;
    }
    for(i=1;i<last_row1;i++)
    {
        cul_log_debug_string("row %d start p_sheet0 row %d",i,j);
        cell_type= xlSheetCellType(sheet1,i,14);
        if(cell_type != CELLTYPE_BLANK && cell_type != CELLTYPE_EMPTY)
        {
            cul_log_debug_string("%d row has pay back %f",i,xlSheetReadNum(sheet,i,14,0));
            continue;
        }

        cell_type= xlSheetCellType(sheet1,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            temp_id = xlSheetReadStr(sheet1,i,3,0);
            cul_log_debug_string("row %d id=%s",i,temp_id);
            if(is_in_sheet2(temp_id)==0)
            {
                cul_log_debug_string("%d row is in sheet2",i);
                continue;
            }
            else
            {
                if(strlen(temp_id)>29)
                {
                     cul_log_debug_string("%s is over 255 len",temp_id);
                }
                strcpy(sheet0->id,temp_id);
            }
        }
        else
        {
            cul_log_debug_string("sheet0 %d 3 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,0);
        if(cell_type == CELLTYPE_NUMBER)
        {
            sheet0->date = xlSheetReadNum(sheet1,i,0,0);
            cul_log_debug_string("%f",sheet0->date);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 0 data is not num",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,1);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet1,i,1,0);
            if(strlen(s)>255)
            {
                cul_log_debug_string("%s is over 255 len",s);
            }
            strcpy(sheet0->org_id,s);
            cul_log_debug_string("%s",sheet0->org_id);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 1 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,2);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet1,i,2,0);
            if(strlen(s)>19)
            {
                cul_log_debug_string("%s is over 19 len",s);
            }
            strcpy(sheet0->name,s);
            cul_log_debug_string("%s",sheet0->name);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 2 data is not string",i);
            return -1;
        }
        


        cell_type= xlSheetCellType(sheet1,i,4);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet1,i,4,0);
            if(strlen(s)>19)
            {
                cul_log_debug_string("%s is over 19 len",s);
            }
            strcpy(sheet0->phone_no,s);
            cul_log_debug_string("%s",sheet0->phone_no);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 4 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,5);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet1,i,5,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 29 len",s);
            }
            strcpy(sheet0->bank,s);
            cul_log_debug_string("%s",sheet0->bank);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 5 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,6);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet1,i,6,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 29 len",s);
            }
            strcpy(sheet0->card_no,s);
            cul_log_debug_string("%s",sheet0->card_no);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 6 data is not string",i);
            return -1;
        }

        cell_type= xlSheetCellType(sheet1,i,7);
        if(cell_type == CELLTYPE_NUMBER)
        {
            sheet0->amount = xlSheetReadNum(sheet1,i,7,0);
            cul_log_debug_string("%f",sheet0->amount);
        }
        else
        {
            cul_log_debug_string("sheet0 %d 7 data is not num",i);
            return -1;
        }
        sheet0++;
        j++;
    }
    sheet0_len = j;
    return 0;
}

int xlsx_get_sheet_1()
{
    SheetHandle sheet = xlBookGetSheet(book, 1);
    if(!sheet)
    {
        cul_log_debug_string("sheet 1 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 1 %s",xlSheetName(sheet));
    
    return 0;
}

int xlsx_get_sheet_2()
{
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int i = 0;
    int cell_type = -1;
    unsigned char* s = NULL;
    Sheet2Data* sheet2 = NULL;
    SheetHandle sheet = xlBookGetSheet(book, 2);
    if(!sheet)
    {
        cul_log_debug_string("sheet 2 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 2 %s",xlSheetName(sheet));
    first_col = xlSheetFirstCol(sheet);
    first_row = xlSheetFirstRow(sheet);
    last_col = xlSheetLastCol(sheet);
    last_row = xlSheetLastRow(sheet);
    cul_log_debug_string("sheet 2 layout %d %d %d %d",first_col,first_row,last_col,last_row);
    if(first_col!=0 ||first_row!=0)
    {
        cul_log_debug_string("sheet 2 init data failed");
        return -1;
    }
    if(last_col != 6 && last_col != 7)
    {
        cul_log_debug_string("sheet 2 col is not 6 failed");
        return -1;
    }
    //重定位最后一行
    while(1)
    {
        cell_type= xlSheetCellType(sheet,last_row-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row--;
        }
        else
        {
             break;
        }
        if(last_row == 1 ||last_row == 0)
        {
            cul_log_debug_string("have not data");
            break;
        }
    }
    cul_log_debug_string("after relocate last_row is %d",last_row);
    if(last_row == 1 ||last_row == 0)
    {
        p_sheet2 = NULL;
        return 0;
    }
    p_sheet2 = (Sheet2Data*)malloc((last_row-1)*sizeof(Sheet2Data));
    if(!p_sheet2)
    {
        cul_log_debug_string("sheet 2 malloc mem failed");
        return -1;
    }
    sheet2_len = last_row - 1;
    sheet2 = p_sheet2;
    memset(p_sheet2,0x00,(last_row-1)*sizeof(Sheet2Data));
    for(i=1;i<last_row;i++)
    {
        cell_type= xlSheetCellType(sheet,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,3,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 30 len",s);
                return -1;
            }
            strcpy(sheet2->id,xlSheetReadStr(sheet,i,3,0));
            cul_log_debug_string("%s",sheet2->id);
        }
        else
        {
            cul_log_debug_string("sheet2 %d 3 data is not string",i);
            return -1;
        }
        sheet2++;
    }
    return 0;
}

int xlsx_get_sheet_3()
{
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int i = 0;
    int is_find = 0;
    int cell_type = -1;
    double qishu = 1;
    unsigned char* s = NULL;
    SheetHandle sheet = xlBookGetSheet(book, 3);
    if(!sheet)
    {
        cul_log_debug_string("sheet 3 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 3 %s",xlSheetName(sheet));
    first_col = xlSheetFirstCol(sheet);
    first_row = xlSheetFirstRow(sheet);
    last_col = xlSheetLastCol(sheet);
    last_row = xlSheetLastRow(sheet);
    cul_log_debug_string("sheet 3 layout %d %d %d %d",first_col,first_row,last_col,last_row);
    if(first_col!=0 ||first_row!=0)
    {
        cul_log_debug_string("sheet 2 init data failed");
        return -1;
    }
    //重定位最后一行
    while(1)
    {
        cell_type= xlSheetCellType(sheet,last_row-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row--;
        }
        else
        {
             break;
        }
        if(last_row == 1 ||last_row == 0)
        {
            cul_log_debug_string("have not data");
            break;
        }
    }
    cul_log_debug_string("after relocate last_row is %d",last_row);
    if(last_row == 1 ||last_row == 0)
    {
        return 0;
    }
    for(i=1;i<last_row;i++)
    {
        int j = 0;
        cell_type= xlSheetCellType(sheet,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,3,0);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 30 len",s);
                return -1;
            }
            for(j=0;j<sheet0_len;j++)
            {
                if(_strcmpi(s,p_sheet0[j].id)==0)
                {
                    is_find = 1;
                    cell_type= xlSheetCellType(sheet,i,11);
                    if(cell_type == CELLTYPE_STRING)
                    {
                        strcpy(p_sheet0[j].cuishou,xlSheetReadStr(sheet,i,11,0));
                    }
                    else
                    {
                        cul_log_debug_string("is not string");
                    }
                    cell_type= xlSheetCellType(sheet,i,12);
                    if(cell_type == CELLTYPE_STRING)
                    {
                        strcpy(p_sheet0[j].status,xlSheetReadStr(sheet,i,12,0));
                    }
                    else
                    {
                        cul_log_debug_string("is not string2");
                    }

                    //比较代扣日期
                    cell_type= xlSheetCellType(sheet,i,7);
                    if(cell_type == CELLTYPE_NUMBER)
                    {
                        qishu = xlSheetReadNum(sheet,i,7,0);
                    }
                    else
                    {
                        cul_log_debug_string("qishu +++++++ is not number");
                    }
                    cul_log_debug_string("qishu +++++++ is %f",qishu);
                    cell_type = xlSheetCellType(sheet,i,0);
                    if(cell_type == CELLTYPE_NUMBER)
                    {
                        if(0!=p_sheet0[j].date-xlSheetReadNum(sheet,i,0,NULL))
                        {
                            qishu=qishu+1;
                        }
                    }
                    else
                    {
                        cul_log_debug_string("is not string2");
                    }
                    p_sheet0[j].periods = qishu;
                    qishu = 1;
                    break;
                }
            }
        }
        else
        {
            cul_log_debug_string("sheet2 %d 3 data is not string",i);
            return -1;
        }
    }
    return 0;
}

int xlsx_get_sheet_4()
{
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int i = 0;
    int cell_type = -1;
    unsigned char* s = NULL;
    SheetHandle sheet = xlBookGetSheet(book, 4);
    if(!sheet)
    {
        cul_log_debug_string("sheet 4 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 4 %s",xlSheetName(sheet));
    first_col = xlSheetFirstCol(sheet);
    first_row = xlSheetFirstRow(sheet);
    last_col = xlSheetLastCol(sheet);
    last_row = xlSheetLastRow(sheet);
    cul_log_debug_string("sheet 4 layout %d %d %d %d",first_col,first_row,last_col,last_row);
    if(first_col!=0 ||first_row!=0)
    {
        cul_log_debug_string("sheet 2 init data failed");
        return -1;
    }
    //重定位最后一行
    while(1)
    {
        cell_type= xlSheetCellType(sheet,last_row-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row--;
        }
        else
        {
             break;
        }
        if(last_row == 1 ||last_row == 0)
        {
            cul_log_debug_string("have not data");
            break;
        }
    }
    cul_log_debug_string("after relocate last_row is %d",last_row);
    if(last_row == 1 ||last_row == 0)
    {
        return 0;
    }
    for(i=1;i<last_row;i++)
    {
        int j = 0;
        cell_type= xlSheetCellType(sheet,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            s = xlSheetReadStr(sheet,i,3,0);
            cul_log_debug_string("id is %s",s);
            if(strlen(s)>29)
            {
                cul_log_debug_string("%s is over 30 len",s);
                return -1;
            }
            for(j=0;j<sheet0_len;j++)
            {
                if(_strcmpi(s,p_sheet0[j].id)==0)
                {
                    cell_type= xlSheetCellType(sheet,i,11);
                    if(cell_type == CELLTYPE_NUMBER)
                    {
                        p_sheet0[j].total_amount=xlSheetReadNum(sheet,i,11,0);
                    }
                    else
                    {
                        cul_log_debug_string("is not NUMBER");
                    }
                    cell_type= xlSheetCellType(sheet,i,12);
                    if(cell_type == CELLTYPE_NUMBER)
                    {
                        p_sheet0[j].balance_amount=xlSheetReadNum(sheet,i,12,0);
                    }
                    else
                    {
                        cul_log_debug_string("is not NUMBER");
                    }
                    break;
                }
                cul_log_debug_string("%s is not found at sheet 0",s);
            }
        }
        else
        {
            cul_log_debug_string("sheet4 %d  data is not string",i);
            return -1;
        }
    }
    return 0;
}


int xlsx_get_sheet_5()
{
    int first_col = 0;
    int first_row = 0;
    int last_col = 0;
    int last_row = 0;
    int i = 0;
    int cell_type = -1;
    SheetHandle sheet = xlBookGetSheet(book, 3);
    if(!sheet)
    {
        cul_log_debug_string("sheet 3 is not exsit");
        return -1;
    }
    cul_log_debug_string("sheet 3 %s",xlSheetName(sheet));
    first_col = xlSheetFirstCol(sheet);
    first_row = xlSheetFirstRow(sheet);
    last_col = xlSheetLastCol(sheet);
    last_row = xlSheetLastRow(sheet);
    cul_log_debug_string("sheet 3 layout %d %d %d %d",first_col,first_row,last_col,last_row);
    if(first_col!=0 ||first_row!=0)
    {
        cul_log_debug_string("sheet 2 init data failed");
        return -1;
    }
    //重定位最后一行
    while(1)
    {
        cell_type= xlSheetCellType(sheet,last_row-1,0);
        if(cell_type == CELLTYPE_BLANK ||cell_type == CELLTYPE_EMPTY)
        {
             last_row--;
        }
        else
        {
             break;
        }
        if(last_row == 1 ||last_row == 0)
        {
            cul_log_debug_string("have not data");
            break;
        }
    }
    cul_log_debug_string("after relocate last_row is %d",last_row);
    if(last_row == 1 ||last_row == 0)
    {
        return 0;
    }
    sheet3_len = last_row -1;
    p_sheet3=(Sheet0Data*)malloc((last_row-1)*sizeof(Sheet0Data));
    if(!p_sheet3)
    {
        cul_log_debug_string("sheet 5 malloc mem failed");
    }
    memset(p_sheet3,0x00,(last_row-1)*sizeof(Sheet0Data));
    for(i=1;i<last_row;i++)
    {
        cul_log_debug_string("start %d",i);
        cell_type= xlSheetCellType(sheet,i,0);
        if(cell_type == CELLTYPE_NUMBER)
        {
            p_sheet3[i-1].date = xlSheetReadNum(sheet,i,0,0);
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,1);
        
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].org_id,xlSheetReadStr(sheet,i,1,0));
        }
        else
        {
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,3);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].id,xlSheetReadStr(sheet,i,3,0));
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,4);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].phone_no,xlSheetReadStr(sheet,i,4,0));
        }
        else
        {
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,5);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].bank,xlSheetReadStr(sheet,i,5,0));
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,6);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].card_no,xlSheetReadStr(sheet,i,6,0));
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,7);
        if(cell_type == CELLTYPE_NUMBER)
        {
            p_sheet3[i-1].periods=xlSheetReadNum(sheet,i,7,0);
        }
        else
        {
            return -1;
        }

        cell_type= xlSheetCellType(sheet,i,8);
        if(cell_type == CELLTYPE_NUMBER)
        {
            p_sheet3[i-1].amount=xlSheetReadNum(sheet,i,8,0);
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,9);
        if(cell_type == CELLTYPE_NUMBER)
        {
            p_sheet3[i-1].total_amount=xlSheetReadNum(sheet,i,9,0);
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,10);
        if(cell_type == CELLTYPE_NUMBER)
        {
            p_sheet3[i-1].balance_amount=xlSheetReadNum(sheet,i,10,0);
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,11);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].cuishou,xlSheetReadStr(sheet,i,11,0));
        }
        else if(cell_type == CELLTYPE_BLANK || cell_type == CELLTYPE_EMPTY)
        {
            //do nothing
        }
        else
        {
            return -1;
        }
        cell_type= xlSheetCellType(sheet,i,12);
        if(cell_type == CELLTYPE_STRING)
        {
            strcpy(p_sheet3[i-1].status,xlSheetReadStr(sheet,i,12,0));
        }
        else if(cell_type == CELLTYPE_BLANK || cell_type == CELLTYPE_EMPTY)
        {
            //do nothing
        }
        else
        {
            return -1;
        }
        cul_log_debug_string("end %d",i);
    }
    return 0;
}


int xlsx_set_sheet_0()
{
    int i = 0;
    SheetHandle sheet = NULL;
    Sheet0Data* sheet0 = p_sheet0;
    sheet = xlBookAddSheet(book2,gbk_curr_week,NULL);
    if(!sheet)
    {
        cul_log_debug_string("sheet 0 failed");
    }

    xlSheetWriteStr(sheet,0,0,gbk_sheet0_0,NULL);
    xlSheetWriteStr(sheet,0,1,gbk_sheet0_1,NULL);
    xlSheetWriteStr(sheet,0,2,gbk_sheet0_2,NULL);
    xlSheetWriteStr(sheet,0,3,gbk_sheet0_3,NULL);
    xlSheetWriteStr(sheet,0,4,gbk_sheet0_4,NULL);
    xlSheetWriteStr(sheet,0,5,gbk_sheet0_5,NULL);
    xlSheetWriteStr(sheet,0,6,gbk_sheet0_6,NULL);
    xlSheetWriteStr(sheet,0,7,gbk_sheet0_7,NULL);
    xlSheetWriteStr(sheet,0,8,gbk_sheet0_8,NULL);
    xlSheetWriteStr(sheet,0,9,gbk_sheet0_9,NULL);
    xlSheetWriteStr(sheet,0,10,gbk_sheet0_10,NULL);
    xlSheetWriteStr(sheet,0,11,gbk_sheet0_11,NULL);
    xlSheetWriteStr(sheet,0,12,gbk_sheet0_12,NULL);
#if 1

    for(i=0;i<sheet0_len;i++)
    {
        xlSheetWriteNum(sheet,i+1,0,p_sheet0[i].date,NULL);
        
        xlSheetWriteStr(sheet,i+1,1,p_sheet0[i].org_id,NULL);
        xlSheetWriteStr(sheet,i+1,2,p_sheet0[i].name,NULL);
        xlSheetWriteStr(sheet,i+1,3,p_sheet0[i].id,NULL);
        xlSheetWriteStr(sheet,i+1,4,p_sheet0[i].phone_no,NULL);
        xlSheetWriteStr(sheet,i+1,5,p_sheet0[i].bank,NULL);
        xlSheetWriteStr(sheet,i+1,6,p_sheet0[i].card_no,NULL);
        xlSheetWriteStr(sheet,i+1,11,p_sheet0[i].cuishou,NULL);
        xlSheetWriteStr(sheet,i+1,12,p_sheet0[i].status,NULL);
        xlSheetWriteNum(sheet,i+1,8,p_sheet0[i].amount,NULL);
        xlSheetWriteNum(sheet,i+1,9,p_sheet0[i].total_amount,NULL);
        xlSheetWriteNum(sheet,i+1,10,p_sheet0[i].balance_amount,NULL);
        if(p_sheet0[i].periods-0 == 0)
        {
            p_sheet0[i].periods = 1;
        }
        xlSheetWriteNum(sheet,i+1,7,p_sheet0[i].periods,NULL);
    }
#endif 
    xlSheetSetAutoFitArea(sheet,0,0,1,12);
    //xlSheetSetCol(sheet,0,12,18,NULL,0);
    return 0;
}

int xlsx_set_sheet_1()
{
    int i = 0;
    int j = 0;
    int rows = 0;
    int cols = 0;
    int cell_type = -1;
    SheetHandle sheet_init = NULL;
    SheetHandle sheet = NULL;
    sheet_init = xlBookGetSheet(book,3);
    if(!sheet_init)
    {
        cul_log_debug_string("book1 has not sheet 3");
        return -1;
    }
    sheet = xlBookAddSheet(book2,gbk_last_week,NULL);
    if(!sheet)
    {
        cul_log_debug_string("book2 add sheet1 failed");
        return -1;
    }
    rows=xlSheetLastRow(sheet_init);
    cols = xlSheetLastCol(sheet_init);
    cul_log_debug_string("book1 sheet3 row=%d cols=%d",rows,cols);
    
    for(i = 0;i<rows;i++)
    {
        for(j = 0;j<cols;j++)
        {
            cell_type= xlSheetCellType(sheet_init,i,j);
            {
                cul_log_debug_string("cell type is %d %d %d",i,j,cell_type);
                if(cell_type == CELLTYPE_STRING)
                {
                    cul_log_debug_string("row %d col %d %s",i,j,xlSheetReadStr(sheet_init,i,j,0));
                    xlSheetWriteStr(sheet,i,j,xlSheetReadStr(sheet_init,i,j,0),NULL);
                }
                else if(cell_type == CELLTYPE_NUMBER)
                {
                    cul_log_debug_string("row %d col %d %f",i,j,xlSheetReadNum(sheet_init,i,j,0));
                    xlSheetWriteNum(sheet,i,j,xlSheetReadNum(sheet_init,i,j,0),NULL);
                }
                else if(cell_type == CELLTYPE_BLANK)
                {
                    xlSheetWriteBlank(sheet,i,j,NULL);
                }
                else if(cell_type == CELLTYPE_EMPTY)
                {
                    ;
                }
                else
                {
                    cul_log_debug_string("sheet 1 out celltype is %d %d %d",cell_type,i,j);
                }
            }
        }
    }
    xlSheetSetAutoFitArea(sheet,0,0,1,cols);
    return 0;
}

int xlsx_set_sheet_2()
{
    int i = 0;
    int last_m[7]= {0x00};
    int curr_m[7]={0x00};
    FormatHandle format = NULL;
    SheetHandle sheet = NULL;
    sheet = xlBookAddSheet(book2,gbk_tongjibiao,NULL);
    if(!sheet)
    {
        cul_log_debug_string("book2 add sheet2 failed");
        return -1;
    }
    format = xlBookAddFormat(book2,NULL);
    if(!format)
    {
        cul_log_debug_string("book2 add format failed");
        return -1;
    }
    xlFormatSetAlignH(format,ALIGNH_CENTER);
    xlFormatSetAlignV(format,ALIGNV_CENTER);
    xlFormatSetBorder(format,BORDERSTYLE_THIN);
    xlSheetSetMerge(sheet,0,0,0,9);
    xlSheetWriteStr(sheet,0,0,gbk_benzhouyuqishuju,format);

    xlSheetWriteStr(sheet,1,0,gbk_yuqiqishu,format);
    xlSheetWriteStr(sheet,1,1,gbk_last_week,format);
    xlSheetWriteStr(sheet,1,2,gbk_curr_week,format);
    xlSheetWriteStr(sheet,1,3,gbk_cuihuishuliang,format);
    xlSheetWriteStr(sheet,1,4,gbk_chulifangan,format);
    xlSheetWriteStr(sheet,1,5,gbk_jianshu,format);
    xlSheetWriteStr(sheet,1,6,gbk_sheet0_10,format);
    xlSheetWriteStr(sheet,1,7,gbk_zhanghuyue,format);
    xlSheetWriteStr(sheet,1,8,gbk_tijibili,format);
    xlSheetWriteStr(sheet,1,9,gbk_huaizhangjitixing,format);

    xlSheetWriteStr(sheet,2,0,"M1",format);
    xlSheetWriteStr(sheet,3,0,"M2",format);
    xlSheetWriteStr(sheet,4,0,"M3",format);
    xlSheetWriteStr(sheet,5,0,"M4",format);
    xlSheetWriteStr(sheet,6,0,"M5",format);
    xlSheetWriteStr(sheet,9,0,"M6",format);
    xlSheetWriteStr(sheet,13,0,"M6+",format);
    xlSheetWriteStr(sheet,15,0,gbk_heji,format);
    xlSheetSetMerge(sheet,6,8,0,0);
    xlSheetSetMerge(sheet,9,12,0,0);
    xlSheetSetMerge(sheet,13,14,0,0);
    for(i=0;i<sheet3_len;i++)
    {
        if(0==p_sheet3[i].periods-1)
        {
            last_m[0]++;
        }
        else if(0 == p_sheet3[i].periods-2)
        {
            last_m[1]++;
        }
        else if(0 == p_sheet3[i].periods-3)
        {
            last_m[2]++;
        }
        else if(0 == p_sheet3[i].periods-4)
        {
            last_m[3]++;
        }
        else if(0 == p_sheet3[i].periods-5)
        {
            last_m[4]++;
        }
        else if(0 == p_sheet3[i].periods-6)
        {
            last_m[5]++;
        }
        else if(0 == p_sheet3[i].periods-0)
        {
            //do nothing
        }
        else
        {
            last_m[6]++;
        }
    }
    for(i=0;i<sheet0_len;i++)
    {
        if(0==p_sheet0[i].periods-1)
        {
            curr_m[0]++;
        }
        else if(0 == p_sheet0[i].periods-2)
        {
            curr_m[1]++;
        }
        else if(0 == p_sheet0[i].periods-3)
        {
            curr_m[2]++;
        }
        else if(0 == p_sheet0[i].periods-4)
        {
            curr_m[3]++;
        }
        else if(0 == p_sheet0[i].periods-5)
        {
            curr_m[4]++;
        }
        else if(0 == p_sheet0[i].periods-6)
        {
            curr_m[5]++;
        }
        else if(0 == p_sheet0[i].periods-0)
        {
            //do nothing
        }
        else
        {
            curr_m[6]++;
        }
    }
    xlSheetWriteNum(sheet,2,1,last_m[0],format);
    xlSheetWriteNum(sheet,3,1,last_m[1],format);
    xlSheetWriteNum(sheet,4,1,last_m[2],format);
    xlSheetWriteNum(sheet,5,1,last_m[3],format);
    xlSheetWriteNum(sheet,6,1,last_m[4],format);
    xlSheetWriteNum(sheet,9,1,last_m[5],format);
    xlSheetWriteNum(sheet,13,1,last_m[6],format);
    xlSheetWriteNum(sheet,15,1,sheet3_len,format);
    xlSheetSetMerge(sheet,6,8,1,1);
    xlSheetSetMerge(sheet,9,12,1,1);
    xlSheetSetMerge(sheet,13,14,1,1);

    xlSheetWriteNum(sheet,2,2,curr_m[0],format);
    xlSheetWriteNum(sheet,3,2,curr_m[1],format);
    xlSheetWriteNum(sheet,4,2,curr_m[2],format);
    xlSheetWriteNum(sheet,5,2,curr_m[3],format);
    xlSheetWriteNum(sheet,6,2,curr_m[4],format);
    xlSheetWriteNum(sheet,9,2,curr_m[5],format);
    xlSheetWriteNum(sheet,13,2,curr_m[6],format);
    xlSheetWriteNum(sheet,15,2,sheet0_len,format);
    xlSheetSetMerge(sheet,6,8,2,2);
    xlSheetSetMerge(sheet,9,12,2,2);
    xlSheetSetMerge(sheet,13,14,2,2);

    xlSheetWriteNum(sheet,2,5,curr_m[0],format);
    xlSheetWriteNum(sheet,3,5,curr_m[1],format);
    xlSheetWriteNum(sheet,4,5,curr_m[2],format);
    xlSheetWriteNum(sheet,5,5,curr_m[3],format);
    xlSheetWriteNum(sheet,6,5,curr_m[4],format);
    xlSheetWriteNum(sheet,9,5,curr_m[5],format);
    xlSheetWriteNum(sheet,13,5,curr_m[6],format);
    xlSheetWriteBlank(sheet,15,5,format);
    xlSheetSetMerge(sheet,6,8,5,5);
    xlSheetSetMerge(sheet,9,12,5,5);
    xlSheetSetMerge(sheet,13,14,5,5);

    xlSheetWriteStr(sheet,2,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,3,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,4,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,5,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,6,4,gbk_goutongjigou,format);
    xlSheetWriteStr(sheet,7,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,8,4,gbk_lvshihan,format);
    xlSheetWriteStr(sheet,9,4,gbk_weiwai,format);
    xlSheetWriteStr(sheet,10,4,gbk_goutongjigou,format);
    xlSheetWriteStr(sheet,11,4,gbk_lvshihan,format);
    xlSheetWriteStr(sheet,12,4,gbk_dianhuaim,format);
    xlSheetWriteStr(sheet,13,4,gbk_weiwai,format);
    xlSheetWriteStr(sheet,14,4,gbk_goutongjigou,format);
    xlSheetWriteBlank(sheet,15,4,format);
    xlSheetSetAutoFitArea(sheet,0,0,16,9);
    return 0;
}

int xlsx_set_sheet_3()
{
    return 0;
}

