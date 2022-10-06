
// MineSweeperView.h : interface of the CMineSweeperView class
//

#pragma once


class CMineSweeperView : public CView
{
protected: // create from serialization only
	CMineSweeperView();
	DECLARE_DYNCREATE(CMineSweeperView)

// Attributes
public:
	CMineSweeperDoc* GetDocument() const;

// Operations
public:
	void setDifficulty(double difficulty);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMineSweeperView();
	void ResizeWindow();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLevelLevel1();
	afx_msg void OnUpdateLevelLevel1(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel2();
	afx_msg void OnUpdateLevelLevel2(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel3();
	afx_msg void OnUpdateLevelLevel3(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel4();
	afx_msg void OnUpdateLevelLevel4(CCmdUI *pCmdUI);
	afx_msg void OnLevelLevel5();
	afx_msg void OnUpdateLevelLevel5(CCmdUI *pCmdUI);
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in MineSweeperView.cpp
inline CMineSweeperDoc* CMineSweeperView::GetDocument() const
   { return reinterpret_cast<CMineSweeperDoc*>(m_pDocument); }
#endif

