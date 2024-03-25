#ifndef _MINE_SWEEPER_H
#define _MINE_SWEEPER_H

#include <vector>
#include "Board.h"

struct MineSweeperConfig
{
	uint32 TotalColumns;
	uint32 TotalRows;
	uint32 TotalMines;
	uint32 Height;
	uint32 Width;
};

namespace MineSweeper
{
	void AskUserForDifficulty();
	MineSweeperConfig const& GetConfig(GameDifficulty const& difficulty);
	uint32 GetWindowSize(uint32 rows);
	void InitializeAvailablePointsContainer(std::vector<Point*>& availablePoints);
	void InitializeGame();
	void InitializeMinesPositions(std::vector<Point*>& availablePoints);
	inline void InitializeRandom();
	void InitializeRandomMines();
	bool const IsValidDifficulty(int const& difficulty);
	void PlayGame();
	void SetBoardSizeByDifficulty(GameDifficulty difficulty);
	void ShowAvailablePoints();
}

#endif
