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
	_board[0][1].Piece = blackKnightLeft;

	// Right g8
	Piece* blackKnightRight = new Piece(Team::Black, PieceType::Knight);
	_board[0][6].Piece = blackKnightRight;

	// White knights
	// Left b1
	Piece* whiteKnightLeft = new Piece(Team::White, PieceType::Knight);
	_board[7][1].Piece = whiteKnightLeft;

	// Right g1
	Piece* whiteKnightRight = new Piece(Team::White, PieceType::Knight);
	_board[7][6].Piece = whiteKnightRight;
}

void Board::InitializeKings()
{
	Piece* whiteKing = new Piece(Team::White, PieceType::King);
	_board[7][4].Piece = whiteKing;

	Piece* blackKing = new Piece(Team::Black, PieceType::King);
	_board[0][4].Piece = blackKing;
}

void Board::InitializeBishops()
{
	// White bishops
	Piece* whiteLeftBishop = new Piece(Team::White, PieceType::Bishop);
	_board[7][2].Piece = whiteLeftBishop;

	Piece* whiteRightBishop = new Piece(Team::White, PieceType::Bishop);
	_board[7][5].Piece = whiteRightBishop;

	// Black bishops
	Piece* blackLeftBishop = new Piece(Team::Black, PieceType::Bishop);
	_board[0][2].Piece = blackLeftBishop;

	Piece* blackRightBishop = new Piece(Team::Black, PieceType::Bishop);
	_board[0][5].Piece = blackRightBishop;
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
	InitializeKnights();
	InitializeKings();
	InitializeBishops();
}
