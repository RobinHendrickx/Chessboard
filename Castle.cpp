#include "Castle.h"
#include "ChessBoard.h"
#include <iostream>

using namespace std;

bool Castle::validMove(int origRank, int origFile, int destRank, int destFile){

  if(!destinationCheck(destRank, destFile))
    return false;
   
  // Check if moving in straight line
  if(origRank != destRank && origFile != destFile)
    return false;

  // determine direction of move
  enum direction {north, east, south, west}; // enum for direction
  direction dir;
  
  if(destRank>origRank)
    dir = north;
  
  else if(destFile>origFile)
    dir = east;
  
  else if (destRank<origRank)
    dir = south;
  
  else
    dir = west;


  // Check if any pieces between the origin and the destination square
  switch(dir) {

    case(north):
    
      for (int i=1; i<destRank-origRank; i++){
	if(cb->board[destRank-i][destFile]!=nullptr)
	  return false;	
      }
      break;

    case(east):

      for (int i=1; i<destFile-origFile; i++){
	if(cb->board[destRank][destFile-i]!=nullptr)
	  return false;
      }
      break;
      
    case(south):

      for (int i=1; i<origRank-destRank; i++){
	if(cb->board[destRank+i][destFile]!=nullptr)
	  return false;
      }
      break;
      
    case(west):

      for (int i=1; i<origFile-destFile; i++){
	if(cb->board[destRank][destFile+i]!=nullptr)
	  return false;
      }
      break;
  }

  
  return true;
  
}

Castle::Castle(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

}

Castle::~Castle(){

}
