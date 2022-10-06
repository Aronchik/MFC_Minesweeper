#include "StdAfx.h"
#include "MineSweeperBoard.h"

CMineSweeperBoard::CMineSweeperBoard(void)
	: m_arrBoard(NULL),
	m_nColumns(15), m_nRows(15),
	m_nHeight(35), m_nWidth(35),
	m_Score(0), m_difficulty(1.01)
{
	m_arrColors[0] = RGB(220, 220, 220);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(123, 252, 0);
}

CMineSweeperBoard::CMineSweeperBoard(const CMineSweeperBoard& board)
{
	//  Copy all of the regular data members
	m_nColumns = board.m_nColumns;
	m_nRows = board.m_nRows;
	m_nHeight = board.m_nHeight;
	m_nWidth = board.m_nWidth;
	m_Score = board.m_Score;
	m_difficulty = board.m_difficulty;
	//	Copy over the colors for the board
	for (int i = 0; i < 3; i++)
		m_arrColors[i] = board.m_arrColors[i];
	m_arrBoard = NULL;

	//  Create a new game board of the same size
	CreateBoard();
	//  Copy the colors of the game board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = board.m_arrBoard[row][col];
	//	Copy over the mine locations for the board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrMineLocations[row][col] = board.m_arrMineLocations[row][col];
}

CMineSweeperBoard::~CMineSweeperBoard(void)
{
	//  Simply delete the board
	DeleteBoard();
}

void CMineSweeperBoard::SetupBoard(void)
{
	//	Seeding rand with time
	srand(time(NULL));

	//	Reset Score
	m_Score = 0;

	//  Create the board if needed
	if (m_arrBoard == NULL)
		CreateBoard();
	//  Fill the board with the background color
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;;
	//  Randomly setup Mines
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			m_arrMineLocations[row][col] = rand() >(RAND_MAX / m_difficulty);;
}

COLORREF CMineSweeperBoard::GetBoardSpace(int row, int col)
{
	//  Check the bounds of the array
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return m_arrColors[0];
	return m_arrColors[m_arrBoard[row][col]];
}

void CMineSweeperBoard::DeleteBoard(void)
{
	//  Don't delete a NULL board
	if (m_arrBoard != NULL)
	{
		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrBoard[row] != NULL)
			{
				//  Delete each row first
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}

		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrMineLocations[row] != NULL)
			{
				//  Delete each row first
				delete[] m_arrMineLocations[row];
				m_arrMineLocations[row] = NULL;
			}
		}
		//  Finally delete the array of rows
		delete[] m_arrBoard;
		delete[] m_arrMineLocations;
		m_arrBoard = NULL;
		m_arrMineLocations = NULL;
	}
}

void CMineSweeperBoard::CreateBoard(void)
{
	//  If there is already a board, delete it	
	if (m_arrBoard != NULL)
		DeleteBoard();
	//  Create the array of rows
	m_arrBoard = new int*[m_nRows];
	m_arrMineLocations = new int*[m_nRows];
	//  Create each row
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];
		//  Set each square to be empty
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}

	for (int row = 0; row < m_nRows; row++)
	{
		m_arrMineLocations[row] = new int[m_nColumns];
		//  No mines yet
		for (int col = 0; col < m_nColumns; col++)
			m_arrMineLocations[row][col] = 0;
	}
}

void CMineSweeperBoard::displayMineLocations(void)
{
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			if (m_arrBoard[row][col] != 2)
				m_arrBoard[row][col] = m_arrMineLocations[row][col];;
}

bool CMineSweeperBoard::IsGameOver(void) const
{
	bool isGameOver = false;
	bool validMove = false;
	//  Go column by column, left to right
	for (int col = 0; col < m_nColumns; col++)
	{
		//  Row by row, bottom to top
		for (int row = 0; row < m_nRows; row++)
		{
			int viewColor = m_arrBoard[row][col];
			int matrixColor = m_arrMineLocations[row][col];

			if (viewColor == 1)
				isGameOver = true;
			else if (viewColor == 0 && matrixColor == 0)
				validMove = true;
		}
	}
	//  Check two conditions: 
	//	1) If a mine was clicked 
	//	2) If there are any valid moves left
	return isGameOver || !validMove;
}

/* Save and load the game*/
void CMineSweeperBoard::saveGame(CArchive& ar)
{
	//  Copy all of the regular data members
	ar << m_nColumns;
	ar << m_nRows;
	ar << m_nHeight;
	ar << m_nWidth;
	ar << m_Score;
	ar << m_difficulty;
	//	Copy over the colors for the board
	for (int i = 0; i < 3; i++)
		ar << m_arrColors[i];

	//  Copy the colors of the game board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			ar << m_arrBoard[row][col];
	//	Copy over the mine locations for the board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			ar << m_arrMineLocations[row][col];
}


void CMineSweeperBoard::loadGame(CArchive& ar)
{
	//  First delete the board
	DeleteBoard();
	//  Load all of the regular data members
	ar >> m_nColumns;
	ar >> m_nRows;
	ar >> m_nHeight;
	ar >> m_nWidth;
	ar >> m_Score;
	ar >> m_difficulty;
	//	Copy over the colors for the board
	for (int i = 0; i < 3; i++)
		ar >> m_arrColors[i];

	SetWidth(m_nWidth);
	SetHeight(m_nHeight);
	//  Update the board
	SetupBoard();

	//  Load the colors of the game board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			ar >> m_arrBoard[row][col];
	//	Load the mine locations for the board
	for (int row = 0; row < m_nRows; row++)
		for (int col = 0; col < m_nColumns; col++)
			ar >> m_arrMineLocations[row][col];
}