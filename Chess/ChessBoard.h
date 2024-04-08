#ifndef _BOARD_H_
#define _BOARD_H_

#include "Field.h"

#define MAX_COLUMNS 8
#define MAX_ROWS	8

class Board
{
public:
	static Board* instance()
	{
		static Board instance;
		return &instance;
	}

	Board(Board const&) = delete;
	void operator=(Board const&) = delete;

	void Initialize();
	void InitializeBoard();
	void InitializePawns();
	void InitializeKnights();
	void InitializeQueens();
	void InitializeBishops();
	void InitializeRooks();
	void InitializeKings();

	void Test();

	void Update();

private:
	Board() { }
	Field _board[MAX_ROWS][MAX_COLUMNS];
};

#define sChessBoard Board::instance()

#endif
