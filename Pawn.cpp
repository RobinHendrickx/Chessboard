#include "Pawn.h"
#include "ChessBoard.h"
#include <iostream>

bool Pawn::validMove(int origRank, int origFile, int destRank, int destFile){

  
  if(!destinationCheck(destRank, destFile))
    return false;
  
  if (colour == WHITE){
    // Can put one step forward if no piece in front
    if (origFile == destFile && destRank == origRank+1){
      if(cb->board[destRank][destFile] == nullptr)
	return true;
    }
  
    // Can go two steps if it is original position
    if(origFile == destFile && origRank == 1 && destRank == origRank+2){ 
      if(cb->board[destRank][destFile] == nullptr && cb->board[destRank-1][destFile] == nullptr)
	return true;
    }  
    // Can go diagonal if there is a opponent piece
    if((destFile == origFile-1 || destFile == origFile+1) && destRank == origRank+1){
      if(cb->board[destRank][destFile] != nullptr)
	return true;
      
    }
  }
    
  else if (colour == BLACK){

    // Can put one step forward if no piece in front
    if (origFile == destFile && destRank == origRank-1){
      if(cb->board[destRank][destFile] == nullptr)
	return true;
    }
  
    // Can go two steps if it is original position
    // Replace with a global constant! (both color and origRank)
    if(origFile == destFile && destRank == origRank-2 && origRank == 6){
      if(cb->board[destRank][destFile] == nullptr && cb->board[destRank+1][destFile] == nullptr)
	return true;
    }  
    // Can go diagonal if there is a opponent piece
    if((destFile == origFile-1 || destFile == origFile+1) && destRank == origRank-1){
      if(cb->board[destRank][destFile] != nullptr)
	return true;
    }
  }

  return false;
  
}

Pawn::Pawn(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

}

Pawn::~Pawn(){

}
