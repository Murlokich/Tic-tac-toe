#include <boost/config.hpp>
#include <sstream>
#include "view.h"

namespace tictactoe {

class ViewPretty : View {
public:

    Command parseInput([[maybe_unused]]const std::string &input) const {
        if (input.length() == 0) {
            return Command(CommandType::EXIT);
        }
        if (isChangeView(input)) {
            return Command({CommandType::CHANGE_VIEW, input});
        }
        std::stringstream lineStream(input);
        int row;
        char col_ch;
        lineStream >> std::noskipws;
        if (lineStream >> col_ch >> row) {
            if (!lineStream.eof()) {
                return Command(CommandType::INVALID);
            }
            if (row >= 0 && row <= 9 && col_ch >= 'a' && col_ch <= 'j') {
                int col = col_ch - 'a';
                return Command(CommandType::MOVE, std::make_pair<>(9 - row, col));
            }
        }
        return Command(CommandType::INVALID);
    }

    void display_board(const std::vector<std::vector<
                                    OptionalPlayer>> &board) const override {
        if (prev_move_bad) {
            return;
        }
        std::cout << std::endl;
        for (int i = 9; i >= 0; i--){
            print_horizontal_wall();
            print_row(board, i);
        }
        print_horizontal_wall();
        print_columns_names();
    }
private: 
    void print_horizontal_wall() const {
        std::cout << "  ";
        for (int i = 0; i < 10; i++) {
            std::cout << "+----";
        }
        std::cout << "+" << std::endl;
    }
    
    void print_row(const std::vector<std::vector<
                                    OptionalPlayer>> &board, int row) const {
        std::cout << row << " ";
        row = 9 - row;
        for (int j = 0; j < 10; j++) {
            std::cout << "|";
            OptionalPlayer cell = board[row][j];
            switch (cell) {
                case OptionalPlayer::empty:
                    std::cout << "    ";
                    break;
                case OptionalPlayer::O:
                    std::cout << " @@ ";
                    break;
                case OptionalPlayer::X:
                    std::cout << " \\/ ";
                    break;
            }
        }
        std::cout << "|" << std::endl << "  ";

        for (int j = 0; j < 10; j++) {
            std::cout << "|";
            OptionalPlayer cell = board[row][j];
            switch (cell) {
                case OptionalPlayer::empty:
                    std::cout << "    ";
                    break;
                case OptionalPlayer::O:
                    std::cout << " @@ ";
                    break;
                case OptionalPlayer::X:
                    std::cout << " /\\ ";
                    break;
            }
        }
        std::cout << "|" << std::endl;
    }

    void print_columns_names() const {
        std::cout << "  ";
        for (char col = 'a'; col <= 'j'; col++) {
            std::cout << "  " << col << "  ";
        }
        std::cout << " " << std::endl;
    }
};

extern "C" BOOST_SYMBOL_VISIBLE ViewPretty view_pretty;
ViewPretty view_pretty;

} // namespace tictactoe