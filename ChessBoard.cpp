#include "ChessBoard.h"
#include "Pawn.h"
#include "Piece.h"
#include "Bishop.h"
#include "Castle.h"
#include "Queen.h"
#include "King.h"
#include "Knight.h"
#include <iostream>
#include <typeinfo>


void ChessBoard::makeMove(int origRank, int origFile, int destRank, int destFile,
			      Piece* &tempOrigin, Piece* &tempDest){

  // Make move and store original piece pointers
  tempOrigin = board[origRank][origFile];
  tempDest = board[destRank][destFile];	      
  board[destRank][destFile] = board[origRank][origFile];
  board[origRank][origFile] = nullptr;


  // Change king coordinates if it is king
  if(typeid(*tempOrigin) == typeid(kingArray[0])){
    if(tempOrigin->colour == WHITE){

      wKingC[0] = destRank;
      wKingC[1] = destFile;
    }
    
    if(tempOrigin->colour == BLACK){
      
      bKingC[0] = destRank;
      bKingC[1] = destFile;
    }
  }
}


void ChessBoard::undoMove(int origRank, int origFile, int destRank, int destFile,
			      Piece* &tempOrigin, Piece* &tempDest){

  // Reset position by using original piece pointers
  board[origRank][origFile] = tempOrigin;
  board[destRank][destFile] = tempDest;

  // reset king coords if it was king who moved
  if(typeid(*tempOrigin) == typeid(kingArray[0])){
 

    if(tempOrigin->colour == WHITE){
      wKingC[0] = origRank;
      wKingC[1] = origFile;
    }
    else{
      bKingC[0] = origRank;
      bKingC[1] = origFile;
    }
  }

  tempOrigin = nullptr;
  tempDest = nullptr;
}


bool ChessBoard::checkBounds(int Rank, int File){

  if (Rank < 0 || Rank > nrOfRanks-1  || File < 0 || File > nrOfFiles-1)
    return true;

  return false;
  
}


bool ChessBoard::preMoveChecks(int &origRank, int &origFile, int &destRank, int &destFile, string orig, string dest){

  // Check if input is correct length
  if(orig.size() != 2 || dest.size() != 2){
    cout << "Input values are not of correct length!\n";
    return false;
  }
  
  origFile = static_cast<int>(orig[0] - 'A');
  origRank = static_cast<int>(orig[1] - '1');				    
  destFile = static_cast<int>(dest[0] - 'A');
  destRank = static_cast<int>(dest[1] - '1');

  // check whether the bounds are valid
  if (checkBounds(destRank,destFile) || checkBounds(origRank, origFile)){
    cout << "Invalid bounds for move!\n";
    return false;
  }
  
  // check whether there is a piece at origin
  if (board[origRank][origFile] == nullptr){
    cout << "No piece at position "<< orig << "!\n";
    return false;
  }

  // check if it is their turn
  if (board[origRank][origFile]->colour!=turn){
    cout << "It is not ";
    cout << ((board[origRank][origFile]->colour == WHITE) ? "White's " : "Black's ");
    cout << "turn to move!\n";
    return false;
  }
  // Check if logically possible for piece to move to destination
  if(!board[origRank][origFile]->validMove(origRank, origFile,
					   destRank, destFile)){
    cout << ((board[origRank][origFile]->colour == WHITE) ? "White's " : "Black's ");
    cout << board[origRank][origFile]->id << " cannot move to " << dest << "!\n";
    return false;
  }

  return true;
}


bool ChessBoard::checkMate(int colour){

  Piece* tempOrigin = nullptr;
  Piece* tempDest = nullptr;
  
  // Loop through all pieces of same colour
  for (int i = 0; i< nrOfRanks; i++){
    for (int j = 0; j<nrOfFiles; j++){
      if(board[i][j] != nullptr && board[i][j]->colour == colour){

	// Loop through possible moves that can be made and see if king is still checked
	for (int k = 0; k< nrOfRanks; k++){
	  for (int l = 0; l<nrOfFiles; l++){
	    if(board[i][j]->validMove(i,j,k,l)){

	      makeMove(i,j,k,l,tempOrigin,tempDest);
	      
	      if(!isCheck(colour)){
      		undoMove(i,j,k,l,tempOrigin,tempDest);
		return false;
	      }
	     
	      undoMove(i,j,k,l,tempOrigin,tempDest);
	      
	    }	      
	  }
	}
      }
    }
  }

  return true;
  
}


