
// MineSweeperDoc.h : interface of the CMineSweeperDoc class
//


#pragma once
#include "MineSweeperBoard.h"
#include <stack>

class CMineSweeperDoc : public CDocument
{
protected: // create from serialization only
	CMineSweeperDoc();
	DECLARE_DYNCREATE(CMineSweeperDoc)

	// Attributes
public:

	// Operations
public:
	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board->GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board->SetupBoard(); }
	int GetWidth(void) { return m_board->GetWidth(); }
	int GetHeight(void) { return m_board->GetHeight(); }
	int GetColumns(void) { return m_board->GetColumns(); }
	int GetRows(void) { return m_board->GetRows(); }
	void DeleteBoard(void) { m_board->DeleteBoard(); }
	int checkIfMine(int row, int col) { return m_board->checkIfMine(row, col); }
	int getScore(void) { return m_board->getScore(); }
	void increaseScore(void) { m_board->increaseScore(); }
	void setSquareColor(int row, int col, int color) { m_board->setSquareColor(row, col, color); }
	int getColor(int row, int col) { return m_board->getColor(row, col); }
	void diplayMineLocations(void) { m_board->displayMineLocations(); }
	bool IsGameOver(void) { return m_board->IsGameOver(); }
	void difficultySetter(double difficulty) { m_board->difficultySetter(difficulty); m_board->SetupBoard(); }
	double difficultyGetter(void) { return m_board->difficultyGetter(); }
	void SetWidth(int nWidth) { m_board->SetWidth(nWidth); }
	void SetHeight(int nHeight) { m_board->SetHeight(nHeight); }
	void SetColumns(int nColumns) { m_board->SetColumns(nColumns); }
	void SetRows(int nRows) { m_board->SetRows(nRows); }
	void pushToStack() { m_undo.push(new CMineSweeperBoard(*m_board)); }
	/*  Functions to clear undo/redo stacks */
	void ClearUndo();
	void ClearRedo();
	/*  Undo/redo functions */
	void UndoLast();
	bool CanUndo();
	void RedoLast();
	bool CanRedo();
	/* Save and load the game*/
	void saveGame(CArchive& ar) { m_board->saveGame(ar); };
	void loadGame(CArchive& ar) { m_board->loadGame(ar); };

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CMineSweeperDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	/*  Instance of the game board */
	CMineSweeperBoard* m_board;
	/*  Undo stack */
	std::stack<CMineSweeperBoard*> m_undo;
	/*  Redo stack */
	std::stack<CMineSweeperBoard*> m_redo;

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
