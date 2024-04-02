#ifndef _BOARD_H_
#define _BOARD_H_

class Board
{
public:
	static Board* instance()
	{
		static Board instance;
		return &instance;
	}
};

#define sBoard Board::instance()

#endif
