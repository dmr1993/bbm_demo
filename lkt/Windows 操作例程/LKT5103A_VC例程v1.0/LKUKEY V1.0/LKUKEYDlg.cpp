/*********************************************************
    文件名： LKUKEY.cpp                 作者：LKT 技术部 王宏瑾      升级人： 技术部 张亮                           
    编写日期：   2014.07.03             版本：V1.1 （内部）          升级日期： 2015.09.10
    功能：   实现与加密芯片通讯的功能。对应新版本动态库，4个接口（复位、ADPU、disconnect）都带有返回值。因此软件处理增加了返回值判断
    函数列表：   
    1. OnUkeyConnect
    2. OnUkeyDisconnect
	3. OnUkeyReset
	4. OnSendAPDU
    修改记录：         
          <作者>   <时间>   <版本>   <修改目的>
***********************************************************/

#include "stdafx.h"
#include "LKUKEY.h"
#include "LKUKEYDlg.h"
#include "FucBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLKUKEYDlg dialog
typedef int  (__stdcall *pConnect)(int);  
typedef int (__stdcall *pAtr)(int*, unsigned char*); 
typedef int (__stdcall *pDisConnect)(void); 
typedef int (__stdcall *pSendAPDU)(int, unsigned char*, int*, unsigned char*);

pConnect ConnectUkey;
pDisConnect DisConnectUkey;
pAtr GetUkeyAtr; 
pSendAPDU SendAPDU;

HMODULE g_hDll; //动态库句柄

CLKUKEYDlg::CLKUKEYDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLKUKEYDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLKUKEYDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLKUKEYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLKUKEYDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLKUKEYDlg, CDialog)
	//{{AFX_MSG_MAP(CLKUKEYDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_UKEYCONNECT, OnUkeyConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, OnUkeyDisconnect)
	ON_BN_CLICKED(IDC_UKEYRESET, OnUkeyReset)
	ON_BN_CLICKED(IDC_SENDAPDU, OnSendAPDU)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLKUKEYDlg message handlers

BOOL CLKUKEYDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	g_hDll = ::LoadLibrary(".\\LKT5103A.dll");  //加载动态库
	if (g_hDll == NULL)
	{ 
		MessageBox("找不到LKT5103A.dll, 加载动态链接库失败", "Warning", MB_OK | MB_ICONWARNING);
		exit(0);
	} 
	else 
	{
		ConnectUkey = (pConnect)::GetProcAddress(g_hDll, "EK_Open"); 
		if(ConnectUkey == NULL)
		{
			MessageBox("函数调用失败", "Warning", MB_OK | MB_ICONWARNING); 
			exit(0);
		}
		
		GetUkeyAtr = (pAtr)::GetProcAddress(g_hDll, "EK_Reset"); 
		if(GetUkeyAtr == NULL)
		{
			MessageBox("函数调用失败", "Warning", MB_OK | MB_ICONWARNING); 
			exit(0);
		}
		
        DisConnectUkey = (pDisConnect)::GetProcAddress(g_hDll, "EK_Close"); 
		if(DisConnectUkey == NULL)
		{
			MessageBox("函数调用失败", "Warning", MB_OK | MB_ICONWARNING);
			exit(0);
		}
		
		SendAPDU = (pSendAPDU)::GetProcAddress(g_hDll, "EK_Exchange_APDU"); 
		if(SendAPDU == NULL)
		{
			MessageBox("函数调用失败", "Warning", MB_OK | MB_ICONWARNING);
			exit(0);
		}
    }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLKUKEYDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CLKUKEYDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