bool ChessBoard::staleMate(int colour){
  
  Piece* tempOrigin = nullptr;
  Piece* tempDest = nullptr;

  // Loop through all pieces of other colour
  for (int i = 0; i< nrOfRanks; i++){
    for (int j = 0; j<nrOfFiles; j++){
      if(board[i][j] != nullptr && board[i][j]->colour != colour){

	// Loop through possible moves to check if they can be made
	// without checking its own king
	for (int k = 0; k< nrOfRanks; k++){
	  for (int l = 0; l<nrOfFiles; l++){
	    if(board[i][j]->validMove(i,j,k,l)){

	      makeMove(i,j,k,l,tempOrigin,tempDest);
	      
	      if(!isCheck(tempOrigin->colour)){
      		undoMove(i,j,k,l,tempOrigin,tempDest);
		return false;
	      }
	     
	      undoMove(i,j,k,l,tempOrigin,tempDest);

	    }	      
	  }
	}
      }
    }
  }

  return true;
  
}


bool ChessBoard::isCheck(int colour){

  // Loop through pieces of opposite colour and see if they check King
  for (int m = 0; m< nrOfRanks; m++){
    for (int n = 0; n<nrOfFiles; n++){
      if(board[m][n] != nullptr && board[m][n]->colour != colour){

	if(colour == WHITE)
	  if(board[m][n]->validMove(m,n,wKingC[0],wKingC[1]))
	    return true;

	if(colour == BLACK)
	  if(board[m][n]->validMove(m,n,bKingC[0],bKingC[1]))
	    return true;


      }
    }
  }
  
  return false;

}


ChessBoard::ChessBoard(){

  // Create the pawns
  pawnArray.reserve(nrOfPawns);
 
  for (int i=0; i<nrOfPawns/2; i++){
    
    pawnArray.insert(pawnArray.begin()+i,Pawn(this, WHITE, "Pawn"));
    pawnArray.emplace_back(this, BLACK, "Pawn");

  }

  // Create the Bishops
  bishopArray.reserve(nrOfBishops);

  for (int i=0; i<nrOfBishops/2; i++){
    
    bishopArray.insert(bishopArray.begin()+i,Bishop(this, WHITE, "Bishop"));
    bishopArray.emplace_back(this, BLACK, "Bishop");

  }
  
  //Create the Castles
  castleArray.reserve(nrOfCastles);

    for (int i=0; i<nrOfCastles/2; i++){
    
    castleArray.insert(castleArray.begin()+i,Castle(this, WHITE, "Castle"));
    castleArray.emplace_back(this, BLACK, "Castle");

  }

  //Create the Knights
  knightArray.reserve(nrOfKnights);
  
  
    for (int i=0; i<nrOfKnights/2; i++){
    
    knightArray.insert(knightArray.begin()+i,Knight(this, WHITE, "Knight"));
    knightArray.emplace_back(this, BLACK, "Knight");

    }
  
  //Create the Queens
  queenArray.reserve(nrOfQueens);

  queenArray.emplace_back(this, WHITE, "Queen");
  queenArray.emplace_back(this, BLACK, "Queen");

  // Create the kings
  kingArray.reserve(nrOfKings);

  kingArray.emplace_back(this, WHITE, "King");
  kingArray.emplace_back(this, BLACK, "King");
  
  
  resetBoard();
  
  
  }

ChessBoard::~ChessBoard(){

};

