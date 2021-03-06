#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class ChessBoard;

class Bishop : public Piece{

 public:

  // Function which checks whether a proposed move is valid. Takes as an input the rank and file
  // of both the original position of the piece (origin) and the proposed position (destination) 
  bool validMove(int origRank, int origFile, int destRank, int destFile) override;

  // Constructor. Takes as input a pointer to the chessboard, an integer specifying colour of
  // the piece (WHITE = 0 & BLACK = 1) and a string specifying the name of the piece
  Bishop(ChessBoard* cb, int colour, string id);

  // Destructor
  ~Bishop();


};

#endif