/*************************************************
    函数名称：   Bprintf     
    功能：       打印BYTE类型信息（十六进制）      
    调用函数：   NULL  
    被调用函数：    
    输入参数：   strIn, dataIn, lenIn                
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::Bprintf(CHAR* strIn, BYTE* dataIn, INT* lenIn)
{
	INT i;
	CEdit* pDisplay = (CEdit*)GetDlgItem(IDC_MEMOINFORMATION);
	CString strText = _T(strIn); 
	
	for (i = 0; i < *lenIn; i++)
	{	
		CString  strTemp = _T("");
		strTemp.Format(_T("%02X "), dataIn[i]);
		strText += strTemp;
	}
	pDisplay->SetSel(-1, -1);
	pDisplay->ReplaceSel(strText + "\r\n");
	UpdateData(true);	
}

/*************************************************
    函数名称：   Bprintf     
    功能：       打印整形数据信息（十进制）      
    调用函数：   NULL  
    被调用函数：    
    输入参数：   strIn, dataIn, lenIn                
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::Iprintf(CHAR* strIn, INT* dataIn, INT* lenIn)
{
	INT i;
	CEdit* pDisplay = (CEdit*)GetDlgItem(IDC_MEMOINFORMATION);
	CString strText = _T(strIn); 
	
	for (i = 0; i < *lenIn; i++)
	{	
		CString  strTemp = _T("");
		strTemp.Format(_T("%d "), dataIn[i]);
		strText += strTemp;
	}
	pDisplay->SetSel(-1, -1);
	pDisplay->ReplaceSel(strText + "\r\n");
	UpdateData(true);	
}

/*************************************************
    函数名称：   Sprintf     
    功能：       打印信息     
    调用函数：   NULL  
    被调用函数：    
    输入参数：   strIn               
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::Sprintf(CHAR* strIn)
{
	CEdit* pDisplay = (CEdit*)GetDlgItem(IDC_MEMOINFORMATION);
	CString strText = _T(strIn); 
	pDisplay->SetSel(-1, -1);
	pDisplay->ReplaceSel(strText + "\r\n");
	UpdateData(true);
}

/*************************************************
    函数名称：   OnUkeyConnect    
    功能：       连接uKey     
    调用函数：   ConnectUkey  
    被调用函数：    
    输入参数：   NULL               
    输出参数：   NULL    
    返回值：     NULL
    其他：       ConnectUkey(1)中的参数1为函数保留功能, 
				 没有意义       
*************************************************/
void CLKUKEYDlg::OnUkeyConnect() 
{
	// TODO: Add your control notification handler code here
	UINT res = ConnectUkey(1);
	if (res == UKEY_RIGHT)
	{
		CLKUKEYDlg::Sprintf("连接成功");
	}
	else if (res == UKEY_WRONG)
	{
		CLKUKEYDlg::Sprintf("连接失败");
	}	
}

/*************************************************
    函数名称：   OnUkeyDisconnect    
    功能：       断开uKey     
    调用函数：   DisConnectUkey 
    被调用函数：    
    输入参数：   NULL               
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::OnUkeyDisconnect() 
{
	// TODO: Add your control notification handler code here
	INT res, len;
    res = DisConnectUkey();
	if(0 != res){
		len = 1;
		CLKUKEYDlg::Sprintf("已处于断开连接状态");
	}
	else
	CLKUKEYDlg::Sprintf("连接已断开");	
}

/*************************************************
    函数名称：   OnUkeyReset    
    功能：       复位uKey     
    调用函数：   OnUkeyReset 
    被调用函数：    
    输入参数：   NULL               
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::OnUkeyReset() 
{
	// TODO: Add your control notification handler code here
	INT  atrLen,len,res;
	BYTE ukeyAtr[30];
	
	res = GetUkeyAtr(&atrLen, ukeyAtr);
	if(0 != res){
		len = 1;
		CLKUKEYDlg::Iprintf("Reset failed, the res is: ", &res, &len);
	}
	else
	CLKUKEYDlg::Bprintf("ATR <- : ", ukeyAtr, &atrLen);		
}

/*************************************************
    函数名称：   OnSendAPDU    
    功能：       uKey通讯     
    调用函数：   SendAPDU 
    被调用函数： 
    输入参数：   NULL               
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::OnSendAPDU() 
{
	// TODO: Add your control notification handler code here
	INT  lenSnd, lenRcv, res, len;
	BYTE cmdAPDU[0x200], outBuf[0x200];
	CHAR tmpBuf[4096];
	
    CWnd* pWnd = GetDlgItem(IDC_COMMAND); 
	pWnd->GetWindowText(tmpBuf, 4096);    
	lenSnd = Hex2Byte(tmpBuf, cmdAPDU);
	
    res = SendAPDU(lenSnd, cmdAPDU, &lenRcv, outBuf);
	if(0 != res){
		len = 1;
		CLKUKEYDlg::Iprintf("SendApdu failed,the res is: ", &res, &len);
	}
	else
	CLKUKEYDlg::Bprintf("SendApdu -> : ", outBuf, &lenRcv);		
}

/*************************************************
    函数名称：   OnDestroy    
    功能：       窗体关闭处理函数     
    调用函数：   NULL 
    被调用函数： NULL
    输入参数：   NULL               
    输出参数：   NULL    
    返回值：     NULL
    其他：           
*************************************************/
void CLKUKEYDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	FreeLibrary(g_hDll); //释放句柄
}
