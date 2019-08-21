// LKUKEYDlg.h : header file
//

#if !defined(AFX_LKUKEYDLG_H__4E994C6F_1E2E_4F55_BC34_4B352C2C86F8__INCLUDED_)
#define AFX_LKUKEYDLG_H__4E994C6F_1E2E_4F55_BC34_4B352C2C86F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLKUKEYDlg dialog

class CLKUKEYDlg : public CDialog
{
// Construction
public:
	CLKUKEYDlg(CWnd* pParent = NULL);	// standard constructor
	afx_msg void Bprintf(CHAR* strIn, BYTE* dataIn, INT* lenIn);
	afx_msg void Iprintf(CHAR* strIn, INT* dataIn, INT* lenIn);
	afx_msg void Sprintf(CHAR* strIn);
// Dialog Data
	//{{AFX_DATA(CLKUKEYDlg)
	enum { IDD = IDD_LKUKEY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLKUKEYDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLKUKEYDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnUkeyConnect();
	afx_msg void OnUkeyDisconnect();
	afx_msg void OnUkeyReset();
	afx_msg void OnSendAPDU();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LKUKEYDLG_H__4E994C6F_1E2E_4F55_BC34_4B352C2C86F8__INCLUDED_)
