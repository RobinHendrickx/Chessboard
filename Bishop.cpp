#include "Bishop.h"
#include "ChessBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool Bishop::validMove(int origRank, int origFile, int destRank, int destFile){


  if(!destinationCheck(destRank, destFile))
    return false;
  
  // Check if moving diagonally
  if (abs(origRank-destRank) != abs(origFile-destFile))
    return false;
  

  // determine direction
  enum direction {northEast, southEast, southWest, northWest}; // enum for direction
  direction dir;
  
  if(destRank-origRank>0 && destFile-origFile>0)
    dir = northEast;
  
  else if(destRank-origRank<0 && destFile-origFile>0)
    dir = southEast;
  
  else if (destRank-origRank<0 && destFile-origFile<0)
    dir = southWest;
  
  else
    dir = northWest;



  // Check if any pieces between the origin and the destination square
  switch(dir) {

    case(northEast):
    
      for (int i=1; i<abs(origRank-destRank); i++){
	if(cb->board[destRank-i][destFile-i]!=nullptr)
	  return false;	
      }
      break;

    case(southEast):

      for (int i=1; i<abs(origRank-destRank); i++){
	if(cb->board[destRank+i][destFile-i]!=nullptr)
	  return false;
      }
      break;
      
    case(southWest):

      for (int i=1; i<abs(origRank-destRank); i++){
	if(cb->board[destRank+i][destFile+i]!=nullptr)
	  return false;
      }
      break;
      
    case(northWest):

      for (int i=1; i<abs(origRank-destRank); i++){
	if(cb->board[destRank-i][destFile+i]!=nullptr)
	  return false;
      }
      break;
  }
  
  return true;
    
}

Bishop::Bishop(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

}

Bishop::~Bishop(){

}
