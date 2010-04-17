// FloppyWriter.h : main header file for the FLOPPYWRITER application
//

#if !defined(AFX_FLOPPYWRITER_H__ACA49710_A2D2_49F5_9FC1_8D5E17FF25C4__INCLUDED_)
#define AFX_FLOPPYWRITER_H__ACA49710_A2D2_49F5_9FC1_8D5E17FF25C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFloppyWriterApp:
// See FloppyWriter.cpp for the implementation of this class
//

class CFloppyWriterApp : public CWinApp
{
public:
	CFloppyWriterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloppyWriterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFloppyWriterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPPYWRITER_H__ACA49710_A2D2_49F5_9FC1_8D5E17FF25C4__INCLUDED_)
