#include "windows.h"
#include "windowsx.h"
#include "culmis_tools.h"
#include "resource.h"
#include "cul_trans.h"
#include "ShellApi.h"
#include "cul_json.h"
#include "cul_adaptor.h"

#define MAX_BUFFER_LEN 8192

CulAdaptorReqST structReq;
CulAdaptorRspST structRsp;

static int interface_mode = 0;
static int tran_type= 0;

char req_text[MAX_BUFFER_LEN];
char rsp_text[MAX_BUFFER_LEN];

static HWND s_hwnd;
int (__stdcall*  cul_interface) (char* str1,char* str2,int mode);
HINSTANCE h_interface_dll = NULL;
int cul_free_dll();

int cul_load_dll()
{
    char file_name[256]={0x00};
    GetWindowText(GetDlgItem(s_hwnd,IDC_ET_DLL),file_name,256);
    h_interface_dll = LoadLibrary(file_name);
    if( h_interface_dll == NULL)
    {    
        cul_free_dll();        
        MessageBox(NULL,file_name,TEXT("警告"),MB_OK); 
        return -1;
    }    
    cul_interface  = (int (__stdcall* )(char *,char *,int))GetProcAddress(h_interface_dll, "cul_interface");    
    if(cul_interface == 0)
    {
        cul_free_dll();
        MessageBox(NULL,TEXT("找不到对应函数"),TEXT("警告"),MB_OK);
        return -2;
    }
    return 0;
}

int cul_free_dll()
{
    FreeLibrary(h_interface_dll);
    h_interface_dll = NULL;
    return 0;
}

int cul_req_send()
{
	memset(req_text,0x00,MAX_BUFFER_LEN);
	memset(rsp_text,0x00,MAX_BUFFER_LEN);
	if(h_interface_dll == NULL)
	{
		if(cul_load_dll())
		{
            return -1;
         }
	}
	GetWindowText(GetDlgItem(s_hwnd,IDC_ET_REQ),req_text,MAX_BUFFER_LEN);
	cul_interface(req_text,rsp_text,interface_mode);
	SetWindowText(GetDlgItem(s_hwnd,IDC_ET_RSP),rsp_text);
	cul_free_dll(); 
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
    ofn.lpstrFilter="Dll File(*.dll)\0*.dll;\0\0";
    ofn.nFilterIndex=1;  
    ofn.lpstrFile=szFile;  
    ofn.nMaxFile=sizeof(szFile);  
    ofn.lpstrFileTitle=szFileTitle;  
    ofn.nMaxFileTitle=sizeof(szFileTitle);  
    ofn.Flags=OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST|OFN_EXPLORER;  
    
    if(GetOpenFileName(&ofn))  
    {
        SetWindowText(GetDlgItem(hwnd,IDC_ET_DLL),szFile);
    }
    return 0;
}

int cul_set_json_req_text(HWND hwnd,int trantype)
{
    cJSON* p_root=NULL;
    char* p_edit_req = NULL;
    p_root = cJSON_CreateObject();
    switch(trantype)
    {
    case CUL_LOGIN:
        cJSON_AddStringToObject(p_root,"TranType","00");        
        break;
    case CUL_REDEEM:
        cJSON_AddStringToObject(p_root,"TranType","01");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336022700000008792=99122011230000");
        cJSON_AddStringToObject(p_root,"PassWord","512493");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        break;
    case CUL_VOID:
        cJSON_AddStringToObject(p_root,"TranType","02");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336022700000008792=99122011230000");
        cJSON_AddStringToObject(p_root,"PassWord","512493");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        cJSON_AddStringToObject(p_root,"OrgTrace","000000");
        break;
    case CUL_BALANCE:
        cJSON_AddStringToObject(p_root,"TranType","04");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336022700000008792=99122011230000");
        cJSON_AddStringToObject(p_root,"PassWord","512493");
        break;
    case CUL_REFUND:
        cJSON_AddStringToObject(p_root,"TranType","03");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336022700000008792=99122011230000");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        cJSON_AddStringToObject(p_root,"OrgRef","000000000001");
        cJSON_AddStringToObject(p_root,"OrgDate","20160918");
        break;
    case CUL_INQUIRE:
        cJSON_AddStringToObject(p_root,"TranType","08");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011523");
        break;
    case CUL_ACTIVE:
        cJSON_AddStringToObject(p_root,"TranType","06");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011804000000010000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336112700100021472=99125014440000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","975203");
        break;
    case CUL_ACTIVE_VOID:
        cJSON_AddStringToObject(p_root,"TranType","07");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011523000000010000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336081210001110165=99125018570000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","367132");
        break;
    case CUL_RECHARGE:
        cJSON_AddStringToObject(p_root,"TranType","09");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000010000");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336112700100011903=99125016280000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336112700100021472=99125014440000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","975203");
        break;
    case CUL_SETTLE:
        cJSON_AddStringToObject(p_root,"TranType","99");
        break;
    default:
        break;
    }
    p_edit_req = cJSON_Print(p_root);
    SetWindowText(GetDlgItem(hwnd,IDC_ET_REQ),p_edit_req);
    cJSON_Delete(p_root);
    return 0;
}

