#include "game.h"
#include <iostream>
#include <cassert>

namespace tictactoe{

Game::Game() : m_field(10, std::vector<OptionalPlayer>(10,
                                        OptionalPlayer::empty)){}


std::string Game::get_user_input() const {
    std::string input;
    std::cin >> input;
    return input;
}

OptionalPlayer Game::get_cur_player() const {
    return m_cur_player;
}

GameResult Game::get_result() const {
    return result;
}

std::vector<std::vector<OptionalPlayer>> Game::get_board() const {
    return m_field;
}

void Game::switch_player(){
    if (m_cur_player == OptionalPlayer::X){
        m_cur_player = OptionalPlayer::O;
    }
    else{
        m_cur_player = OptionalPlayer::X;
    }
}

bool Game::check_winner_vert(Move move) const {
    int upper = std::max(0, move.row - 4);
    int lower = std::min(9, move.row + 4);
    int count_up = 0, count_down = 0;
    for (int i = move.row - 1; i >= upper; i--) {
        if (m_field[i][move.col] != move.player){
            break;
        }
        count_up++;
    }
    for (int i = move.row + 1; i <= lower; i++) {
        if (m_field[i][move.col] != move.player){
            break;
        }
        count_down++;
    }
    return (count_up + count_down + 1 == 5);
}

bool Game::check_winner_horiz(Move move) const {
    int left = std::max(0, move.col - 4);
    int right = std::min(9, move.col + 4);
    int count_left = 0, count_right = 0;
    for (int i = move.col - 1; i >= left; i--){
        if (m_field[move.row][i] != move.player) {
            break;
        }
        count_left++;
    }
    for (int i = move.col + 1; i <= right; i++){
        if (m_field[move.row][i] != move.player) {
            break;
        }
        count_right++;
    }
    return (count_left + count_right + 1 == 5);
}

bool Game::check_winner_left_diag(Move move) const {
    int steps_left_up = std::min(move.col, move.row);
    int steps_right_down = 9 - std::max(move.col, move.row);
    int count_left_up = 0, count_right_down = 0;
    for (int step = 1; step <= steps_left_up; step++) {
        if (m_field[move.row - step][move.col - step] != move.player) {
            break;
        }
        count_left_up++;
    }
    for (int step = 1; step <= steps_right_down; step++) {
        if (m_field[move.row + step][move.col + step] != move.player) {
            break;
        }
        count_right_down++;
    }
    return (count_left_up + count_right_down + 1 == 5);
}

bool Game::check_winner_right_diag(Move move) const {
    int steps_left_down = std::min(9 - move.row, move.col);
    int steps_right_up = std::min(move.row, 9 - move.col);
    int count_left_down = 0, count_right_up = 0;
    for (int step = 1; step <= steps_left_down; step++) {
        if (m_field[move.row + step][move.col - step] != move.player) {
            break;
        }
        count_left_down++;
    }
    for (int step = 1; step <= steps_right_up; step++) {
        if (m_field[move.row - step][move.col + step] != move.player) {
            break;
        }
        count_right_up++;
    }
    return (count_left_down + count_right_up + 1 == 5);
}

void Game::check_winner(Move move) {
    assert(move.legal);
    if (check_winner_vert(move) || check_winner_horiz(move) 
        || check_winner_left_diag(move) || check_winner_right_diag(move)){
            if (move.player == OptionalPlayer::O) {
                result = GameResult::O_wins;
            }
            else {
                result = GameResult::X_wins;
            }
            return;
        }
    if (empty_cells == 0) {
        result = GameResult::draw;
    }
}



Move Game::make_move(int row, int col){
    if (m_field[row][col] != OptionalPlayer::empty){
        return {row, col, m_cur_player, false};
    }
    m_field[row][col] = m_cur_player;
    empty_cells--;
    switch_player();
    return {row, col, m_field[row][col], true};
}

}  // namespace tictactoe