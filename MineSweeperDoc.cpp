// MineSweeperDoc.cpp : implementation of the CMineSweeperDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MineSweeper.h"
#endif

#include "MineSweeperDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMineSweeperDoc

IMPLEMENT_DYNCREATE(CMineSweeperDoc, CDocument)

BEGIN_MESSAGE_MAP(CMineSweeperDoc, CDocument)
END_MESSAGE_MAP()


// CMineSweeperDoc construction/destruction

CMineSweeperDoc::CMineSweeperDoc()
{
	// TODO: add one-time construction code here
	//  There should always be a game board
	m_board = new CMineSweeperBoard();
}

CMineSweeperDoc::~CMineSweeperDoc()
{
	//  Delete the current game board
	delete m_board;
	//  Delete everything from the undo stack
	ClearUndo();
	//  Delete everything from the redo stack
	ClearRedo();
}

BOOL CMineSweeperDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//  Set (or reset) the game board
	m_board->SetupBoard();
	//  Clear the undo/redo stacks
	ClearUndo();
	ClearRedo();

	return TRUE;
}

void CMineSweeperDoc::UndoLast()
{
	//  First make sure that there is a move to undo
	if (m_undo.empty())
		return;
	//  Take the current board and put it on the redo
	m_redo.push(m_board);
	//  Take the top undo and make it the current
	m_board = m_undo.top();
	m_undo.pop();
}

bool CMineSweeperDoc::CanUndo()
{
	//  Can undo if the undo stack isn't empty
	return !m_undo.empty();
}

void CMineSweeperDoc::RedoLast()
{
	//  First make sure that there is a move to redo
	if (m_redo.empty())
		return;
	//  Take the current board and put it on the undo
	m_undo.push(m_board);
	//  Take the top redo and make it the current
	m_board = m_redo.top();
	m_redo.pop();
}

bool CMineSweeperDoc::CanRedo()
{
	//  Can redo if the redo stack isn't empty
	return !m_redo.empty();
}

void CMineSweeperDoc::ClearUndo()
{
	//  Delete everything from the undo stack
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CMineSweeperDoc::ClearRedo()
{
	//  Delete everything from the redo stack
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}




// CMineSweeperDoc serialization

void CMineSweeperDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		m_board->saveGame(ar);
	}
	else
	{
		m_board->loadGame(ar);
	}

	if (!ar.IsStoring())
		UpdateAllViews(NULL);
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMineSweeperDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMineSweeperDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMineSweeperDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMineSweeperDoc diagnostics

#ifdef _DEBUG
void CMineSweeperDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMineSweeperDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMineSweeperDoc commands
