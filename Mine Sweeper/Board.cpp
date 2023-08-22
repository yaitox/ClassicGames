#include "Board.h"
#include "MineSweeper.h"

Board::Board(GameDifficulty difficulty) : _difficulty(difficulty), _discoveredPoints(0)
{
	MineSweeperConfig config = MineSweeper::GetConfig(difficulty);
	_rows = config.TotalRows;
	_columns = config.TotalColumns;
	_mines = config.TotalMines;
	_state = GameState::Playing;
	_board.resize(_rows, std::vector<Point*>(_columns));
}

void Board::AddPoint(Point* newPoint)
{
	_board[newPoint->X][newPoint->Y] = newPoint;
}

void Board::CalcNearPointsFromMine(Point* mine)
{
	std::vector<Point*> nearPoints;
	GetNearPoints(nearPoints, mine);

	for (Point* nearPoint : nearPoints)
		if (!nearPoint->IsMine)
			++nearPoint->TotalAroundMines;
}

Point* Board::GetPoint(int row, int col)
{
	return (ContainsPoint(row, col) ? _board[row][col] : nullptr);
}

bool Board::IsBoardDicovered()
{
	return GetTotalDiscovered() == GetSize() - GetTotalMines();
}

bool Board::ContainsPoint(int row, int col)
{
	return (row >= 0 && col >= 0 && row < (int)GetRows() && col < (int)GetColums());
}

void Board::GetNearPoints(std::vector<Point*>& nearPoints, Point* point)
{
	for (int row = int(point->X) - 1; row <= int(point->X) + 1; ++row)
	{
		for (int col = point->Y - 1; col <= point->Y + 1; ++col)
		{
			if (Point* nearPoint = GetPoint(row, col))
				nearPoints.push_back(nearPoint);
		}
	}	
}

void Board::DiscoverPoint(Point* point)
{
	if (!point || point->IsDiscovered)
		return;

	if (point->IsMine)
	{
		SetGameState(GameState::Lose);
		DiscoverTheEntireMap();
		return;
	}

	point->IsFlag = false; // a point marked as flag can be discovered so we undo the flag.
	point->IsDiscovered = true;
	IncrementDiscovered();

	std::vector<Point*> nearPoints;
	GetNearPoints(nearPoints, point);

	for (Point* nearPoint : nearPoints)
		if (point->TotalAroundMines == 0 && !nearPoint->IsFlag)
			DiscoverPoint(nearPoint);

	if (IsBoardDicovered() && GetGameState() == GameState::Playing)
	{
		SetGameState(GameState::Win);
		return;
	}
}

void Board::DiscoverTheEntireMap()
{
	for (uint32 i = 0; i < GetRows(); ++i)
	{
		for (uint32 j = 0; j < GetColums(); ++j)
		{
			if (Point* point = GetPoint(i, j))
			{
				point->IsFlag = false;
				point->IsDiscovered = true;
			}
		}
	}		
}

void Board::Update(sf::RenderWindow& window, sf::Sprite& sprite)
{
	window.clear(sf::Color::White);

	for (uint32 i = 0; i < GetRows(); ++i)
		for (uint32 j = 0; j < GetColums(); ++j)
		{
			Point* point = GetPoint(i, j);

			uint32 index = point->TotalAroundMines;

			if (point->IsFlag)
				index = 11;

			if (!point->IsDiscovered && !point->IsFlag)
				index = 10;

			if (point->IsMine && point->IsDiscovered)
				index = 9;

			sprite.setTextureRect(sf::IntRect(index * 32, 0, 32, 32));
			sprite.setPosition(32.0f * j, 32.0f * i);
			window.draw(sprite);
		}

	window.display();
}