
// MineSweeper.h : main header file for the MineSweeper application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMineSweeperApp:
// See MineSweeper.cpp for the implementation of this class
//

class CMineSweeperApp : public CWinApp
{
public:
	CMineSweeperApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMineSweeperApp theApp;
