#include <boost/config.hpp>
#include <limits>
#include <sstream>
#include "view.h"

namespace tictactoe {

class ViewCompact : View {
public:
    void display_board(const std::vector<std::vector<
                                    OptionalPlayer>> &board) const override {   
        if (prev_move_bad) {
            return;
        }
        std::cout << std::endl;
        for (int i = 0; i < static_cast<int>(board.size()); i++){
            for (int j = 0; j < static_cast<int>(board[0].size()); j++) {
                std::cout << static_cast<char>(board[i][j]);
            }
            std::cout << std::endl;
        }
    }

    // parse string 
    Command parseInput(const std::string &input) const {
        if (input.length() == 0) {
            return Command(CommandType::EXIT);
        }
        if (isChangeView(input)) {
            return Command({CommandType::CHANGE_VIEW, input});
        }
        std::stringstream lineStream(input);
        int row, col;
        if (lineStream >> row >> col) {
            if (!lineStream.eof()) {
                return Command(CommandType::INVALID);
            }
            if (row == -1 && col == -1) {
                return Command(CommandType::EXIT);
            }
            if (row >= 0 && row <= 9 && col >= 0 && col <= 9) {
                return Command(CommandType::MOVE, std::make_pair<>(row, col));
            }
        }
        return Command(CommandType::INVALID);
    }
};

extern "C" BOOST_SYMBOL_EXPORT ViewCompact view_compact;
ViewCompact view_compact;

} // namespace tictactoe