#ifndef VIEW_H_
#define VIEW_H_

#include "game.h"

#include <boost/config.hpp>
#include <cassert>
#include <iostream>
#include <string>

namespace tictactoe {

class BOOST_SYMBOL_VISIBLE View {
protected:
    bool prev_move_bad = false; // to check if the board supposed to be shown
    bool isChangeView(const std::string &input) const {
        auto res = input.find("view_");
        return res != std::string::npos && res == 0; 
    }

public:
    inline void player_invitation(OptionalPlayer player) const {
        std::cout << static_cast<char>(player) << " move: ";
    }

    inline void winner_declaration(GameResult result) const {
        switch (result){
            case GameResult::O_wins:
                std::cout << "O wins!";
                break;
            case GameResult::X_wins:
                std::cout << "X wins!";
                break;
            case GameResult::draw:
                std::cout << "Draw.";
                break;
            case GameResult::undefined:
                assert(false && "WINNER DECLARATION WHEN GAME CONTINUES");
                break;
        }
        std::cout << std::endl;
    }

    inline void correct_command_completed() {
        prev_move_bad = false;
    }

    inline void bad_move_warning() {
        prev_move_bad = true;
        std::cout << "Bad move!" << std::endl;
    }

    virtual void display_board(const std::vector<std::vector<
                                        OptionalPlayer>> &board) const = 0;
    [[nodiscard]] virtual Command parseInput(const std::string &input) const = 0;
    virtual ~View() = default;
};

} // namespace tictactoe

#endif