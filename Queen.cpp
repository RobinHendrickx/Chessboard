#include "Queen.h"
#include "ChessBoard.h"
#include <iostream>
#include <cstdlib>

using namespace std;

bool Queen::validMove(int origRank, int origFile, int destRank, int destFile){


  if(!destinationCheck(destRank, destFile))
    return false;
  
  
  // Check if moving in straight line
  if(origRank == destRank || origFile == destFile){

    // determine direction
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


  // Check if moving diagonally
  if(abs(origRank-destRank) == abs(origFile-destFile)){

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
    
  return false;
}

Queen::Queen(ChessBoard* cb, int colour, string id): Piece(cb, colour, id) {

}

Queen::~Queen(){

}

