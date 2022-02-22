#include <stdexcept>
#include <string>

#include "tictactoe/tictactoe.h"

namespace tictactoe {

using std::string;

Board::Board(const string& board) {
    if (Board::IsInvalidInput(board)) {
        throw std::invalid_argument("The string provided is not a valid board.");
    }
    // uniform any upper case in input string to lowercase
    string board_string;
    for (size_t i = 0; i < board.size(); i++) {
        board_string += tolower(board.at(i));
    }
    // fill in the 2d board array
    size_t index = 0;
    for (size_t i = 0; i < kBoardDimension; i++) {
        for (size_t j = 0; j < kBoardDimension; j++) {
            if (board_string.at(index) == kPlayerX) {
                board_array_[i][j] = kPlayerX;
            } else if (board_string.at(index) == kPlayerO) {
                board_array_[i][j] = kPlayerO;
            } else {
                board_array_[i][j] = ' ';
            }
            index++;
        }
    }
}

BoardState Board::EvaluateBoard() const {
    if (Board::IsUnreachableState()) {
        return BoardState::UnreachableState;
    } else if (Board::IsThereAWinner() && winner_ == kPlayerX) {
        return BoardState::Xwins;
    } else if (Board::IsThereAWinner() && winner_ == kPlayerO){
        return BoardState::Owins;
    }
    return BoardState::NoWinner;
}

bool Board::IsInvalidInput(const string& board_string) const {
    if (board_string.size() != kInputLength) {
        return true;
    }
    return false;
}

bool Board::IsUnreachableState() const {
    size_t x_count = 0;
    size_t o_count = 0;
    for (size_t i = 0; i < kBoardDimension; i++) {
        for (size_t j = 0; j < kBoardDimension; j++) {
            if (board_array_[i][j] == kPlayerX) {
                x_count++;
            } else if (board_array_[i][j] == kPlayerO) {
                o_count++;
            }
        }
    }
    if (o_count > x_count) {                                   // o starts
        return true;
    } else if (x_count - o_count > 1) {                        // x plays more than once
        return true;
    } else if (Board::IsThereAWinner() && winner_ == kPlayerX
        && x_count == o_count) {                               // x wins and o makes a move
        return true;
    } else if (Board::IsThereAWinner() && winner_ == kPlayerO
        && x_count > o_count) {                                // o wins but x makes a move
        return true;
    }
    return false;
}

bool Board::IsThereAWinner() const {
    if (Board::CheckDiagonalWinner() || Board::CheckRowWinner()
        || Board::CheckColumnWinner() || Board::CheckAntidiagonalWinner()) {
        return true;
    }
    return false;
}

bool Board::CheckColumnWinner() const {
    for (size_t col = 0; col < kBoardDimension; col++) {
        size_t count = 0;
        for (size_t row = 0; row < kBoardDimension - 1; row++) {
            if (board_array_[row][col] == board_array_[row + 1][col]) {
                count++;
            }
            if (count == kBoardDimension - 1) {
                winner_ = board_array_[row][col];
                return true;
            }
        }
    }
    return false;
}

bool Board::CheckRowWinner() const {
    for (size_t row = 0; row < kBoardDimension; row++) {
        size_t count = 0;
        for (size_t col = 0; col < kBoardDimension - 1; col++) {
            if (board_array_[row][col] == board_array_[row][col + 1]) {
                count++;
            }
            if (count == kBoardDimension - 1) {
                winner_ = board_array_[row][col];
                return true;
            }
        }
    }
    return false;
}

bool Board::CheckDiagonalWinner() const {
    size_t count = 0;
    for (size_t row = 0; row < kBoardDimension - 1; row++) {
        for (size_t col = 0; col < kBoardDimension - 1; col++) {
            if (row == col && (board_array_[row][col] == board_array_[row + 1][col + 1])) {
                count++;
            }
            if (count == kBoardDimension - 1) {
                winner_ = board_array_[row][col];
                return true;
            }
        }
    }
    return false;
}

bool Board::CheckAntidiagonalWinner() const {
    size_t count = 0;
    for (size_t row = 0; row < kBoardDimension; row++) {
        for (size_t col = 0; col < kBoardDimension; col++) {
            if ((row + col == kBoardDimension- 1)
                && (board_array_[row][col] == board_array_[row + 1][col - 1])) {
                count++;
            }
            if (count == kBoardDimension - 1) {
                winner_ = board_array_[row][col];
                return true;
            }
        }
    }
    return false;
}

}  // namespace tictactoe
