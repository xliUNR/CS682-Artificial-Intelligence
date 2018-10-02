#include <tictac_support.h>
#include <stdio.h>
#include <iostream>
//free function declaration
int minimaxHelper( int board[][3], int turn );

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

/*int make_move( int board[][3] )
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
}*/

int make_move( int board[][3] )
{
	  //variable to store game state (whose turn it is)
	  int state = 0;
    //variables for sum of rows, columns, and diagonals.
    int r1, r2, r3, c1, c2, c3, dL, dR;
    int winCon = -2;
    int pieceVal = -1;
    int nextTurn = 0;
    int gameOver = -100;
    int tieGame = 101;
    //int tempBoard[3][3];
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
    //std::cout << state << ' ';
    //If state = 0, means it is X turn
    if( state == 0 ){
        winCon = 2;
        pieceVal = 1;
        movesInitVal = -3;
        gameOver = 100;
        nextTurn = -1;
    }

    //calculate values of rows, columns, and diagonals to check for next move
    //wins
    r1 = board[0][0] + board[0][1] + board[0][2];
    r2 = board[1][0] + board[1][1] + board[1][2];
    r3 = board[2][0] + board[2][1] + board[2][2];  
    c1 = board[0][0] + board[1][0] + board[2][0];
    c2 = board[0][1] + board[1][1] + board[2][1];
    c3 = board[0][2] + board[1][2] + board[2][2];
    dL = board[0][0] + board[1][1] + board[2][2];
    dR = board[0][2] + board[1][1] + board[2][0];
    //std::cout << r1 << ' ' << r2 << ' ' << r3 << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << dL << ' ' << dR << std::endl;
    //check to see if instant win is possible before running minimax
    if( r1 == winCon ){
        //see which one is empty and place piece there.
        for( int i = 0; i < 3; i++){
            if( board[0][i] == 0 )
                board[0][i] == pieceVal;
            return gameOver; 
        }
    } 

    else if( r2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[1][i] == 0 )
                board[1][i] == pieceVal;
            return gameOver; 
        }
    }

    else if( r3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[2][i] == 0 )
                board[2][i] == pieceVal;
            return gameOver; 
        }
    }

    else if( c1 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][0] == 0 )
                board[i][0] == pieceVal;
            return gameOver; 
        }
    }
    else if( c2 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][1] == 0 )
                board[i][1] == pieceVal;
            return gameOver; 
        }
    }
    else if( c3 == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][2] == 0 )
                board[i][2] == pieceVal;
            return gameOver; 
        }
    }
    else if( dL == winCon ){
        for( int i = 0; i < 3; i++ ){
            if( board[i][i] == 0 )
                board[i][i] == pieceVal;
            return gameOver; 
        }
    }
    else if( dR == winCon ){
        if( board[0][2] == 0 ){
            board[0][2] == pieceVal;
            return gameOver;
        }
        else if( board[1][1] == 0 ){
            board[1][1] == pieceVal;
            return gameOver;
        }
        else{
            board[2][0] = pieceVal;
            return gameOver;
        }
    }
    //If no win con available, check for empty spots on board
    else{ 
           /*//first copy board into temp board
           for( int i = 0; i < 3; i++ ){
               for( int j = 0; j < 3; j++ ){
                  tempBoard[i][j] = board[i][j];
               }
            }*/

           //intialize counter for number of empty spots
           emptyCtr = 0; 
           //loop over all empty spots, test outcome of each          
           for( int i = 0; i < 3; i++ ){
               for( int j = 0; j < 3; j++ ){
                  //initialize movesList
                  movesList[i][j] = movesInitVal;
                  //std::cout << board[i][j];
                  if( board[i][j] == 0 ){
                     //std::cout << "row: "<< i << ' ' << "col:" << j <<' ';
                     emptyCtr++;
                     board[i][j] = pieceVal;

                     /*for( int k = 0; k < 3; k++ ){
                        for( int l = 0; l < 3; l++ ){
                          std::cout << board[k][l]; 
                        }
                      }*/
                     movesList[i][j] = minimaxHelper( board, nextTurn );
                     //std::cout << "Move value: " << movesList[i][j]<< ' ';
                     //std::cout << "Right after call " << std::endl;
                     /*for( int k = 0; k < 3; k++ ){
                        for( int l = 0; l < 3; l++ ){
                          std::cout << board[k][l]; 
                        }
                      }*/
                     //reset board before next iteration
                     board[i][j] = 0;

                     /*if( tempBoard[i][j] == 0 ){
                        tempBoard[i][j] = pieceVal;
                        //store values of each move into matrix
                        movesList[i][j] = minimaxHelper( tempBoard, nextTurn );
                        emptyCtr++;
                        //recopy board here?
                        tempBoard[i][j] == 0;
                     }*/
                  }
               } 
            }
            //if no spots on board return 0 for tie
            if ( emptyCtr == 0 )
               return tieGame;

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
         //can return anything
         return 0; 
    }
}

