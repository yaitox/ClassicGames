#include "ChessBoard.h"
#include "Piece.h"

void Board::InitializePawns()
{
	// Black pawns
	for (uint8 i = 0; i < MAX_COLUMNS; ++i)
	{
		Piece* pawn = new Piece(Team::Black, PieceType::Pawn);

		FieldColor color = i % 2 == 0 ? FieldColor::Black : FieldColor::White;

		Position position;
		position.X = i;
		position.Y = 6;

		Field field;
		field.Piece = pawn;
		field.FieldColor = color;
		field.Position = position;

		_board[field.Position.Y][field.Position.X] = field;
	}

	// White pawns
	for (uint8 i = 0; i < MAX_COLUMNS; ++i)
	{
		Piece* pawn = new Piece(Team::White, PieceType::Pawn);

		FieldColor color = i % 2 == 0 ? FieldColor::White : FieldColor::Black;

		Position position;
		position.X = i;
		position.Y = 1;

		Field field;
		field.Piece = pawn;
		field.FieldColor = color;
		field.Position = position;

		_board[field.Position.Y][field.Position.X] = field;
	}
}

void Board::Initialize()
{
	InitializePawns();
}
