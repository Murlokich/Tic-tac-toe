#ifndef GAME_LAUNCHER_H_
#define GAME_LAUNCHER_H_

#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <boost/filesystem.hpp>
#include <string>

#include "game.h"
#include "view.h"


#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

namespace tictactoe {

class GameLauncher {
private:
    boost::shared_ptr<tictactoe::View> view;
    Game &game;
    
public:
    GameLauncher(const std::string &view_name, Game &game_);

    void game_launch();
private:
    void change_view(const std::string &view_name);
};

} // tictactoe

#endif