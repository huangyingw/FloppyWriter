// FloppyWriterDlg.h : header file
//

#if !defined(AFX_FLOPPYWRITERDLG_H__CD316FAD_10A0_4AC3_8509_886669F0320B__INCLUDED_)
#define AFX_FLOPPYWRITERDLG_H__CD316FAD_10A0_4AC3_8509_886669F0320B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFloppyWriterDlg dialog

class CFloppyWriterDlg : public CDialog
{
// Construction
public:
	CFloppyWriterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFloppyWriterDlg)
	enum { IDD = IDD_FLOPPYWRITER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloppyWriterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFloppyWriterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnWriteFileToFloppy();
	afx_msg void OnBtnWriteFileToImg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOPPYWRITERDLG_H__CD316FAD_10A0_4AC3_8509_886669F0320B__INCLUDED_)
