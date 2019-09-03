#include "Board.h"
#include "coord.h"
#include <iostream>
#include <string>

using namespace std;

Board::Board()
{
    for(int i = 0; i < y_limit; i++){
        std::vector<char> row (7, ' ');
        board_state.push_back(row);
    }
}


void Board::copy_board(Board other_board){
    for (int i = 0; i < x_limit; i++){
        for(int j = 0; j < y_limit; j++){
            board_state[j][i] = other_board.get_piece(i,j);
        }
    }
}


void Board::print_board()
{
    int vert_axis[] = {1,2,3,4,5,6};
    string horz_axis = "  a b c d e f g\n";
    cout << horz_axis;
    for(int i = 0; i < y_limit; i++){
        cout << vert_axis[i];
        cout << " ";
        for(int j = 0; j < x_limit; j++){
            cout << this->get_piece(j, i);
            cout << " ";
        }
        cout << "\n";
    }
	return;
}


void Board::set_piece(int x_coord, int y_coord, char piece)
{
	board_state[y_coord][x_coord] = piece;
}


int Board::get_board_width()
{
	return x_limit;
}

int Board::get_board_height()
{
    return y_limit;
}

char Board::get_piece(int x, int y)
{
    return board_state[y][x];
}


