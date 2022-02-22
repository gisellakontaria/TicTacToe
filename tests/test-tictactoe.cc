#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
    SECTION("String is too short") {
        REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
    }
    SECTION("String is too long") {
        REQUIRE_THROWS_AS(Board("xxooo.,/';0"), std::invalid_argument);
    }
    SECTION("String is empty") {
        REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
    }
}

TEST_CASE("Boards with no winner") {
    SECTION("Full board with no winner") {
        REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
    }

    SECTION("Empty board with no winner") {
        REQUIRE(Board(".lRw.134[").EvaluateBoard() == BoardState::NoWinner);
    }

    SECTION("Game still in progress, X moved last") {
        REQUIRE(Board("O...X.X..").EvaluateBoard() == BoardState::NoWinner);

    }

    SECTION("Game still in progress, O moved last") {
        REQUIRE(Board("O...X.X.o").EvaluateBoard() == BoardState::NoWinner);
    }
}

TEST_CASE("Unreachable boards") {
    SECTION("O moved first so numO > numX") {
        REQUIRE(Board("xxoooXXoo").EvaluateBoard() == BoardState::UnreachableState);
    }

    SECTION("X moved more than once so numX > numO + 1") {
        REQUIRE(Board("XxXxXxXoX").EvaluateBoard() == BoardState::UnreachableState);
    }

    SECTION("numX == numO when X has won") {
        REQUIRE(Board("xxxOO.o..").EvaluateBoard() == BoardState::UnreachableState);
    }

    SECTION("numX == numO + 1 when O has won") {
        REQUIRE(Board("oooxx/xx/").EvaluateBoard() == BoardState::UnreachableState);
    }
}

TEST_CASE("Boards with X as the winner") {
    SECTION("X wins vertically") {
        REQUIRE(Board("oxo,x-*x'").EvaluateBoard() == BoardState::Xwins);
    }

    SECTION("X wins horizontally") {
        REQUIRE(Board("xxx...oo.").EvaluateBoard() == BoardState::Xwins);
    }

    SECTION("X wins diagonally") {
        REQUIRE(Board("XOXOXO..X").EvaluateBoard() == BoardState::Xwins);
    }

    SECTION("X wins antidiagonally") {
        REQUIRE(Board("OXXOXOX..").EvaluateBoard() == BoardState::Xwins);
    }

    SECTION("X wins with two three-in-a-rows") {
        REQUIRE(Board("xoxoXOXOX").EvaluateBoard() == BoardState::Xwins);
    }
}

TEST_CASE("Boards with O as the winner") {
    SECTION("O wins vertically") {
        REQUIRE(Board("OXooXxO;x").EvaluateBoard() == BoardState::Owins);
    }

    SECTION("O wins horizontally") {
        REQUIRE(Board("XX-xdfooo").EvaluateBoard() == BoardState::Owins);
    }

    SECTION("O wins diagonally") {
        REQUIRE(Board("oxxxo+oXO").EvaluateBoard() == BoardState::Owins);
    }

    SECTION("O wins antidiagonally") {
        REQUIRE(Board("axoxoboxc").EvaluateBoard() == BoardState::Owins);
    }
}