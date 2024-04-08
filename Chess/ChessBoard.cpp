#include "ChessBoard.h"
#include "Piece.h"

void Board::InitializePawns()
{
	// Black pawns
	for (uint8 i = 0; i < MAX_COLUMNS; ++i)
	{
		Field& field = _board[1][i];
		Piece* pawn = new Piece(Team::Black, PieceType::Pawn);
		field.Piece = pawn;
	}

	// White pawns
	for (uint8 i = 0; i < MAX_COLUMNS; ++i)
	{
		Field& field = _board[6][i];
		Piece* pawn = new Piece(Team::White, PieceType::Pawn);
		field.Piece = pawn;
	}
}

void Board::InitializeKnights()
{
	// Black knights
	// Left b8
	Piece* blackKnightLeft = new Piece(Team::Black, PieceType::Knight);
	Position blackKnightLeftPosition;
	blackKnightLeftPosition.X = 1;
	blackKnightLeftPosition.Y = 0;

	Field fieldBlackKnightLeft;
	fieldBlackKnightLeft.FieldColor = FieldColor::Black;
	fieldBlackKnightLeft.Piece = blackKnightLeft;
	fieldBlackKnightLeft.Position = blackKnightLeftPosition;
	_board[fieldBlackKnightLeft.Position.Y][fieldBlackKnightLeft.Position.X] = fieldBlackKnightLeft;

	// Right g8
	Piece* blackKnightRight = new Piece(Team::Black, PieceType::Knight);
	Position blackKnightRightPosition;
	blackKnightRightPosition.X = 6;
	blackKnightRightPosition.Y = 0;

	Field fieldBlackKnightRight;
	fieldBlackKnightRight.FieldColor = FieldColor::White;
	fieldBlackKnightRight.Piece = blackKnightRight;
	fieldBlackKnightRight.Position = blackKnightRightPosition;
	_board[fieldBlackKnightRight.Position.Y][fieldBlackKnightRight.Position.X] = fieldBlackKnightRight;

	// White knights
	// Left b1
	Piece* whiteKnightLeft = new Piece(Team::White, PieceType::Knight);
	Position whiteKnightLeftPosition;
	whiteKnightLeftPosition.X = 1;
	whiteKnightLeftPosition.Y = 7;

	Field fieldWhiteKnightLeft;
	fieldWhiteKnightLeft.FieldColor = FieldColor::White;
	fieldWhiteKnightLeft.Piece = whiteKnightLeft;
	fieldWhiteKnightLeft.Position = whiteKnightLeftPosition;
	_board[fieldWhiteKnightLeft.Position.Y][fieldWhiteKnightLeft.Position.X] = fieldWhiteKnightLeft;

	// Right g1
	Piece* whiteKnightRight = new Piece(Team::White, PieceType::Knight);
	Position whiteKnightRightPosition;
	whiteKnightRightPosition.X = 6;
	whiteKnightRightPosition.Y = 7;

	Field fieldWhiteKnightRight;
	fieldWhiteKnightRight.FieldColor = FieldColor::Black;
	fieldWhiteKnightRight.Piece = whiteKnightRight;
	fieldWhiteKnightRight.Position = whiteKnightRightPosition;
	_board[fieldWhiteKnightRight.Position.Y][fieldWhiteKnightRight.Position.X] = fieldWhiteKnightRight;
}

void Board::InitializeBoard()
{
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		FieldColor lastColor;
		if (i % 2 == 0)
			lastColor = FieldColor::White;
		else
			lastColor = FieldColor::Black;

		for (int j = 0; j < MAX_COLUMNS; ++j)
		{
			Position position;
			position.X = i;
			position.Y = j;

			Field field;
			field.FieldColor = lastColor;
			field.Piece = nullptr;
			field.Position = position;
			_board[i][j] = field;

			if (lastColor == FieldColor::Black)
				lastColor = FieldColor::White;
			else
				lastColor = FieldColor::Black;
		}
	}
}

void Board::Initialize()
{
	InitializeBoard();
	InitializePawns();
}
