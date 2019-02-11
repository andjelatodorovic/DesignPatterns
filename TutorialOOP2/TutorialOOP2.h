
// TutorialOOP2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include <string>

using namespace std;

// CTutorialOOP2App:
// See TutorialOOP2.cpp for the implementation of this class
//

class CTutorialOOP2App : public CWinApp
{
public:
	CTutorialOOP2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTutorialOOP2App theApp;

class CCalculator {
public:
	CCalculator() : m_content(_T("")) {}
	void Interpret() {
		m_result = _T("0");
	}
	CString	m_content;
	CString	m_result;
};

extern CCalculator calculator;