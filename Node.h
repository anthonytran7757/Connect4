#include "Game.h"
#include "coord.h"
#include <vector>

#ifndef Node_header
#define Node_header

class Node{
public:
    Node();
    void copy_node(Node *other_Node);
    Node(Game curr_game, Coord move_to_make);
    bool is_game_over();
    Game & getCurrState();
    int getWins() const;
    int getLosses() const;
    int getTies() const;
    void increment_wins();
    void increment_losses();
    void increment_ties();
    char find_winner();
    Coord get_last_move();
    void perform_move(string col);
    void perform_move(int col);
    void apply_move(Coord move_to_make);
    void reset_wlt_count();
    void set_x_turn(bool turn);

private:
    Game curr_state;
    Coord last_move;

private:
    int wins;
    int losses;
    int ties;

};
#endif