#ifndef _MINE_SWEEPER_H
#define _MINE_SWEEPER_H

#include <vector>
#include "../Defines.h"

struct Point;

struct MineSweeperConfig
{
	uint32 TotalColumns;
	uint32 TotalRows;
	uint32 TotalMines;
	uint32 BoardHeight;
	uint32 BoardWidth;
};

enum class GameDifficulty : uint8
{
	Easy,
	Medium,
	Hard,

	Max
};

enum class GameState : uint8
{
	Lose,
	Win,
	Playing
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
