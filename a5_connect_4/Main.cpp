#include <ctime>
#include <iostream>
#include <random>
#include <vector>
#include "Board.h"
#include "Game.h"
#include "Node.h"

using namespace std;

void play_game(int game_option);
void do_mc_playouts(Node *game_node, int time_limit);
vector<Node> gen_next_moves(Node* curr_node);
void apply_PMCTS_rewards(Node *curr_node, Node *next_node);
void apply_MCTS_with_hueristic_rewards(Node *curr_node, Node *next_node);
int determine_winner_PMCTS(vector<Node> next_moves, int num_of_next_moves);
int determine_winner_with_heuristic(vector<Node> next_moves, int num_of_next_moves);
Node * perform_MCTS(Node *curr_node, int time_limit);

int main() {

    play_game(3);
    return 0;

}

void play_game(int game_option) {
    //Pure monte carlo will be o
    //player or monte carlo with
    Node* curr_node = new Node();
    int time_limit = 5000;
    while(!curr_node->is_game_over()) {
        cout << "current Board:\n";
        curr_node->reset_wlt_count();
        curr_node->getCurrState().print_game();
        cout << "\n";
        if (game_option == 1) {
            if (curr_node->getCurrState().is_x_turn()) {
                cout << "Player O:\nPerforming Pure MCTS...\n";
                curr_node = perform_MCTS(curr_node, time_limit);
            } else {
                //player move / heuristic
                string player_move;
                cout << "Player X:\nPlease enter a column you wish to place a piece in:\n";
                cin >> player_move;
                curr_node->perform_move(player_move);
            }
        }
        if (game_option == 2){
            if (curr_node->getCurrState().is_x_turn()) {
                //player move / heuristic
                string player_move;
                cout << "Player O:\nPlease enter a column you wish to place a piece in:\n";
                cin >> player_move;
                curr_node->perform_move(player_move);
            }
            else {
                cout << "Player X:\nPerforming MCTS with heuristic...\n";
                curr_node = perform_MCTS(curr_node, time_limit);
            }
        }
        if (game_option == 3){
            if (curr_node->getCurrState().is_x_turn()){
                cout << "Player O:\nPerforming Pure MCTS...\n";
            }
            else{
                cout << "Player X:\nPerforming MCTS with heuristic...\n";
            }
            curr_node = perform_MCTS(curr_node, time_limit);
        }
    }
    string winner;
    winner.push_back(curr_node->find_winner());

    cout << "game over!\nwinner is " + winner + "\n";
    curr_node->getCurrState().print_game();
}
Node * perform_MCTS(Node *curr_node, int time_limit) {
        vector<Node> next_moves = gen_next_moves(curr_node);
        //int num_of_next_moves = curr_node->getCurrState().get_board().get_board_width();
        int num_of_next_moves = next_moves.size();
        //perform random playouts
        bool defended_threes = false;

        if(!curr_node->getCurrState().is_x_turn()){
            Coord defending_threes = curr_node->getCurrState().defend_threes(curr_node->get_last_move());
            if (defending_threes.get_x() != -1 && defending_threes.get_y() != -1){
                curr_node->perform_move(defending_threes.get_x());
                defended_threes = true;
            }
        }
        if (!defended_threes) {
            for (int i = 0; i < num_of_next_moves; i++) {
                do_mc_playouts(&next_moves[i], time_limit / num_of_next_moves);
            }

            // find most next move
            if (curr_node->getCurrState().is_x_turn()) {
                int winner = determine_winner_PMCTS(next_moves, num_of_next_moves);
                curr_node = new Node();
                curr_node->copy_node(&next_moves[winner]);
            } else {
                int winner = determine_winner_with_heuristic(next_moves, num_of_next_moves);
                curr_node = new Node();
                curr_node->copy_node(&next_moves[winner]);
            }
        }
        return curr_node;
}


//do playout for one of the different possible games
void do_mc_playouts(Node *game_node, int time_limit){
    clock_t start = clock();
    clock_t end = clock();
    Node* curr_node = game_node;
    while (end - start < time_limit){
        int i = 1;
        int board_width = 7;
        while(!curr_node->is_game_over()) {
            vector<Node> next_states = gen_next_moves(curr_node);
            int rand_index = rand() % board_width;
            while (rand_index >= next_states.size()) {
                rand_index = rand() % next_states.size();
            }
            curr_node = new Node();
            curr_node->copy_node(&next_states[rand_index]);
            i++;
        }


        if (!game_node->getCurrState().is_x_turn())
            apply_PMCTS_rewards(game_node, curr_node);
        else
            apply_MCTS_with_hueristic_rewards(game_node, curr_node);

        end = clock();
        curr_node = game_node;
    }
}

int determine_winner_PMCTS(vector<Node> next_moves, int num_of_next_moves) {
    int curr_winner = 0;
    for (int i = 1; i < num_of_next_moves; i++) {
        if (next_moves[i].getWins() > next_moves[curr_winner].getWins())
            curr_winner = i;
    }
    return curr_winner;
}

int determine_winner_with_heuristic(vector<Node> next_moves, int num_of_next_moves){
    vector<double> win_value;
    for(int i = 0; i < num_of_next_moves; i++){
        double wins = double(next_moves[i].getWins());
        double total = double(next_moves[i].getWins() + next_moves[i].getLosses()+next_moves[i].getTies());
        win_value.push_back(wins / total);
    }
    int curr_winner = 0;
    for (int i = 1; i < num_of_next_moves; i++) {
        if (win_value[curr_winner] < win_value[i])
            curr_winner = i;
    }
    return curr_winner;
}

void apply_PMCTS_rewards(Node *curr_node, Node *next_node) {
    char winner = next_node->find_winner();
    if(winner == 'o'){
        curr_node->increment_wins();
    }
    else if(winner == 'x'){
        curr_node->increment_losses();
    }
    else{
        curr_node->increment_ties();
    }
}

void apply_MCTS_with_hueristic_rewards(Node *curr_node, Node *next_node) {
    char winner = next_node->find_winner();
    if(winner == 'x'){
        curr_node->increment_wins();
    }
    else if(winner == 'o'){
        curr_node->increment_losses();
    }
    else{
        curr_node->increment_ties();
    }
}

vector<Node> gen_next_moves(Node* curr_node){
    vector<Node> next_moves;
    vector<int> next_game_states = curr_node->getCurrState().get_list_of_next_moves();
    for(int i = 0; i < next_game_states.size(); i++){
        if (next_game_states[i] >= 0){
            Coord next_move_coord = Coord(i,next_game_states[i]);
            Node next_move_node = Node();
            next_move_node.copy_node(curr_node);
            next_move_node.apply_move(next_move_coord);
            next_moves.push_back(next_move_node);
        }
    }
    return next_moves;
}