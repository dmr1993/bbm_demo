// LKUKEY.h : main header file for the LKUKEY application
//

#if !defined(AFX_LKUKEY_H__1460C110_71A7_448D_B6BC_E616E920DA22__INCLUDED_)
#define AFX_LKUKEY_H__1460C110_71A7_448D_B6BC_E616E920DA22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLKUKEYApp:
// See LKUKEY.cpp for the implementation of this class
//

class CLKUKEYApp : public CWinApp
{
public:
	CLKUKEYApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLKUKEYApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLKUKEYApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LKUKEY_H__1460C110_71A7_448D_B6BC_E616E920DA22__INCLUDED_)
