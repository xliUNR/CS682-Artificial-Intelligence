#ifndef _TICTAC_SUPPORT_H_
#define _TICTAC_SUPPORT_H_

#include <string>

/**
	load_board: loads a tic-tac-toe board state from a file

	args:
		std::string filename: file to read the board from

	returns (int):
		0: if file loaded OK
		-1: if file doesn't exist

**/


int load_board( std::string filename, int board[][3] );

/**
	save_board: saves a tic-tac-toe board state to a file

	args:
		std::string filename: file to write the board to

	returns (int):
		0: if file opened OK
		-1: if file can't be opened

**/


int save_board( std::string filename, int board[][3] );

#endif