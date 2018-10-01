#include <tictac_support.h>
#include <stdio.h>
/**
	make_move: takes a board state and makes a legal 
	(hopefully optimal) move

	args:
		int [][3] board: 3x3 array of ints representing the 
		board state. The values of board are altered based
		on the move
			0: empty
			1: x
		 -1: o
		
	returns (int):
		the number of steps it took to choose the best move
		(current implementation returns 1 by default, 0 if no move made)
**/

int make_move( int board[][3] )
{
	// figure out what move it is
	int state = 0;
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];

	state = -state;
	if( state == 0 )
		state = 1;

	// default behavior: find any unoccupied square and make the move
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			// find an empty square
			if( board[i][j] == 0 )
			{
				// that's the move
				printf( "player [%d] made move: [%d,%d]\n", state, i, j );
				board[i][j] = state;
				return 1;
			}
	
	// no move was made (board was full)
	return 0;
}

int make_move( int board[][3] )
{
	// figure out what move it is
	int state = 0;
    //variables for sum of rows, columns, and diagonals.
    int r1, r2, r3, c1, c2, c3, dL, dR;
    int winCon = -2;
    int pieceVal = -1;
    int tempBoard[3][3];
    int movesList[3][3];
    int movesInitVal = 3;
    int emptyCtr;
    int optRow, optCol;
    int optVal;
    //initialize matrices on heap
    /*int** tempBoard = new int*[3];
    int** movesList = new int*[3];
    for( int i = 0; i < 3; i++ ){
      tempBoard[i] = new int[3];
      movesList = new int[3];
    }*/

    //loop over board to determine whose turn it is
	for( int i = 0; i < 3; i++ )
		for( int j = 0; j < 3; j++ )
			state += board[i][j];
    
    if( state == 0 ){
        winCon = 2;
        pieceVal = 1;
        movesInitVal = -3;
    }

    //calculate values of rows, columns, and diagonals
    r1 = board[0][0] + board[0][1] + board[0][2];
    r2 = board[1][0] + board[1][1] + board[1][2];
    r3 = board[2][0] + board[2][1] + board[2][2];  
    c1 = board[0][0] + board[1][0] + board[1][0];
    c2 = board[0][1] + board[1][1] + board[2][1];
    c3 = board[0][2] + board[1][2] + board[2][2];
    dL = board[0][0] + board[1][1] + board[2][2];
    dR = board[0][2] + board[1][1] + board[2][0];

    //check to see if instant win is possible before running minimax
    if( r1 == winCon ){
        //see which one is empty and place piece there.
        for( int i = 0; i < 3; i++){
            if( board[0][i] == 0 )
                board[0][i] == pieceVal;
            return pieceVal; 
        }
    } 

    else if( r2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[1][i] == 0 )
                board[1][i] == pieceVal;
            return pieceVal; 
        }
    }

    else if( r3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[2][i] == 0 )
                board[2][i] == pieceVal;
            return pieceVal; 
        }
    }

    else if( c1 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][0] == 0 )
                board[i][0] == pieceVal;
            return pieceVal; 
        }
    }
    else if( c2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][1] == 0 )
                board[i][1] == pieceVal;
            return pieceVal; 
        }
    }
    else if( c3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][2] == 0 )
                board[i][2] == pieceVal;
            return pieceVal; 
        }
    }
    else if( dL == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][i] == 0 )
                board[i][i] == pieceVal;
            return pieceVal; 
        }
    }
    else if( dR == winCon ){
        if( board[0][2] == 0 ){
            board[0][2] == pieceVal;
            return pieceVal;
        }
        else if( board[1][1] == 0 ){
            board[1][1] == pieceVal;
            return pieceVal;
        }
        else{
            board[2][0] = pieceVal;
            return pieceVal;
        }
    }
    //If no win con available, check for empty spots on board
    else{ 
           //first copy board into temp board
           for( int i = 0; i < 3; i++ ){
               for( int j = 0; j < 3; j++ ){
                  tempBoard[i][j] = board[i][j];
               }
            }
           //intialize counter for number of empty spots
           emptyCtr = 0; 
           //loop over all empty spots, test outcome of each          
           for( int i = 0; i < 3; i++ ){
               for( int j = 0; j < 3; j++ ){
                  //Or copy tempBoard from board @ each iteration?
                  //initialize movesList
                  movesList[i][j] = movesInitVal;
                  if( tempBoard[i][j] == 0 ){
                     tempBoard[i][j] = pieceVal;
                     //store values of each move into matrix
                     movesList[i][j] = make_move( tempBoard );
                     emptyCtr++;
                     //recopy board here?
                     tempBoard[i][j] == 0;
                  }
               }
            }
            //if no spots on board return 0 for tie
            if ( emptyCtr == 0 )
               return 0;

            //figure out the max or min depending on whose turn
            optVal = movesList[0][0];
            optRow = 0;
            optCol = 0;
            //if x turn, then find Max
            if( state == 0 ){
            /*for( int k = 1; k < 9; k++ ){
               if( optVal < movesList[k] ){
                     optVal = movesList[k];
                           optIndex = k;
               }
            }*/
               for( int k = 0; k < 3; k++ ){
                  for( int l = 0; l < 3; l++ ){
                     if( optVal < movesList[k][l] ){
                        optVal = movesList[k][l];
                        optRow = k;
                        optCol = l;
                     }
                  }
               } 
            }
            //Otherwise it is O turn so look for min
            else{
               for( int k = 0; k < 3; k++ ){
                  for( int l = 0; l < 3; l++ ){
                     if( optVal > movesList[k][l] ){
                        optVal = movesList[k][l];
                        optRow = k;
                        optCol = l;
                     }
                  }
               } 
            }
         board[optRow][optCol] = pieceVal;
         return optVal; 
    }
}