int cul_set_xml_req_text(HWND hwnd,int trantype)
{
    cJSON* p_root=NULL;
    char* p_edit_req = NULL;
    p_root = cJSON_CreateObject();
    switch(trantype)
    {
    case CUL_LOGIN:
        cJSON_AddStringToObject(p_root,"TranType","00");        
        break;
    case CUL_REDEEM:
        cJSON_AddStringToObject(p_root,"TranType","01");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336113390200060941=99125014790000");
        cJSON_AddStringToObject(p_root,"PassWord","888888");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        break;
    case CUL_VOID:
        cJSON_AddStringToObject(p_root,"TranType","02");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336113390200060941=99125014790000");
        cJSON_AddStringToObject(p_root,"PassWord","888888");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        cJSON_AddStringToObject(p_root,"OrgTrace","000000");
        break;
    case CUL_BALANCE:
        cJSON_AddStringToObject(p_root,"TranType","04");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336113390200060941=99125014790000");
        cJSON_AddStringToObject(p_root,"PassWord","888888");
        break;
    case CUL_REFUND:
        cJSON_AddStringToObject(p_root,"TranType","03");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336113390200060941=99125014790000");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000000001");
        cJSON_AddStringToObject(p_root,"OrgRef","000000000001");
        cJSON_AddStringToObject(p_root,"OrgDate","00000000");
        break;
    case CUL_INQUIRE:
        cJSON_AddStringToObject(p_root,"TranType","08");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011523");
        break;
    case CUL_ACTIVE:
        cJSON_AddStringToObject(p_root,"TranType","06");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011804000000010000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336112700100021472=99125014440000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","975203");
        break;
    case CUL_ACTIVE_VOID:
        cJSON_AddStringToObject(p_root,"TranType","07");
        cJSON_AddStringToObject(p_root,"ActiveInfo","0100000000011272336112700100011523000000010000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336081210001110165=99125018570000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","975203");
        break;
    case CUL_RECHARGE:
        cJSON_AddStringToObject(p_root,"TranType","09");
        cJSON_AddStringToObject(p_root,"OrderAmount","000000010000");
        cJSON_AddStringToObject(p_root,"MediumInfo","2336112700100011903=99125016280000");
        cJSON_AddStringToObject(p_root,"ManageCardNo","2336112700100021472=99125014440000");
        cJSON_AddStringToObject(p_root,"ManageCardPwd","975203");
        break;
    case CUL_SETTLE:
        cJSON_AddStringToObject(p_root,"TranType","99");
        break;
    default:
        break;
    }
    p_edit_req = cJSON_Print(p_root);
    SetWindowText(GetDlgItem(hwnd,IDC_ET_REQ),p_edit_req);
    cJSON_Delete(p_root);
    return 0;
}