void ChessBoard::resetBoard(){

  // Place all the zeros 
  for (int i = 2; i < nrOfRanks-2; i++){
    for (int j = 0; j < nrOfFiles; j++){
      
      board[i][j] = nullptr;

    }
  }

  // Place pawns
  for(int i = 0; i < nrOfPawns/2; i++){
    
    board[1][i] = &pawnArray[i];
    board[nrOfRanks-2][i] = &pawnArray[nrOfFiles+i];
  }
  
  // Place bishops
  board[0][2] = &bishopArray[0];
  board[0][5] = &bishopArray[1];
  board[nrOfRanks-1][2] = &bishopArray[2];
  board[nrOfRanks-1][5] = &bishopArray[3];

  // Place castles
  board[0][0] = &castleArray[0];
  board[0][nrOfFiles-1] = &castleArray[1];
  board[nrOfRanks-1][0] = &castleArray[2];
  board[nrOfRanks-1][nrOfFiles-1] = &castleArray[3];

  // Place knights
  board[0][1] = &knightArray[0];
  board[0][nrOfFiles-2] = &knightArray[1];
  board[nrOfRanks-1][1] = &knightArray[2];
  board[nrOfRanks-1][nrOfFiles-2] = &knightArray[3];

  // Place queens
  board[0][3] = &queenArray[0];
  board[nrOfRanks-1][3] = &queenArray[1];
  
  // Place kings
  board[0][4] = &kingArray[0];
  board[nrOfRanks-1][4] = &kingArray[1];

  wKingC[0] = 0;
  wKingC[1] = 4;
  bKingC[0] = nrOfRanks-1;
  bKingC[1] = 4;
  
  
  turn = WHITE;

  cout << "A new chess game is started!\n";
}


void ChessBoard::submitMove(string orig, string dest){

  int origRank, origFile, destRank, destFile;
 
  if(!preMoveChecks(origRank, origFile, destRank, destFile, orig, dest))
    return;
  
  // temporarily make move. Store the destination pointer in a temporary variable since
  // This is the one that will temporarily be overwritten
  Piece* tempOrigin = nullptr;
  Piece* tempDest = nullptr;
  bool wKingCheck = false;
  bool bKingCheck = false;
  
  makeMove(origRank,origFile,destRank,destFile,tempOrigin,tempDest);
  
  // Check if the move is checking its own king, reset if so 
  if(isCheck(tempOrigin->colour)){

    cout << "Invalid move. " << ((tempOrigin->colour == WHITE) ? "White" : "Black");
    cout << " would check itself by moving its " << tempOrigin->id;
    cout << " to " << dest << "!\n";
    undoMove(origRank,origFile,destRank,destFile,tempOrigin,tempDest);
    return;
  }

  // Print out move
  cout << ((tempOrigin->colour == WHITE) ? "White's " : "Black's ");
  cout << tempOrigin->id << " moved from " << orig << " to " << dest;
  if (tempDest != nullptr){
    cout << " taking " << ((tempDest->colour == WHITE) ? "White's " : "Black's ");
    cout << tempDest->id;
  }
  cout << endl;


  // Check if move checks the opponents king
  if(board[destRank][destFile]->validMove(destRank,destFile,bKingC[0],bKingC[1])){
    bKingCheck = true;
  }

  if(board[destRank][destFile]->validMove(destRank,destFile,wKingC[0],wKingC[1])){
    wKingCheck = true;
  }
  
  
  // Check for checkmate, check and stalemate
  if(wKingCheck && checkMate(WHITE))
    cout << "White is in checkmate\n";
  
  else if(wKingCheck)
    cout << "White is in check\n";
  
  else if(bKingCheck && checkMate(BLACK))
    cout << "Black is in checkmate\n";

  else if (bKingCheck)
    cout << "Black is in check\n";
  
  
  else if (staleMate(board[destRank][destFile]->colour)){
    cout << ((tempOrigin->colour == WHITE) ? "Black " : "White ");
    cout << "is in stalemate\n";
  }

  // Change turn
  switch(turn){
      
    case WHITE: turn = BLACK; break;
    case BLACK: turn = WHITE; break;

  }
}

