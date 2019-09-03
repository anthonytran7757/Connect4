#include "Game.h"
#include "Board.h"
#include "coord.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

Game::Game() //default constructor
{
    x_turn = false;
	game_board = Board();
	int lim = game_board.get_board_width();
	for (int i = 0; i < lim; i++) {
		next_moves.push_back(game_board.get_board_height() - 1);
	}
}

Game::Game(const Game &other_game){
    game_board = Board();
    game_board.copy_board(other_game.get_board());
    x_turn = other_game.x_turn;
    vector<int> other_games_move_list = other_game.get_list_of_next_moves();
    for (int i = 0; i < game_board.get_board_width(); i++){
        next_moves.push_back(other_games_move_list[i]);
    }
}

void Game::set_piece(Coord coords)
{
    int x = coords.get_x();
    int y = coords.get_y();
    char piece;
    x_turn = !x_turn;
    if (is_x_turn()){
        piece = 'x';
    }
    else{
        piece = 'o';
    }
    this->game_board.set_piece(x, y, piece);

}

bool is_board_filled(vector<int> next_moves){
    for(int x : next_moves){
        if (x != -1){
            return false;
        }
    }
    return true;
}

void Game::print_game()
{
	this->game_board.print_board();
}


bool check_vert(Board curr_board, Coord coord){
    string x_win_cond = "xxxx";
    string o_win_cond = "oooo";
    int height_of_board = curr_board.get_board_height();
    int col = coord.get_x();
    string vert_pieces = "";
    for (int i = 0; i < height_of_board; i++){
        char curr_piece = curr_board.get_piece(col, i);
        vert_pieces = vert_pieces + curr_piece;
    }
    if (vert_pieces.find(x_win_cond)!= string::npos || vert_pieces.find(o_win_cond)!= string::npos)
        return true;
    return false;
}

bool check_horz(Board curr_board, Coord coord){
    string x_win_cond = "xxxx";
    string o_win_cond = "oooo";
    int board_width = curr_board.get_board_width();
    int row = coord.get_y();
    string horz_pieces = "";
    for (int i = 0; i < board_width; i++){
        char curr_piece = curr_board.get_piece(i, row);
        horz_pieces = horz_pieces + curr_piece;
    }
    if (horz_pieces.find(x_win_cond)!= string::npos || horz_pieces.find(o_win_cond)!= string::npos)
        return true;
    return false;
}

string to_upper_right(Board board, Coord lm_coord){
    int curr_col = lm_coord.get_x();
    int curr_row = lm_coord.get_y();
    string diag_pieces = "";
    //go toward bottom left
    while(curr_col >= 0 && curr_row <= board.get_board_height() - 1) {
        diag_pieces = board.get_piece(curr_col, curr_row) + diag_pieces;
        curr_col -= 1;
        curr_row += 1;
    }
    curr_col = lm_coord.get_x() + 1;
    curr_row = lm_coord.get_y() - 1;
    //go toward upper right
    while(curr_col <= board.get_board_width() - 1  && curr_row >= 0) {
        diag_pieces = diag_pieces + board.get_piece(curr_col, curr_row);
        curr_col += 1;
        curr_row -= 1;
    }
    return diag_pieces;
}

string to_upper_left(Board board, Coord lm_coord) {
    int curr_col = lm_coord.get_x();
    int curr_row = lm_coord.get_y();
    string diag_pieces = "";
    //go toward bottom right
    while (curr_col <= board.get_board_width() - 1 && curr_row <= board.get_board_height() - 1) {
        diag_pieces = diag_pieces + board.get_piece(curr_col, curr_row);
        curr_col += 1;
        curr_row += 1;
    }
    curr_col = lm_coord.get_x() - 1;
    curr_row = lm_coord.get_y() - 1;
    //go toward upper left
    while (curr_col >= 0 && curr_row >= 0) {
        diag_pieces = board.get_piece(curr_col, curr_row) + diag_pieces;
        curr_col -= 1;
        curr_row -= 1;
    }
    return diag_pieces;
}
bool check_diagonal(Board curr_board, Coord lm_coord){
    string x_win_cond = "xxxx";
    string o_win_cond = "oooo";
    string vert_pieces = to_upper_right(curr_board, lm_coord);
    if (vert_pieces.find(x_win_cond)!= string::npos || vert_pieces.find(o_win_cond)!= string::npos)
        return true;
    vert_pieces = to_upper_left(curr_board, lm_coord);
    if (vert_pieces.find(x_win_cond)!= string::npos || vert_pieces.find(o_win_cond)!= string::npos)
        return true;
    return false;
}

