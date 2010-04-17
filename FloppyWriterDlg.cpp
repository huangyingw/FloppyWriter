// FloppyWriterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FloppyWriter.h"
#include "FloppyWriterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloppyWriterDlg dialog

CFloppyWriterDlg::CFloppyWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFloppyWriterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloppyWriterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFloppyWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloppyWriterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFloppyWriterDlg, CDialog)
	//{{AFX_MSG_MAP(CFloppyWriterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_WRITE_FILE_TO_FLOPPY, OnBtnWriteFileToFloppy)
	ON_BN_CLICKED(IDC_BTN_WRITE_FILE_TO_IMG, OnBtnWriteFileToImg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloppyWriterDlg message handlers

BOOL CFloppyWriterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFloppyWriterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFloppyWriterDlg::OnPaint() 
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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFloppyWriterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFloppyWriterDlg::OnBtnWriteFileToFloppy() 
{
	unsigned char uchBootData[512];
	
	OPENFILENAME ofn;			// common dialog box structure
	char szFile[MAX_PATH] = "Boot.bin";	// buffer for file name
	HWND hwnd = this->m_hWnd;		// owner window

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize		= sizeof(OPENFILENAME);
	ofn.hwndOwner		= hwnd;
	ofn.lpstrFile		= szFile;
	ofn.nMaxFile		= sizeof(szFile);
	ofn.lpstrFilter		= "Binary files(*.bin)\0*.bin\0All(*.*)\0*.*\0";
	ofn.nFilterIndex	= 1;
	ofn.lpstrFileTitle	= NULL;
	ofn.nMaxFileTitle	= 0;
	ofn.lpstrInitialDir	= NULL;
	ofn.lpstrTitle		= "打开文件";
	ofn.Flags		= OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==FALSE){
		return;
	}

	HANDLE hf = ::CreateFile(szFile,
				GENERIC_READ,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	DWORD dwFileSizeHigh = 0;
	DWORD dwFilesize = ::GetFileSize(hf, &dwFileSizeHigh);
	if (dwFilesize <= 0) {
		::MessageBox(m_hWnd, "文件错误!", "Error", MB_OK);
		return;
	}
	DWORD dwRead = 0;
	if (!ReadFile(hf, uchBootData, dwFilesize, &dwRead, NULL)) {
		int iErr;
		char szError[128];
		iErr = GetLastError();
		::sprintf(szError, "文件读取错误!\n错误代码: %d", iErr);
		::MessageBox(m_hWnd, szError, "Error", MB_OK);
		return;
	}
	::CloseHandle(hf);

	HANDLE hDevice = CreateFile(	"\\\\.\\A:", 
					GENERIC_READ | GENERIC_WRITE,
					FILE_SHARE_READ | FILE_SHARE_WRITE, 
					NULL,
					OPEN_EXISTING,
					0,
					NULL);

	if (hDevice == INVALID_HANDLE_VALUE) 
	{
	   MessageBox ("Failed !");
	   return;
	}
    
   
	// setting the file pointer to the start of the 
	//     sector we want to read . 
	//移动文件指针到需要读取位置
	SetFilePointer(	hDevice, 
			0, 
			NULL, 
			FILE_BEGIN); 

	DWORD dwBytesWritten;	
	if (!::WriteFile(hDevice,
				uchBootData,
				512,
				&dwBytesWritten,
				NULL) )
	{
		int err;
		char error[10];
		err=GetLastError ();
		itoa (err, error, 10);
		MessageBox (error, "Writing sectors ...Failed  ");
		return ;
	}
   
	// setting the file pointer to the start of the 
	//     sector we want to read . 
	//移动文件指针到需要读取位置
	SetFilePointer (hDevice, 
					 0, 
					 NULL, 
					 FILE_BEGIN); 

	void* buffer;
	buffer = new BYTE[512];
	DWORD dwBytesRead;
	// reading sector(s) ...
	//读数据
	if (!ReadFile ( hDevice, 
					 buffer, 
					 512, 
					 &dwBytesRead, 
					 NULL) )
	{
		int err;
		char error[10];
		err=GetLastError ();
		itoa (err, error, 10);
		MessageBox (error, "Reading sectors ...Failed  ");
		return ;
	}

	delete buffer;

	//关闭
	CloseHandle(hDevice);
	
	::MessageBox(this->m_hWnd, "成功！", "Floppy writer", MB_OK);
}

void CFloppyWriterDlg::OnBtnWriteFileToImg() 
{
	// 下面读文件 ------------------------------------------------------------------
	
	unsigned char uchBootData[512];
	
	OPENFILENAME ofn;			// common dialog box structure
	char szFile[MAX_PATH] = "Boot.bin";	// buffer for file name
	char szFileFilterBIN[255]= "Binary files(*.bin)\0*.bin\0All(*.*)\0*.*\0";
	char szFileFilterIMG[255]= "Image files(*.img)\0*.img\0All(*.*)\0*.*\0";
	HWND hwnd = this->m_hWnd;		// owner window
	
	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = szFileFilterBIN;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "打开文件";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// Display the Open dialog box. 
	
	if (GetOpenFileName(&ofn)==FALSE){
		return;
	}
	
	HANDLE hf = ::CreateFile(szFile,
				GENERIC_READ,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL,
				NULL);
	DWORD dwFileSizeHigh = 0;
	DWORD dwFilesize = ::GetFileSize(hf, &dwFileSizeHigh);
	if (dwFilesize <= 0) {
		::MessageBox(m_hWnd, "文件错误!", "Error", MB_OK);
		return;
	}
	DWORD dwRead = 0;
	if (!ReadFile(hf, uchBootData, dwFilesize, &dwRead, NULL)) {
		int iErr;
		char szError[128];
		iErr = GetLastError();
		::sprintf(szError, "文件读取错误!\n错误代码: %d", iErr);
		::MessageBox(m_hWnd, szError, "Error", MB_OK);
		return;
	}
	::CloseHandle(hf);
	
	
	// 下面写文件 ------------------------------------------------------------------
	
	::strcpy(szFile, "Tinix.img");
	ofn.lpstrFilter = szFileFilterIMG;
	
	// Display the Open dialog box. 
	
	if (GetOpenFileName(&ofn)==FALSE){
		return;
	}
	
	
	HANDLE hfImage = ::CreateFile(szFile,
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	::SetFilePointer(hfImage, 0, 0, FILE_BEGIN);
	
	DWORD dwBytesWritten;	
	if (!::WriteFile(hfImage,
		uchBootData,
		512,
		&dwBytesWritten,
		NULL) )
	{
		int err;
		char error[10];
		err=GetLastError ();
		itoa (err, error, 10);
		MessageBox (error, "Writing sectors ...Failed  ");
		return ;
	}
	
	::CloseHandle(hfImage);

	::MessageBox(this->m_hWnd, "成功！", "Floppy writer", MB_OK);
}
