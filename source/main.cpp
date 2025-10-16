#include <iostream>
#include <chessGame.hpp>
using namespace std;
int main(){
  chessGame g(26);
  for (int i = 0; i < 5; i++){

    g.setChessPiece(5 - i, i + 5, BLACK);
    
  } 
  cout << g << g.isWin(BLACK);
  return 0;
}