bool Game::is_game_over(Coord last_move){
    if (check_vert(game_board, last_move) || check_horz(this->game_board, last_move) || check_diagonal(this->game_board, last_move))
        return true;
    else if (is_board_filled(next_moves))
        return true;
    return false;
}

bool Game::is_x_turn() {
    return x_turn;
}

void Game::update_next_move_tracking(int col) {
    next_moves[col] = next_moves[col] - 1;
}

vector<int> Game::get_list_of_next_moves() const{
    return next_moves;
}

Board Game::get_board() const {
    return game_board;
}

string get_vert(Board curr_board, Coord last_move){
    int height_of_board = curr_board.get_board_height();
    int col = last_move.get_x();
    string vert_pieces = "";
    for (int i = 0; i < height_of_board; i++){
        char curr_piece = curr_board.get_piece(col, i);
        vert_pieces = vert_pieces + curr_piece;
    }
    return vert_pieces;
}

string get_horz(Board curr_board, Coord last_move){
    int board_width = curr_board.get_board_width();
    int row = last_move.get_y();
    string horz_pieces = "";
    for (int i = 0; i < board_width; i++){
        char curr_piece = curr_board.get_piece(i, row);
        horz_pieces = horz_pieces + curr_piece;
    }
    return horz_pieces;
}

char Game::find_winner(Coord last_move){
    string res;
    string x_win_cond = "xxxx";
    string o_win_cond = "oooo";
    res = get_vert(game_board, last_move);
    if(check_vert(this->game_board, last_move)){
        res = get_vert(game_board, last_move);
        if(res.find(x_win_cond)!= string::npos){
            return 'x';
        }
        else{
            return 'o';
        }
    }
    else if(check_horz(this->game_board, last_move)){
        res = get_horz(game_board, last_move);
        if(res.find(x_win_cond)!= string::npos){
            return 'x';
        }
        else{
            return  'o';
        }
    }
    else if(check_diagonal(game_board, last_move))
    {
        res = to_upper_left(this->game_board, last_move);
        if(res.find(x_win_cond)!= string::npos){
            return 'x';
        }
        else if(res.find(o_win_cond)!=string::npos){
            return  'o';
        }
        else{
            res = to_upper_right(this->game_board, last_move);
            if(res.find(x_win_cond)!= string::npos){
                return 'x';
            }
            else{
                return  'o';
            }
        }
    }
    else{
        return 't';
    }
}

bool verify_player_move(vector<int> moves, string col){
    if (col.length() != 1)
        return false;
    else if(tolower(col[0]) > 'g' || tolower(col[0]) < 'a')
        return false;
    else if (moves[(int)col[0] - (int)'a'] < 0)
        return false;
    return true;
}



Coord Game::perform_player_move(string col){
    string move = col;
    while (!verify_player_move(next_moves, move)){
        move = "";
        cout << "please enter a valid move:\n";
        cin >> move;
    }
    int col_as_int = (int)move[0] - (int)'a';
    Coord player_move =  Coord(col_as_int, next_moves[col_as_int]);
    this->set_piece(player_move);
    this->update_next_move_tracking(col_as_int);
    return player_move;
}

Coord Game::perform_player_move(int col) {
    Coord player_move =  Coord(col, next_moves[col]);
    this->set_piece(player_move);
    this->update_next_move_tracking(col);
    return player_move;
}

Coord Game::defend_threes(Coord last_move){
    int curr_index_x = last_move.get_x();
    int curr_index_y = last_move.get_y();
    string o_threes = "ooo";
    vector <string> three_cases = {" ooo", "o oo", "oo o", "ooo "};
    string res = get_vert(game_board, last_move);
    if (res.find(o_threes)!=string::npos && curr_index_y - 1 >= 0
        && game_board.get_piece(curr_index_x, curr_index_y - 1) == ' '){
        return Coord(curr_index_x, last_move.get_y() - 1);
    }
    res = get_horz(game_board, last_move);
    for (string x: three_cases){
        if(res.find(x)!=string::npos){
            int index_of_space = res.find(x) + x.find(" ");
            if(next_moves[index_of_space] == curr_index_y){
                return Coord(index_of_space, curr_index_y);
            }
        }
    }
    return Coord(-1,-1);
}

void Game::set_x_turn(bool turn){
    x_turn = turn;
}