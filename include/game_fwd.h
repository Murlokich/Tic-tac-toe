#ifndef GAME_FWD_H_
#define GAME_FWD_H_

#include <cassert>
#include <string>

namespace tictactoe {

class Game;
enum class OptionalPlayer : char {X = 'X', O = 'O', empty = '.'};
enum class GameResult{X_wins, O_wins, draw, undefined};
enum class CommandType{MOVE, EXIT, CHANGE_VIEW, INVALID};

class Command {
    const CommandType type;
    const std::string view_name;
    const std::pair<int,int> coordinates;

public:
    bool completed = false;


    Command(CommandType type_) : type(type_) {}
    Command(CommandType type_, const std::string &view_name_) : type(type_), 
                                                    view_name(view_name_) {}
    Command(CommandType type_, const std::pair<int,int> &coordinates_) : type(type_), 
                                                    coordinates(coordinates_) {}
    CommandType get_type() {
        return type;
    }

    std::pair<int,int> get_coordinates() {
        assert(type == CommandType::MOVE);
        return coordinates;
    }

    std::string get_view_name() {
        assert(type == CommandType::CHANGE_VIEW);
        return view_name;
    }
};

class Move{
    public:
        const int row, col;
        const OptionalPlayer player;
        const bool legal;
};

} // namespace tictactoe




#endif