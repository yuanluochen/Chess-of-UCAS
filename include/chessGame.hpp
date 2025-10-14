#pragma once
class chessGame{
  private:
    struct chessBoard{
      int row;   // 行
      int col;   // 列
      int *data; // 棋盘数据
    } Board;
  public:
    chessGame(int row, int col){
      this->Board.row = row;
      this->Board.col = col;
      this->Board.data = new int[this->Board.row * this->Board.col];
    }
    ~chessGame(){
      delete [] this->Board.data;
    }
    
    //展示棋盘
    void displayBoard(){

    }


};