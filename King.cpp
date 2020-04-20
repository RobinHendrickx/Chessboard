#include "King.h"
#include "ChessBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool King::validMove(int origRank, int origFile, int destRank, int destFile){

  if(!destinationCheck(destRank, destFile))
    return false;
  
  // Check if only moves 1 square
  if(max(abs(origRank-destRank),abs(origFile-destFile))>1){
    return false;
  }
  
  return true;
}

King::King(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

        
}

King::~King(){

}
