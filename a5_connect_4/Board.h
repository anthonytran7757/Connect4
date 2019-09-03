#ifndef Board_header
#define Board_header
#include <vector>
#include "coord.h"
class Board
{

public:
	Board();
	void copy_board(Board other_board);
	void print_board();
	void set_piece(int x_coord, int y_coord, char piece);
	int get_board_width();
	int get_board_height();
	char get_piece(int x, int y);

private:
	const static int x_limit = 7;
	const static int y_limit = 6;
    std::vector<std::vector<char>> board_state;
};
#endif
