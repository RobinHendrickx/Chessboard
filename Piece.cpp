#include "Piece.h"
#include "ChessBoard.h"

Piece::Piece(ChessBoard* cb, int colour, string id): cb(cb), colour(colour), id(id){

}

Piece::~Piece(){

}


bool Piece::destinationCheck(int destRank, int destFile){

  if (cb->board[destRank][destFile] != nullptr &&
      cb->board[destRank][destFile]->colour == colour)
    return false;

  return true;
}
