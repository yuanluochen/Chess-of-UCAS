#pragma once
#include <vector>

enum chessType { 
  BLACK = 1, 
  WRITE = -1, 
  VOID = 0 
};
class chessPiece {
private:
  // 类型
  chessType type;
  // 位置
  struct {
    int row;
    int col;
  } pos;

public:
  chessPiece(chessType type, int rowPos, int colPos)
      : type(type), 
        pos({
          rowPos, 
          colPos
        }) {};
};

class chessGame {
private:
  // 棋盘
  struct {
    int row;   // 行
    int col;   // 列
    int *data; // 棋盘数据
  } chessBoard;
  // 棋子历史数据
  std::vector<chessPiece> chessPieces;
public:
  chessGame(int row, int col) : chessBoard({row, col}) {
    // 初始化并且清空棋盘
    this->chessBoard.data =
        new int[this->chessBoard.row * this->chessBoard.col]{};
  }
  ~chessGame() { delete[] this->chessBoard.data; }

  // 显示棋盘数据
  void displayBoard() const;
};
