#include "game.h"
#include "doctest.h"
#include <vector>

tictactoe::GameResult game_simulator(std::vector<std::pair<int,int>> moves) {
    tictactoe::Game game{};
    int counter = 0;
    while (game.get_result() == tictactoe::GameResult::undefined 
           && counter < static_cast<int>(moves.size())) {
        tictactoe::Move move = game.make_move(moves[counter].first, moves[counter].second);
        game.check_winner(move);
        counter++;
    }
    return game.get_result();
}

TEST_CASE("Fast horizontal win") {
    SUBCASE("only right, O wins"){
        std::vector<std::pair<int,int>> moves = {
            {0, 0}, {1, 0},
            {0, 1}, {1, 1},
            {0, 2}, {1, 2},
            {0, 3}, {1, 3},
            {0, 4}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("only left, O wins"){
        std::vector<std::pair<int,int>> moves = {
            {0, 9}, {1, 0},
            {0, 8}, {1, 1},
            {0, 7}, {1, 2},
            {0, 6}, {1, 3},
            {0, 5}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("both sides + X wins"){
        std::vector<std::pair<int,int>> moves = {
            {0, 9}, {1, 3},
            {0, 8}, {1, 2},
            {0, 7}, {1, 1},
            {0, 6}, {1, 5},
            {0, 0}, {1, 4}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::X_wins);
    }
}

TEST_CASE("Fast vertical win"){
    SUBCASE("only down, O wins") {
        std::vector<std::pair<int,int>> moves = {
                {0, 3}, {5, 4},
                {1, 3}, {6, 4},
                {2, 3}, {7, 4},
                {3, 3}, {8, 4},
                {4, 3}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("only up, X wins") {
        std::vector<std::pair<int,int>> moves = {
                {0, 0}, {9, 9},
                {1, 1}, {8, 9},
                {2, 2}, {7, 9},
                {3, 3}, {6, 9},
                {4, 9}, {5, 9}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::X_wins);
    }
    SUBCASE("both sides, O wins") {
        std::vector<std::pair<int,int>> moves = {
                {0, 2}, {1, 1},
                {4, 2}, {0, 0},
                {3, 2}, {7, 0},
                {1, 2}, {6, 0},
                {2, 2}, {5, 0}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
}

TEST_CASE("Fast left diagonal, O wins"){
    SUBCASE("only right down, O wins") {
        std::vector<std::pair<int,int>> moves = {
                {0, 0}, {5, 4},
                {1, 1}, {6, 4},
                {2, 2}, {7, 4},
                {3, 3}, {8, 4},
                {4, 4}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("only left up, X wins") {
        std::vector<std::pair<int,int>> moves = {
                {0, 0}, {9, 9},
                {1, 1}, {8, 8},
                {2, 2}, {7, 7},
                {3, 3}, {6, 6},
                {4, 9}, {5, 5}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::X_wins);
    }
    SUBCASE("both sides, O wins") {
        std::vector<std::pair<int,int>> moves = {
                {5, 5}, {1, 1},
                {2, 2}, {0, 0},
                {6, 6}, {7, 0},
                {3, 3}, {6, 0},
                {4, 4}, {5, 0}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
}

TEST_CASE("Fast right diagonal, O wins"){
    SUBCASE("only left down") {
        std::vector<std::pair<int,int>> moves = {
                {0, 7}, {5, 4},
                {1, 6}, {6, 4},
                {2, 5}, {7, 4},
                {3, 4}, {8, 4},
                {4, 3}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("only right up, O wins") {
        std::vector<std::pair<int,int>> moves = {
                {7, 0}, {9, 9},
                {6, 1}, {8, 8},
                {5, 2}, {7, 7},
                {4, 3}, {6, 6},
                {3, 4}, {5, 5}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
    SUBCASE("both sides") {
        std::vector<std::pair<int,int>> moves = {
                {8, 8}, {1, 1},
                {7, 7}, {0, 0},
                {6, 6}, {7, 0},
                {4, 4}, {6, 0},
                {5, 5}
        };
        tictactoe::GameResult res = game_simulator(moves);
        CHECK(res == tictactoe::GameResult::O_wins);
    }
}

TEST_CASE("Draw cases") {
    std::vector<std::pair<int,int>> moves =  {
        {0, 0}, {0, 1},
        {0, 3}, {0, 2}, 
        {0, 5}, {0, 4},
        {0, 6}, {0, 7}, 
        {0, 8}, {1, 1},
        {0, 9}, {1, 4},
        {1, 0}, {1, 5}, 
        {1, 2}, {1, 8}, 
        {1, 3}, {1, 9},
        {1, 6}, {2, 2},
        {1, 7}, {2, 3},
        {2, 0}, {2, 4},
        {2, 1}, {2, 6},
        {2, 5}, {2, 7},
        {3, 3}, {2, 8},
        {3, 5}, {2, 9},
        {3, 6}, {3, 0},
        {3, 8}, {3, 1},
        {4, 0}, {3, 2},
        {4, 1}, {3, 4},
        {4, 3}, {3, 7},
        {4, 4}, {3, 9},
        {4, 5}, {4, 2},
        {4, 8}, {4, 6},
        {4, 9}, {4, 7},
        {5, 0}, {5, 1},
        {5, 2}, {5, 3},
        {5, 5}, {5, 4},
        {5, 7}, {5, 6},
        {5, 8}, {6, 0},
        {5, 9}, {6, 1},
        {6, 4}, {6, 2},
        {6, 6}, {6, 3},
        {6, 7}, {6, 5},
        {6, 8}, {7, 1},
        {6, 9}, {7, 6},
        {7, 0}, {7, 7},
        {7, 2}, {7, 8},
        {7, 3}, {7, 9},
        {7, 4}, {8, 0},
        {7, 5}, {8, 1},
        {8, 3}, {8, 2},
        {8, 6}, {8, 4},
        {8, 7}, {8, 5},
        {9, 0}, {8, 8},
        {9, 1}, {8, 9},
        {9, 2}, {9, 3},
        {9, 4}, {9, 6},
        {9, 5}, {9, 7},
        {9, 8}, {9, 9}
    };
    tictactoe::GameResult res = game_simulator(moves);
    CHECK(res == tictactoe::GameResult::draw);
}


