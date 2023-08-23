#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Defines.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"

enum class GameDifficulty : uint8
{
	Easy,
	Medium,
	Hard,

	Max
};

struct Point
{
public:
	uint32 X;
	uint32 Y;
	bool IsDiscovered;

	// Mines system
	uint32 TotalAroundMines;
	bool IsMine;

	// Flag system
	bool IsFlag;

	Point(uint32 x, uint32 y) : X(x), Y(y), IsDiscovered(false), 
		TotalAroundMines(0), IsMine(false), 
		IsFlag(false) { }

	~Point() { }

	void ToString()
	{
		std::cout << "Point set on:" << std::endl
			<< "Row: " << X << ' '
			<< "Column: " << Y << std::endl;

		if (IsMine)
			std::cout << "The point is a mine." << std::endl;
		else
			std::cout << (IsDiscovered ? "The point is discovered" : "The point is not discovered")
			<< " and has " << TotalAroundMines << " mines around." << "\n\n";
	}

	void SetOrUndoFlag() { IsFlag = !IsFlag; }
};

enum class GameState : uint32
{
	Lose,
	Win,
	Playing
};

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

	void Clean();

	void AddPoint(Point* point);
	void CalcNearPointsFromMine(Point* mine);
	void DiscoverPoint(Point* point);
	void DiscoverTheEntireMap();
	void GetNearPoints(std::vector<Point*>& nearPoints, Point* point);
	void IncrementDiscovered() { _discoveredPoints++; }
	void Update(sf::RenderWindow& window, sf::Sprite& sprite);

	Point* GetPoint(int row, int col);

	uint32 GetColums() { return _columns; }
	uint32 GetRows() { return _rows; };
	uint32 GetSize() { return GetRows() * GetColums(); }
	uint32 GetTotalMines() { return _mines; }
	uint32 GetTotalDiscovered() { return _discoveredPoints; }

	bool ContainsPoint(int row, int col);
	bool IsBoardDicovered();

	GameDifficulty GetDifficulty() { return _difficulty; }
	void InitializeBoard(GameDifficulty const difficulty);

	void SetGameState(GameState state) { _state = state; }
	GameState const GetGameState() { return _state; }

private:
	Board() { };

	std::vector<std::vector<Point*>> _board;
	uint32 _rows;
	uint32 _columns;
	uint32 _mines;
	uint32 _discoveredPoints;
	GameDifficulty _difficulty;
	GameState _state;
};

#define sBoard Board::instance()

#endif
