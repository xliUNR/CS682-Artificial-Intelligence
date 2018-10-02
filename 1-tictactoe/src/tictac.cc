#include <stdio.h>
#include <iostream>
#include <tictac_support.h>

int main( int argc, char* argv[] )
{

	int board[3][3], move[3][3];
   int gameState = 0;
	// load in current board state
	load_board( argv[1], board );

	// make move
   while( gameState == 0 ){
	  gameState =  make_move( board );

   }

	
	// save board state
	save_board( argv[2], board );

	return 0;
}
