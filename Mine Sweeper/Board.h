#ifndef _BOARD_H_
#define _BOARD_H_

#include "Defines.h"
#include <vector>
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
	uint32 X;	// X Coord
	uint32 Y; 	// Y Coord
	bool IsDiscovered; // Tells if the point is already known
	//char Symbol; // NYI: is supposed to be the sysmbol that represents the point: number, * or -

	// Mines system
	uint32 TotalAroundMines; // Total mines around the point
	bool IsMine;

	// Flag system
	bool IsFlag;

	Point(uint32 x, uint32 y) : X(x), Y(y), /*Symbol('-'),*/ TotalAroundMines(0), IsDiscovered(false), IsMine(false), IsFlag(false) { }

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

class Board
{
public:
	Board(GameDifficulty difficulty);

	void AddPoint(Point* point);
	void CalcNearPointsFromMine(Point* mine);
	void IncrementDiscovered() { _discoveredPoints++; }
	void GetNearPoints(std::vector<Point*>& nearPoints, Point* point);
	void DiscoverPoint(Point* point);
	void DiscoverTheEntireMap();
	void Update(sf::RenderWindow& window, sf::Sprite& sprite);

	Point* GetPoint(int row, int col);

	uint32 GetRows() { return _rows; };
	uint32 GetColums() { return _columns; }
	uint32 GetTotalMines() { return _mines; }
	uint32 GetTotalDiscovered() { return _discoveredPoints; }
	uint32 GetSize() { return GetRows() * GetColums(); }

	bool IsBoardDicovered();
	bool ContainsPoint(int row, int col);

	GameDifficulty GetDifficulty() { return _difficulty; }

private:
	std::vector<std::vector<Point*>> _board;
	uint32 _rows;
	uint32 _columns;
	uint32 _mines;
	uint32 _discoveredPoints;
	GameDifficulty _difficulty;
};

#endif
