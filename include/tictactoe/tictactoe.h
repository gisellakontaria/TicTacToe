#pragma once

#include <string>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  static constexpr int kBoardDimension = 3;
  static constexpr int kInputLength = kBoardDimension * kBoardDimension;
  static constexpr char kPlayerX = 'x';
  static constexpr char kPlayerO = 'o';
  mutable char winner_;
  char board_array_[kBoardDimension][kBoardDimension];

  /***
   * Function that determines if a board is reachable
   * @return true if board is unreachable
   */
  bool IsUnreachableState() const;

  /***
   * Function that determines input board string is valid
   * @param board_string represents the board
   * @return true if the input is not of valid length
   */
  bool IsInvalidInput(const std::string& board_string) const;

  /***
   * Function that determines a player has won
   * @return true if there exists a winner in the board
   */
  bool IsThereAWinner() const;

  /***
   * Function that checks if there exists a winner in any of the rows
   * @return true if a player has won horizontally
   */
  bool CheckRowWinner() const;

  /***
   * Function that checks if there exists a winner in its diagonal
   * @return true if a player has won diagonally
   */
  bool CheckDiagonalWinner() const;

  /***
   * Function that checks if there exists a winner in any of the columns
   * @return true if a player has won vertically
   */
  bool CheckColumnWinner() const;

  /***
   * Function that checks if there exists a winner in its antidiagonal
   * @return true if a player has won antidiagonally
   */
  bool CheckAntidiagonalWinner() const;
};

}  // namespace tictactoe
