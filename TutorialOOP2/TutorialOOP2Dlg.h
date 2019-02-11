
// TutorialOOP2Dlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CTutorialOOP2Dlg dialog
class CTutorialOOP2Dlg : public CDialogEx
{
// Construction
public:
	CTutorialOOP2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TUTORIALOOP2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNum6();
	afx_msg void OnBnClickedButtonNum1();
protected:
	CString m_editContent;
public:
	afx_msg void OnBnClickedButtonNum2();
	afx_msg void OnBnClickedButtonNum3();
	afx_msg void OnBnClickedButtonNum4();
	afx_msg void OnBnClickedButtonNum5();
	afx_msg void OnBnClickedButtonNum7();
	afx_msg void OnBnClickedButtonNum8();
	afx_msg void OnBnClickedButtonNum9();
	afx_msg void OnBnClickedButtonNum0();
	afx_msg void OnBnClickedButtonNumPlus();
	afx_msg void OnBnClickedButtonNumMinus();
	afx_msg void OnBnClickedButtonNumMul();
	afx_msg void OnBnClickedButtonNumDiv();
	afx_msg void OnBnClickedButtonNumCalc();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
protected:
	CSliderCtrl m_slideCtrl;
public:
	CTreeCtrl m_treeCtrl;
};
