#include <iostream>
#include "chessGame.hpp"
#include "decisionTree.hpp"
using namespace std;
int main(){
  // chessGame g(26);
  // for (int i = 0; i < 5; i++){
  //   g.setChessPiece(i, 5, BLACK);   
  // } 
  // cout << g << g.isWin(BLACK);

  graph<int> graph;
  int idx = graph.addNode(-1, 20);
  idx = graph.addNode(idx, 30);
  idx = graph.addNode(idx, 40);
  idx = graph.addNode(idx, 50);
  idx = graph.addNode(idx, 60);
  idx = graph.addNode(idx, 70);
  cout << graph;
  return 0;
}