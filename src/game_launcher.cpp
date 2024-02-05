#include "game_launcher.h"
#include <iostream>

namespace tictactoe {
    GameLauncher::GameLauncher(const std::string &view_name, Game &game_) : game(game_) {
        change_view(view_name);
    }

    void GameLauncher::change_view(const std::string &view_name) {
        boost::filesystem::path path = boost::filesystem::current_path();
        view = boost_dll_import_symbol<tictactoe::View>(path / view_name, 
                            view_name, boost::dll::load_mode::append_decorations);
    }

    void GameLauncher::game_launch() {
        view->display_board(game.get_board());
        while (game.get_result() == GameResult::undefined) {
            while (true) {
                view->player_invitation(game.get_cur_player());
                std::string line;
                std::getline(std::cin, line);
                Command command = view->parseInput(line);

                switch (command.get_type()) {
                    case CommandType::EXIT :
                        return;
                    case CommandType::MOVE :
                        {
                            auto [row, col] = command.get_coordinates();
                            Move move = game.make_move(row, col);
                            if (move.legal) {
                                command.completed = true;
                                game.check_winner(move);
                            }
                            else {
                                view->bad_move_warning();
                            }
                            break;
                        }
                    case CommandType::CHANGE_VIEW :
                        change_view(command.get_view_name());
                        command.completed = true;
                        break;
                    case CommandType::INVALID :
                        view->bad_move_warning();
                        break;
                }
                if (command.completed) {
                    view->correct_command_completed();
                    view->display_board(game.get_board());
                    break;
                }
            }   
        }
        view->winner_declaration(game.get_result());
    }
} // namespace tictactoe