int make_moveHelper( board[][] ){

}

int checkWin( board[][], int turn ){
   int r1, r2, r3, c1, c2, c3, dL, dR;
   int winCon = -2;
   int pieceVal = -1;
   //if turn = 0, then it is x turn
   if( turn == 0 ){
      winCon = 2;
      pieceVal = 1;
   }
   //calculate values of rows, columns, and diagonals
    r1 = board[0][0] + board[0][1] + board[0][2];
    r2 = board[1][0] + board[1][1] + board[1][2];
    r3 = board[2][0] + board[2][1] + board[2][2];  
    c1 = board[0][0] + board[1][0] + board[1][0];
    c2 = board[0][1] + board[1][1] + board[2][1];
    c3 = board[0][2] + board[1][2] + board[2][2];
    dL = board[0][0] + board[1][1] + board[2][2];
    dR = board[0][2] + board[1][1] + board[2][0];

   //check for win conditions
   if( r1 == winCon ){
        //see which one is empty and place piece there.
        for( int i = 0; i < 3; i++){
            if( board[0][i] == 0 )
                board[0][i] == pieceVal;
            return pieceVal; 
        }
    } 

    else if( r2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[1][i] == 0 )
                board[1][i] == pieceVal;
            return pieceVal; 
        }
    }

    else if( r3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[2][i] == 0 )
                board[2][i] == pieceVal;
            return pieceVal; 
        }
    }

    else if( c1 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][0] == 0 )
                board[i][0] == pieceVal;
            return pieceVal; 
        }
    }
    else if( c2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][1] == 0 )
                board[i][1] == pieceVal;
            return pieceVal; 
        }
    }
    else if( c3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][2] == 0 )
                board[i][2] == pieceVal;
            return pieceVal; 
        }
    }
    else if( dL == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][i] == 0 )
                board[i][i] == pieceVal;
            return pieceVal; 
        }
    }
    else if( dR == winCon ){
        if( board[0][2] == 0 ){
            board[0][2] == pieceVal;
            return pieceVal;
        }
        else if( board[1][1] == 0 ){
            board[1][1] == pieceVal;
            return pieceVal;
        }
        else{
            board[2][0] = pieceVal;
            return pieceVal;
        }
    }
    //If no win conditions found, return 0
    else{
      return 0;
    }

}