int cul_set_cstruct_req_text(HWND hwnd,int trantype)
{
    char* p_edit_req = NULL;
    CulAdaptorReqST* pReq = &structReq;
    CulAdaptorRspST* pRsp = &structRsp;
    memset(pReq,0x00,sizeof(CulAdaptorReqST));
    memset(pReq,0x20,sizeof(CulAdaptorReqST)-1);
    memset(pRsp,0x00,sizeof(CulAdaptorRspST));
    p_edit_req = (char*)pReq;
    switch(trantype)
    {
    case CUL_LOGIN:
        memcpy(pReq->TranType,"00",2);
        break;
    case CUL_REDEEM:
        memcpy(pReq->TranType,"01",2);
        memcpy(pReq->MediumInfo,"2336113390200060941=99125014790000",34);
        memcpy(pReq->PassWord,"888888",6);
        memcpy(pReq->OrderAmount,"000000000001",12);
        break;
    case CUL_BALANCE:
        memcpy(pReq->TranType,"04",2);
        memcpy(pReq->MediumInfo,"2336113390200060941=99125014790000",34);
        memcpy(pReq->PassWord,"888888",6);
        break;
    case CUL_VOID:
        memcpy(pReq->TranType,"02",2);
        memcpy(pReq->MediumInfo,"2336113390200060941=99125014790000",34);
        memcpy(pReq->OrderAmount,"000000000001",12);
        memcpy(pReq->PassWord,"888888",6);
        memcpy(pReq->OrgTrace,"000000",6);
        break;
    case CUL_REFUND:
        memcpy(pReq->TranType,"03",2);
        memcpy(pReq->MediumInfo,"2336113390200060941=99125014790000",34);
        memcpy(pReq->OrderAmount,"000000000001",12);
        memcpy(pReq->OrgRef,"000000000000",12);
        memcpy(pReq->OrgDate,"20160814",8);
        break;
    case CUL_INQUIRE:
        memcpy(pReq->TranType,"08",2);
        memcpy(pReq->ActiveInfo,"0100000000008122336081210001110207",34);
        break;
    case CUL_ACTIVE:
        memcpy(pReq->TranType,"06",2);
        memcpy(pReq->ActiveInfo,"0100000000008122336081210001110207000000000100",46);
        memcpy(pReq->ManageCardNo,"2336081210001110165=99125018570000",34);
        memcpy(pReq->ManageCardPwd,"367132",6);
        break;
    case CUL_ACTIVE_VOID:
        memcpy(pReq->TranType,"07",2);
        memcpy(pReq->ActiveInfo,"0100000000008122336081210001110207000000000100",46);
        memcpy(pReq->ManageCardNo,"2336081210001110165=99125018570000",34);
        memcpy(pReq->ManageCardPwd,"367132",6);
        break;
    case CUL_RECHARGE:
        memcpy(pReq->TranType,"09",2);
        memcpy(pReq->OrderAmount,"000000010000",12);
        memcpy(pReq->MediumInfo,"2336112700100011903=99125016280000",34);
        memcpy(pReq->ManageCardNo,"2336112700100021472=99125014440000",34);
        memcpy(pReq->ManageCardPwd,"975203",6);
        break;    
    case CUL_SETTLE:
        memcpy(pReq->TranType,"99",2);
        break;
    default:
        break;
    }
    SetWindowText(GetDlgItem(hwnd,IDC_ET_REQ),p_edit_req);
    return 0;
}


int cul_set_req_text(HWND hwnd,int mode,int trantype)
{
    switch(mode)
    {
    case JSON_MODE:
        cul_set_json_req_text(hwnd,trantype);
        break;
    case XML_MODE:
        cul_set_xml_req_text(hwnd,trantype);
        break;
    case CSTRUCT_MODE:
        cul_set_cstruct_req_text(hwnd,trantype);
        break;
    default:
        break;
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
********************************************************************************/
BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    /* Set app icons */
    char strFileName[MAX_PATH]={0x00};
    HINSTANCE hinst = NULL;
    HICON hIcon = LoadIcon((HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE) ,MAKEINTRESOURCE(IDI_ICONAPP));
    SendMessage(hwnd, WM_SETICON, TRUE,  (LPARAM)hIcon);
    SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)hIcon);
    
    /*
    * Add initializing code here
    */
    hinst = GetModuleHandle(NULL);
    GetModuleFileName(hinst, strFileName, MAX_PATH);
    *(strrchr(strFileName,'\\')+1)=0;
    strcat(strFileName,"cul_interface.dll");
    SetWindowText(GetDlgItem(hwnd,IDC_ET_DLL),strFileName);
    s_hwnd = hwnd;
    /*允许窗口接收拖放消息WM_DROPFILES*/    
    DragAcceptFiles(hwnd, TRUE);
    return TRUE;
}

