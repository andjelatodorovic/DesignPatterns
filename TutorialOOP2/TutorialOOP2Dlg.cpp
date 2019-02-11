
// TutorialOOP2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TutorialOOP2.h"
#include "TutorialOOP2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTutorialOOP2Dlg dialog



CTutorialOOP2Dlg::CTutorialOOP2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TUTORIALOOP2_DIALOG, pParent)
	, m_editContent(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTutorialOOP2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONTENT, m_editContent);
	DDX_Control(pDX, IDC_SLIDER1, m_slideCtrl);
	DDX_Control(pDX, IDC_TREE1, m_treeCtrl);
}

BEGIN_MESSAGE_MAP(CTutorialOOP2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NUM6, &CTutorialOOP2Dlg::OnBnClickedButtonNum6)
	ON_BN_CLICKED(IDC_BUTTON_NUM1, &CTutorialOOP2Dlg::OnBnClickedButtonNum1)
	ON_BN_CLICKED(IDC_BUTTON_NUM2, &CTutorialOOP2Dlg::OnBnClickedButtonNum2)
	ON_BN_CLICKED(IDC_BUTTON_NUM3, &CTutorialOOP2Dlg::OnBnClickedButtonNum3)
	ON_BN_CLICKED(IDC_BUTTON_NUM4, &CTutorialOOP2Dlg::OnBnClickedButtonNum4)
	ON_BN_CLICKED(IDC_BUTTON_NUM5, &CTutorialOOP2Dlg::OnBnClickedButtonNum5)
	ON_BN_CLICKED(IDC_BUTTON_NUM7, &CTutorialOOP2Dlg::OnBnClickedButtonNum7)
	ON_BN_CLICKED(IDC_BUTTON_NUM8, &CTutorialOOP2Dlg::OnBnClickedButtonNum8)
	ON_BN_CLICKED(IDC_BUTTON_NUM9, &CTutorialOOP2Dlg::OnBnClickedButtonNum9)
	ON_BN_CLICKED(IDC_BUTTON_NUM0, &CTutorialOOP2Dlg::OnBnClickedButtonNum0)
	ON_BN_CLICKED(IDC_BUTTON_NUM_PLUS, &CTutorialOOP2Dlg::OnBnClickedButtonNumPlus)
	ON_BN_CLICKED(IDC_BUTTON_NUM_MINUS, &CTutorialOOP2Dlg::OnBnClickedButtonNumMinus)
	ON_BN_CLICKED(IDC_BUTTON_NUM_MUL, &CTutorialOOP2Dlg::OnBnClickedButtonNumMul)
	ON_BN_CLICKED(IDC_BUTTON_NUM_DIV, &CTutorialOOP2Dlg::OnBnClickedButtonNumDiv)
	ON_BN_CLICKED(IDC_BUTTON_NUM_CALC, &CTutorialOOP2Dlg::OnBnClickedButtonNumCalc)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CTutorialOOP2Dlg message handlers

BOOL CTutorialOOP2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	SetTimer(NULL, 100, NULL);

	m_slideCtrl.SetRangeMax(100);
	m_slideCtrl.SetPos(50);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTutorialOOP2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTutorialOOP2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTutorialOOP2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTutorialOOP2Dlg::OnBnClickedButtonNum6()
{
	calculator.m_content = calculator.m_content + _T("6");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum1()
{
	calculator.m_content = calculator.m_content + _T("1");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum2()
{
	calculator.m_content = calculator.m_content + _T("2");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum3()
{
	calculator.m_content = calculator.m_content + _T("3");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum4()
{
	calculator.m_content = calculator.m_content + _T("4");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum5()
{
	calculator.m_content = calculator.m_content + _T("5");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum7()
{
	calculator.m_content = calculator.m_content + _T("7");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum8()
{
	calculator.m_content = calculator.m_content + _T("8");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum9()
{
	calculator.m_content = calculator.m_content + _T("9");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNum0()
{
	calculator.m_content = calculator.m_content + _T("0");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNumPlus()
{
	calculator.m_content = calculator.m_content + _T("+");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNumMinus()
{
	calculator.m_content = calculator.m_content + _T("-");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNumMul()
{
	calculator.m_content = calculator.m_content + _T("*");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNumDiv()
{
	calculator.m_content = calculator.m_content + _T("/");
	m_editContent.Format(calculator.m_content);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnBnClickedButtonNumCalc()
{
	calculator.Interpret();
	m_editContent.Format(calculator.m_result);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}


void CTutorialOOP2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_editContent.Format(_T("Mouse on point (%d, %d)"), point.x, point.y);
	UpdateData(FALSE);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CTutorialOOP2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	static int x = 0;
	x++;
	m_editContent.Format(_T("%d"), x);
	UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


void CTutorialOOP2Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar == (CScrollBar*)&m_slideCtrl) {
		m_editContent.Format(_T("Slide at %d"), m_slideCtrl.GetPos());
		UpdateData(FALSE);
	}
	else {
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}
