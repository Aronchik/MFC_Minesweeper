
// MineSweeperView.cpp : implementation of the CMineSweeperView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MineSweeper.h"
#endif

#include "MineSweeperDoc.h"
#include "MineSweeperView.h"
#include "OptionsDialog.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMineSweeperView

IMPLEMENT_DYNCREATE(CMineSweeperView, CView)

BEGIN_MESSAGE_MAP(CMineSweeperView, CView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_LEVEL_LEVEL1, &CMineSweeperView::OnLevelLevel1)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL1, &CMineSweeperView::OnUpdateLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CMineSweeperView::OnLevelLevel2)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL2, &CMineSweeperView::OnUpdateLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CMineSweeperView::OnLevelLevel3)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL3, &CMineSweeperView::OnUpdateLevelLevel3)
	ON_COMMAND(ID_LEVEL_LEVEL4, &CMineSweeperView::OnLevelLevel4)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL4, &CMineSweeperView::OnUpdateLevelLevel4)
	ON_COMMAND(ID_LEVEL_LEVEL5, &CMineSweeperView::OnLevelLevel5)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_LEVEL5, &CMineSweeperView::OnUpdateLevelLevel5)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CMineSweeperView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CMineSweeperView::OnSetupBlocksize)
	ON_COMMAND(ID_EDIT_REDO, &CMineSweeperView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMineSweeperView::OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_UNDO, &CMineSweeperView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMineSweeperView::OnUpdateEditUndo)
END_MESSAGE_MAP()

// CMineSweeperView construction/destruction

CMineSweeperView::CMineSweeperView()
{
	// TODO: add construction code here

}

CMineSweeperView::~CMineSweeperView()
{
}

BOOL CMineSweeperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMineSweeperView drawing

void CMineSweeperView::OnDraw(CDC* pDC)
{
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	//  Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	//  Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	//  Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Draw the background first
	pDC->FillSolidRect(&rcClient, clr);
	//  Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			//  Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			//  Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			//  Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}


// CMineSweeperView diagnostics

#ifdef _DEBUG
void CMineSweeperView::AssertValid() const
{
	CView::AssertValid();
}

void CMineSweeperView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMineSweeperDoc* CMineSweeperView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMineSweeperDoc)));
	return (CMineSweeperDoc*)m_pDocument;
}
#endif //_DEBUG


// CMineSweeperView message handlers


void CMineSweeperView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//  Resize the window
	ResizeWindow();

	// TODO: Add your specialized code here and/or call the base class
}

void CMineSweeperView::ResizeWindow()
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CMineSweeperView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Delete the blocks from the document
	int clickedMine = pDoc->checkIfMine(row, col);
	//  Check if there were any blocks deleted
	bool isGameOver = pDoc->IsGameOver();
	//  Save the current board in the undo stack if game is not over
	if (!isGameOver)
	{
		pDoc->pushToStack();
		//	Clear Redo stack
		pDoc->ClearRedo();
	}
	if (!isGameOver)
	{
		if (clickedMine)
		{
			//  Set colors and update screen with info
			pDoc->setSquareColor(row, col, 1);
			pDoc->diplayMineLocations();
			Invalidate();
			UpdateWindow();

			int score = pDoc->getScore();
			CString message;
			message.Format(_T("Your score: %d"), score);

			//  Display the results to the user
			PlaySound(_T("Sounds/Explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
		else
		{

			if (pDoc->getColor(row, col) != 2)
			{
				pDoc->setSquareColor(row, col, 2);
				pDoc->increaseScore();
				Invalidate();
				UpdateWindow();
			}

			if (pDoc->IsGameOver())
			{
				int score = pDoc->getScore();
				CString message;
				message.Format(_T("Your score: %d"), score);

				//  Display the results to the user
				PlaySound(_T("Sounds/Applause.wav"), NULL, SND_FILENAME | SND_ASYNC);
				MessageBox(message, _T("You've Won!"), MB_OK | MB_ICONINFORMATION);
			}
		}
	}

	//  Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}

void CMineSweeperView::setDifficulty(double difficulty)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->difficultySetter(difficulty);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CMineSweeperView::OnLevelLevel1()
{
	setDifficulty(1.01);
}


void CMineSweeperView::OnUpdateLevelLevel1(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->difficultyGetter() == 1.01);
}


void CMineSweeperView::OnLevelLevel2()
{
	setDifficulty(1.1);
}


void CMineSweeperView::OnUpdateLevelLevel2(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->difficultyGetter() == 1.1);
}


void CMineSweeperView::OnLevelLevel3()
{
	setDifficulty(1.2);
}


void CMineSweeperView::OnUpdateLevelLevel3(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->difficultyGetter() == 1.2);
}


void CMineSweeperView::OnLevelLevel4()
{
	setDifficulty(1.5);
}


void CMineSweeperView::OnUpdateLevelLevel4(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->difficultyGetter() == 1.5);
}


void CMineSweeperView::OnLevelLevel5()
{
	setDifficulty(1.8);
}


void CMineSweeperView::OnUpdateLevelLevel5(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->difficultyGetter() == 1.8);
}



void CMineSweeperView::OnSetupBlockcount()
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(true, this);
	//  Set the row and column values
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CMineSweeperView::OnSetupBlocksize()
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(false, this);
	//  Set the width and height values
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}


void CMineSweeperView::OnEditRedo()
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call redo on the document
	pDoc->RedoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}


void CMineSweeperView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanRedo());
}


void CMineSweeperView::OnEditUndo()
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Call undo on the document
	pDoc->UndoLast();
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}


void CMineSweeperView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CMineSweeperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Enable option if it is available
	pCmdUI->Enable(pDoc->CanUndo());
}
