cmake_minimum_required(VERSION 3.10)

project(tic-tac-toe CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(../../default-options.cmake)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)  # Recommended by Boost.DLL's manual

find_package(Boost 1.82 COMPONENTS filesystem system REQUIRED)  # Required by Boost.DLL
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

include_directories(include)

add_executable(tic-tac-toe src/game.cpp src/game_launcher.cpp src/main.cpp)
target_link_libraries(tic-tac-toe ${Boost_LIBRARIES} ${CMAKE_DL_LIBS})

add_library(view_compact SHARED src/view_compact.cpp src/game.cpp)
add_library(view_pretty SHARED src/view_pretty.cpp src/game.cpp)