#ifndef _PIECE_H_
#define _PIECE_H_

#include "../Defines.h"

enum class Team : uint8
{
	Black,
	White
};

enum class PieceType : uint8
{
	Bishop,
	King,
	Knight,
	Pawn,
	Queen,
	Rook
};

class Piece
{
public:
	Piece(Team team, PieceType type) : _team(team), _pieceType(type) { }

	void GetAvailableMoves();

	// Helpers
	PieceType GetPieceType() { return _pieceType; }
	Team GetTeam() { return _team; }
	
private:
	PieceType _pieceType;
	Team _team;
};

#endif
