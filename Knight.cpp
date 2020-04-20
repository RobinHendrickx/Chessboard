#include "Knight.h"
#include "ChessBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool Knight::validMove(int origRank, int origFile, int destRank, int destFile){

  if(!destinationCheck(destRank, destFile))
    return false;

  if(abs(origRank-destRank)==1 && abs(origFile-destFile)==2)
    return true;

  else if(abs(origRank-destRank)==2 && abs(origFile-destFile)==1)
    return true;

  return false;

}

Knight::Knight(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

}

Knight::~Knight(){

}