/*******************************************************************************
*  Main_OnCommand
********************************************************************************/
void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    HMENU  hMenu;
    int iSelection = -1;
    
    hMenu = GetMenu(hwnd);
    iSelection = id;
    if(iSelection>=IDM_JSON 
    && iSelection<=IDM_XML)
    {
        CheckMenuItem(hMenu, IDM_JSON, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_XML, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_CSTRUCT, MF_UNCHECKED);
        CheckMenuItem(hMenu, iSelection, MF_CHECKED);
    }
    if(iSelection>=IDM_LOGIN
    && iSelection<=IDM_RECHARGE)
    {
        CheckMenuItem(hMenu, IDM_LOGIN, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_REDEEM, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_BALANCE, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_VOID, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_REFUND, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_SETTLE, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_ACTIVE, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_ACTIVE_VOID, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_INQUIRE, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_REPRINT, MF_UNCHECKED);
        CheckMenuItem(hMenu, IDM_RECHARGE, MF_UNCHECKED);            
        CheckMenuItem(hMenu, iSelection, MF_CHECKED);
    }
    
    switch(id)
    {        
    case IDM_DLL:
    case IDC_BT_OPEN:
        cul_open_file_dlg(hwnd);
        break;

    case IDM_QUIT:
        if(IDYES == MessageBox(hwnd,TEXT("是否退出？"),TEXT("提示"),MB_YESNO))
        {
            EndDialog(hwnd, id);
        }
        break;
        
    case IDC_BT_SEND:
        cul_req_send();
        break;
        
    case IDM_JSON:
        interface_mode = JSON_MODE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_XML:
        interface_mode = XML_MODE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_CSTRUCT:
        interface_mode = CSTRUCT_MODE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_LOGIN:
        tran_type = CUL_LOGIN;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_SETTLE:
        tran_type = CUL_SETTLE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_REPRINT:
        tran_type = CUL_REPRINT;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_REDEEM:
        tran_type = CUL_REDEEM;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_VOID:
        tran_type = CUL_VOID;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_REFUND:
        tran_type = CUL_REFUND;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_BALANCE:
        tran_type = CUL_BALANCE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_INQUIRE:
        tran_type = CUL_INQUIRE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_ACTIVE:
        tran_type = CUL_ACTIVE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_ACTIVE_VOID:
        tran_type = CUL_ACTIVE_VOID;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    case IDM_RECHARGE:
        tran_type = CUL_RECHARGE;
        cul_set_req_text(hwnd,interface_mode,tran_type);
        break;
        
    default:
        break;
    }
}

void Main_OnDropFiles(HWND hwnd, HDROP wParam)
{
    char strFileName[MAX_PATH];
    HDROP hDrop = (HDROP)wParam;  
    UINT nFileNum = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
    if(nFileNum!=1)
    {
        MessageBox(hwnd,TEXT("不支持同时拖动多个文件"),TEXT("出错提示"),MB_OK);
    }
    DragQueryFile(hDrop, 0, strFileName, MAX_PATH);  
    SetWindowText(GetDlgItem(hwnd,IDC_ET_DLL),strFileName);
    DragFinish(hDrop);
    InvalidateRect(hwnd, NULL, TRUE);
}

/*******************************************************************************
*  Main_OnClose
*/
void Main_OnClose(HWND hwnd)
{
    if(IDYES == MessageBox(hwnd,TEXT("是否退出？"),TEXT("提示"),MB_YESNO))
    {
        EndDialog(hwnd, 0);
    }
}
