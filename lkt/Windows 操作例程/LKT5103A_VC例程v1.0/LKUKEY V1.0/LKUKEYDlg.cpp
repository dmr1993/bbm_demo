/*********************************************************
    �ļ����� LKUKEY.cpp                 ���ߣ�LKT ������ �����      �����ˣ� ������ ����                           
    ��д���ڣ�   2014.07.03             �汾��V1.1 ���ڲ���          �������ڣ� 2015.09.10
    ���ܣ�   ʵ�������оƬͨѶ�Ĺ��ܡ���Ӧ�°汾��̬�⣬4���ӿڣ���λ��ADPU��disconnect�������з���ֵ�����������������˷���ֵ�ж�
    �����б�   
    1. OnUkeyConnect
    2. OnUkeyDisconnect
	3. OnUkeyReset
	4. OnSendAPDU
    �޸ļ�¼��         
          <����>   <ʱ��>   <�汾>   <�޸�Ŀ��>
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

HMODULE g_hDll; //��̬����

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
	g_hDll = ::LoadLibrary(".\\LKT5103A.dll");  //���ض�̬��
	if (g_hDll == NULL)
	{ 
		MessageBox("�Ҳ���LKT5103A.dll, ���ض�̬���ӿ�ʧ��", "Warning", MB_OK | MB_ICONWARNING);
		exit(0);
	} 
	else 
	{
		ConnectUkey = (pConnect)::GetProcAddress(g_hDll, "EK_Open"); 
		if(ConnectUkey == NULL)
		{
			MessageBox("��������ʧ��", "Warning", MB_OK | MB_ICONWARNING); 
			exit(0);
		}
		
		GetUkeyAtr = (pAtr)::GetProcAddress(g_hDll, "EK_Reset"); 
		if(GetUkeyAtr == NULL)
		{
			MessageBox("��������ʧ��", "Warning", MB_OK | MB_ICONWARNING); 
			exit(0);
		}
		
        DisConnectUkey = (pDisConnect)::GetProcAddress(g_hDll, "EK_Close"); 
		if(DisConnectUkey == NULL)
		{
			MessageBox("��������ʧ��", "Warning", MB_OK | MB_ICONWARNING);
			exit(0);
		}
		
		SendAPDU = (pSendAPDU)::GetProcAddress(g_hDll, "EK_Exchange_APDU"); 
		if(SendAPDU == NULL)
		{
			MessageBox("��������ʧ��", "Warning", MB_OK | MB_ICONWARNING);
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
    �������ƣ�   Bprintf     
    ���ܣ�       ��ӡBYTE������Ϣ��ʮ�����ƣ�      
    ���ú�����   NULL  
    �����ú�����    
    ���������   strIn, dataIn, lenIn                
    ���������   NULL    
    ����ֵ��     NULL
    ������           
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
    �������ƣ�   Bprintf     
    ���ܣ�       ��ӡ����������Ϣ��ʮ���ƣ�      
    ���ú�����   NULL  
    �����ú�����    
    ���������   strIn, dataIn, lenIn                
    ���������   NULL    
    ����ֵ��     NULL
    ������           
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
    �������ƣ�   Sprintf     
    ���ܣ�       ��ӡ��Ϣ     
    ���ú�����   NULL  
    �����ú�����    
    ���������   strIn               
    ���������   NULL    
    ����ֵ��     NULL
    ������           
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
    �������ƣ�   OnUkeyConnect    
    ���ܣ�       ����uKey     
    ���ú�����   ConnectUkey  
    �����ú�����    
    ���������   NULL               
    ���������   NULL    
    ����ֵ��     NULL
    ������       ConnectUkey(1)�еĲ���1Ϊ������������, 
				 û������       
*************************************************/
void CLKUKEYDlg::OnUkeyConnect() 
{
	// TODO: Add your control notification handler code here
	UINT res = ConnectUkey(1);
	if (res == UKEY_RIGHT)
	{
		CLKUKEYDlg::Sprintf("���ӳɹ�");
	}
	else if (res == UKEY_WRONG)
	{
		CLKUKEYDlg::Sprintf("����ʧ��");
	}	
}

/*************************************************
    �������ƣ�   OnUkeyDisconnect    
    ���ܣ�       �Ͽ�uKey     
    ���ú�����   DisConnectUkey 
    �����ú�����    
    ���������   NULL               
    ���������   NULL    
    ����ֵ��     NULL
    ������           
*************************************************/
void CLKUKEYDlg::OnUkeyDisconnect() 
{
	// TODO: Add your control notification handler code here
	INT res, len;
    res = DisConnectUkey();
	if(0 != res){
		len = 1;
		CLKUKEYDlg::Sprintf("�Ѵ��ڶϿ�����״̬");
	}
	else
	CLKUKEYDlg::Sprintf("�����ѶϿ�");	
}

/*************************************************
    �������ƣ�   OnUkeyReset    
    ���ܣ�       ��λuKey     
    ���ú�����   OnUkeyReset 
    �����ú�����    
    ���������   NULL               
    ���������   NULL    
    ����ֵ��     NULL
    ������           
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
    �������ƣ�   OnSendAPDU    
    ���ܣ�       uKeyͨѶ     
    ���ú�����   SendAPDU 
    �����ú����� 
    ���������   NULL               
    ���������   NULL    
    ����ֵ��     NULL
    ������           
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
    �������ƣ�   OnDestroy    
    ���ܣ�       ����رմ�����     
    ���ú�����   NULL 
    �����ú����� NULL
    ���������   NULL               
    ���������   NULL    
    ����ֵ��     NULL
    ������           
*************************************************/
void CLKUKEYDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	FreeLibrary(g_hDll); //�ͷž��
}
