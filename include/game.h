#ifndef GAME_H_
#define GAME_H_

#include "game_fwd.h"
#include <vector>
#include <map>
#include <string>

namespace tictactoe {


class Game {
    GameResult result = GameResult::undefined;
    int empty_cells = 10 * 10;
    std::vector<std::vector<OptionalPlayer>> m_field;
    OptionalPlayer m_cur_player = OptionalPlayer::O;
    
    bool check_winner_vert(Move move) const;
    bool check_winner_horiz(Move move) const;
    bool check_winner_left_diag(Move move) const;
    bool check_winner_right_diag(Move move) const;
    void switch_player();

public:
    Game();
    [[nodiscard]] std::string get_user_input() const;
    [[nodiscard]] GameResult get_result() const;
    [[nodiscard]] OptionalPlayer get_cur_player() const;
    [[nodiscard]] std::vector<std::vector<OptionalPlayer>> get_board() const;
    Move make_move(int row, int col);
    void check_winner(Move move);
};

}

#endif