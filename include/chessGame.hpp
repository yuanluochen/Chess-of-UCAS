#pragma once
#include <iostream>
#include <ostream>
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
  friend std::ostream & operator<<(std::ostream & os, const chessGame & chess);
  //获取对应位置的棋子数值
  int getChessPieceVal(int row, int col) const;
  //设置棋子位置
  bool setChessPiece(int row, int col, chessType chtype);
};
