#ifndef Game_header
#define Game_header
#include "Board.h"
#include "coord.h"
#include <string>
#include <vector>
using namespace std;
class Game 
{
public:
	Game();
    Game(const Game &other_game);
	void print_game();
	Board get_board() const;
	vector<int> get_list_of_next_moves() const;
	bool is_x_turn();
	void update_next_move_tracking(int col);
    void set_piece(Coord coords);
    Coord perform_player_move(string col);
    Coord perform_player_move(int col);
    bool is_game_over(Coord last_move);
    char find_winner(Coord last_move);
    Coord defend_threes(Coord last_move);
    void set_x_turn(bool turn);
private:
	Board game_board;
	std::vector <int> next_moves;
	bool x_turn;
};
#endif
