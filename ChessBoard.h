// Define global constexpr
static constexpr int BLACK = 1;
static constexpr int WHITE = 0;
static constexpr int nrOfRanks = 8;
static constexpr int nrOfFiles = 8;
static constexpr int nrOfPawns = 2*nrOfFiles;
static constexpr int nrOfBishops = 4;
static constexpr int nrOfCastles = 4;
static constexpr int nrOfKnights = 4;
static constexpr int nrOfQueens = 2;
static constexpr int nrOfKings = 2;


// Define ChessBoard class 
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <vector>

using namespace std;

// Forward declarations
class Piece;
class Pawn;
class Bishop;
class Castle;
class Queen;
class King;
class Knight;

// ChessBoard Class
class ChessBoard{

  // Helper function that makes a move to the board (Piece* board[][]). 
  // Inputs: rank and file of starting position and destination position (origRank, origFile,
  // destRank, destFile) tempOrigin and tempDest are storing the origin and
  // destination pieces in case move needs to be reversed.
  void makeMove(int origRank, int origFile, int destRank, int destFile,
		Piece* &tempOrigin, Piece* &tempDest);

  // Helper function that undoes a move to the board (Piece* board[][]). 
  // Inputs: rank and file of starting position and destination position (origRank, origFile,
  // destRank, destFile) tempOrigin and tempDest are storing the origin and
  // destination pieces of previous move.
  void undoMove(int origRank, int origFile, int destRank, int destFile,
		Piece*  &tempOrigin, Piece* &tempDest);

  // Helper function which converts the string inputs of submit move and tests
  // their basic logic validity.
  // Inputs: rank and file of starting position and destination position (origRank, origFile,
  // destRank, destFile) and strings orig and dest which are inputs to submitMove. Returns
  // true if checks are passed, false otherwise.
  bool preMoveChecks(int &origRank, int &origFile, int &destRank, int &destFile,
		     string orig, string dest);

  // Helper function which checks whether provided rank and file are on the board. Returns
  // true if on the board, false otherwise.
  bool checkBounds(int Rank, int File);

  // Helper function which checks whether provided colour is in checkmate. Returns true if
  // in checkmate, false otherwise.
  bool checkMate(int colour);

  // Helper function which checks whether opposite of theprovided colour is in stalemate.
  // Returns true if in stalemate, false otherwise.
  bool staleMate(int colour);

  // Helper function which checks whether provided colour is in check. Returns true if
  // in check, false otherwise.
  bool isCheck(int colour);

 public:

  friend Piece; // Base class of all pieces friend declaration 
    
  int wKingC[2]; // Coordinates of the white king (rank and file)
  int bKingC[2]; // Coordinates of the white king (rank and file)
  int turn; // int which indicates whose turn it is to move (WHITE=0, BLACK=1)

  Piece* board[nrOfRanks][nrOfFiles]; // Chessboard: pointers to Piece objects
  
  vector<Pawn> pawnArray; // Vector holding the pawn objects
  vector<Bishop> bishopArray; // Vector holding bishop objects
  vector<Castle> castleArray; // Vector holding castle objects
  vector<Queen> queenArray; // Vector holding queen objects 
  vector<King> kingArray; // Vector holding king objects
  vector<Knight> knightArray; // Vector holding knight objects

  
  ChessBoard(); // ChessBoard constructor

  // Function which makes a move to the board if the move is valid. Input are two string
  // of length 2 which are the origin and destination of move respectively (going from "A1"
  // to "H8")
  void submitMove(string orig, string dest);
  
  // Function that resets the board to its starting configuration
  void resetBoard();  
  ~ChessBoard(); // Destructor
  
};

#endif
