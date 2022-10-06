#pragma once

class CMineSweeperBoard
{
public:
	/*  Default Constructor */
	CMineSweeperBoard(void);
	/*  Copy Constructor */
	CMineSweeperBoard(const CMineSweeperBoard& board);
	/*  Destructor */
	~CMineSweeperBoard(void);
	/*  Function to randomly setup the board */
	void SetupBoard(void);
	/*  Get the color at a particular location */
	COLORREF GetBoardSpace(int row, int col);
	/*  Check if a Mine is present at current location */
	int checkIfMine(int row, int col) { return m_arrMineLocations[row][col]; }
	/*  Accessor functions to get/set board size information */
	int GetWidth(void) const { return m_nWidth; }
	void SetWidth(int nWidth)
	{
			m_nWidth = (nWidth >= 10 && nWidth <= 75) ? nWidth : 35;
	}
	int GetHeight(void) const { return m_nHeight; }
	void SetHeight(int nHeight)
	{
			m_nHeight = (nHeight >= 10 && nHeight <= 75) ? nHeight : 35;
	}
	int GetColumns(void) const { return m_nColumns; }
	void SetColumns(int nColumns)
	{
		m_nColumns = (nColumns >= 10 && nColumns <= 50) ? nColumns : 15;
	}
	int GetRows(void) const { return m_nRows; }
	void SetRows(int nRows)
	{
		m_nRows = (nRows >= 10 && nRows <= 50) ? nRows : 15;
	}
	/*  Score setter and getter */
	int getScore(void) { return m_Score; }
	void increaseScore(void) { m_Score++; }
	/*  Color setter and getter */
	int getColor(int row, int col) { return m_arrBoard[row][col]; }
	void setSquareColor(int row, int col, int color)
	{
		if (0 <= color && color <= 3) m_arrBoard[row][col] = color;
	}
	/*  Function to transfer mine locations to view matrix */
	void displayMineLocations(void);
	/*  Function to check if there are valid game moves left*/
	bool IsGameOver(void) const;
	/*  Difficulty selected by the user */
	void difficultySetter(double difficulty) { m_difficulty = difficulty; }
	double difficultyGetter(void) { return m_difficulty; }
	/*  Function to delete the board and free memory */
	void DeleteBoard(void);
	/* Save and load the game*/
	void saveGame(CArchive& ar);
	void loadGame(CArchive& ar);

private:
	/*  Function to create the board and allocate memory */
	void CreateBoard(void);
	/*  2D array pointer */
	int** m_arrBoard;
	int** m_arrMineLocations;
	/*  List of colors, 0 is background, 1 is a mine, 2 is a clear space*/
	COLORREF m_arrColors[3];
	/*  Board size information */
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	/*  Difficulty selected by the user */
	double m_difficulty;
	/*  Current score of the user */
	int m_Score;
};