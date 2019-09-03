#include "Node.h"
#include "coord.h"
#include <string>
#include <iostream>
#include <vector>
#include <climits>

Node::Node() {
    curr_state = Game();
    last_move = Coord(0, 0);
    wins = 0;
    losses = 0;
    ties = 0;
}

void Node::copy_node(Node *other_Node){
    curr_state = Game(other_Node->getCurrState());
    last_move = Coord(other_Node->get_last_move().get_x(), other_Node->get_last_move().get_y());
    wins = other_Node->getWins();
    losses = other_Node->getLosses();
    ties = other_Node->getTies();
}

void Node::apply_move(Coord move_to_make) {
    curr_state.set_piece(move_to_make);
    curr_state.update_next_move_tracking(move_to_make.get_x());
    last_move = Coord(move_to_make.get_x(), move_to_make.get_y());
}

bool Node::is_game_over() {
    return curr_state.is_game_over(last_move);
}

Game & Node::getCurrState(){
    return curr_state;
}

int Node::getWins() const {
    return wins;
}

int Node::getLosses() const {
    return losses;
}

int Node::getTies() const {
    return ties;
}

void Node::increment_wins() {
    Node::wins += 1;
}

void Node::increment_losses() {
    Node::losses += 1;
}

void Node::increment_ties() {
    Node::ties += 1;
}

char Node::find_winner(){
    return curr_state.find_winner(last_move);
}

Coord Node::get_last_move() {
    return last_move;
}

void Node::perform_move(string col){
    Coord player_move = curr_state.perform_player_move(col);
    last_move = Coord(player_move);
}

void Node::perform_move(int col) {
    Coord player_move = curr_state.perform_player_move(col);
    last_move = Coord(player_move);
}

void Node:: reset_wlt_count(){
    wins = 0;
    losses = 0;
    ties = 0;
}

void Node::set_x_turn(bool turn) {
    curr_state.set_x_turn(turn);
}