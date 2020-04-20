#ifndef PIECE_H
#define PIECE_H

#include <string>

using namespace std;

class ChessBoard;

// Piece class (base class for all chess pieces)
class Piece{

 public:
  
  ChessBoard* cb; // Pointer to chessboard 
  int colour; // Colour of the piece (WHITE = 0 & BLACK = 1)
  string id; // Name of the piece 

  // Function which checks whether a proposed move is valid. Takes as an input the rank and file
  // of both the original position of the piece (origin) and the proposed position (destination) 
  virtual bool validMove(int origRank, int origFile, int destRank, int destFile) = 0;
 
  // Function that checks whether the destination taken as input holds either no piece
  // or a piece of the opposite colour. Returns true if so, false otherwise.
  bool destinationCheck(int destRank, int destFile); 

  // Constructor. Takes as input a pointer to the chessboard, an integer specifying colour of
  // the piece (WHITE = 0 & BLACK = 1) and a string specifying the name of the piece
  Piece(ChessBoard* cb, int colour, string id);

  // Destructor
  virtual ~Piece();
  
};
#endif

