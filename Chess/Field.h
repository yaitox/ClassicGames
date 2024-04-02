#ifndef _FIELD_H_
#define _FIELD_H_

#include "../Defines.h"

enum class FieldColor : uint8
{
	Black,
	White
};

class Piece;

struct Field
{
	Piece* Piece;
	FieldColor FieldColor;
};

#endif
