#ifndef _MINE_SWEEPER_H
#define _MINE_SWEEPER_H

#include <vector>
#include "Board.h"

namespace MineSweeper
{
	void InitializeAvailablePointsContainer();
	void ShowAvailablePoints();
	void InitializeMinesPositions();
	inline void InitializeRandom();
	void SetBoardSizeByDifficulty(GameDifficulty difficulty);
	bool IsValidDifficulty(int difficulty);
	void AskUserForDifficulty();
	void InitializeRandomMines();
	uint32 GetWindowSize(uint32 rows);
	void InitializeGame();
	void PlayGame();
}

#endif