//recursion helper function
int minimaxHelper( int board[][3], int turn ){
   int r1, r2, r3, c1, c2, c3, dL, dR;
   int winCon = -2;
   int pieceVal = -1;
   int movesInitVal = 3;
   int winsList[8];
   int movesList[3][3];
   int nextTurn = 0;
   int optVal;
   //std::cout << "hello from helper";
  /*//loop over board to determine whose turn it is
   for( int i = 0; i < 3; i++ )
     for( int j = 0; j < 3; j++ )
       state += board[i][j];*/
  //std::cout << "H: ";
  /*for( int i = 0; i < 3; i++ )
    for( int j = 0; j < 3; j++ )
      std::cout << board[i][j];*/ 

  //std::cout << "  ";
   if( turn == 0 ){
       winCon = 2;
       pieceVal = 1;
       movesInitVal = -3;
       nextTurn = -1;
   }
  //calculate values of rows, columns, and diagonals
   winsList[0] = board[0][0] + board[0][1] + board[0][2];
   winsList[1] = board[1][0] + board[1][1] + board[1][2];
   winsList[2] = board[2][0] + board[2][1] + board[2][2];
   winsList[3] = board[0][0] + board[1][0] + board[2][0];
   winsList[4] = board[0][1] + board[1][1] + board[2][1];
   winsList[5] = board[0][2] + board[1][2] + board[2][2];
   winsList[6] = board[0][0] + board[1][1] + board[2][2];
   winsList[7] = board[0][2] + board[1][1] + board[2][0];

  //loop over win states and see if any leads to win 
   for( int i = 0; i < 8; i++ ){
      if ( winsList[i] == winCon ){
        //std::cout << "hello from winstate in helper" << std::endl;
        return pieceVal;
      }
   }
  //check if board is tie, aka no possible moves left
   int emptyCtr = 0; 
   for( int i = 0; i < 3; i++ ){
      for( int j = 0; j < 3; j++ ){
         if( board[i][j] == 0 ){
            emptyCtr++;   
         } 
      }
   } 
   //std::cout << ' ' << "emptyCtr = " << emptyCtr << ' ';
   if( emptyCtr == 0 ){
      //std::cout << " Is empty" << ' ';
      return 0;
   }

  //If no win state found, then minimax
    //std::cout << "right before recursion" << std::endl;
   for(int i = 0; i < 3; i++ ){
      //std::cout << "outer loop";
      for( int j = 0; j < 3; j++ ){
         //std::cout << "inner loop";
         movesList[i][j] = movesInitVal;

         if( board[i][j] == 0 ){
          //std::cout << "rowi: "<< i << ' ' << "coli:" << j <<' ';
          //std::cout << "hello from inside helper";
            board[i][j] = pieceVal; 
            //std::cout << "Hello right before minimaxhelper recurse" << std::endl;
            movesList[i][j] = minimaxHelper( board, nextTurn );
            board[i][j] = 0;
         }
      }
   }

   /*for( int k = 0; k <3; k++){
              for( int l = 0; l <3; l++){
                std::cout << board[k][l];
              }
            }
            std::cout << "  ";*/
  //maximize out of set of moves
  //figure out the max or min depending on whose turn
   optVal = movesList[0][0];
   //optRow = 0;
   //optCol = 0;
   //if x turn, then find Max
   if( turn == 0 ){
      for( int k = 0; k < 3; k++ ){
         for( int l = 0; l < 3; l++ ){
            if( optVal < movesList[k][l] ){
               optVal = movesList[k][l];
               //optRow = k;
               //optCol = l;
            }
         }
      } 
   }

  //Otherwise it is O's turn so look for min
   else{
      for( int k = 0; k < 3; k++ ){
         for( int l = 0; l < 3; l++ ){
            if( optVal > movesList[k][l] ){
               optVal = movesList[k][l];
               //optRow = k;
               //optCol = l;
            }
         }
      } 
   }
   return optVal; 
}

/*int checkWin( board[][], int turn ){
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

}*/


