#ifndef _FIELD_H_
#define _FIELD_H_

#include "../Defines.h"

class Piece;

enum class FieldColor : uint8
{
	Black,
	White
};

struct Position
{
	uint8 X;
	uint8 Y;
};

struct Field
{
	Piece* Piece;
	FieldColor FieldColor;
	Position Position;
};

#endif
