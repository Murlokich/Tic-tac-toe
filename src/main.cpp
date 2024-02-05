#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include "game.h"
#include "game_launcher.h"

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif





int main(int argc, char* argv[]) {
    tictactoe::Game game_logic{};
    std::string view_name = "view_compact";
    if (argc > 1) {
        view_name = argv[1];
    }
    tictactoe::GameLauncher game_launcher(view_name, game_logic);
    game_launcher.game_launch();
}
