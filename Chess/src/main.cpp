// Chess 
#include "Chess.h"
#include <iostream>
#include <string>
#include "Board.h"
#include "Rook.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();

	// initialize the board
	Board chessBoard;
	// set the pieces on the board
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			char pieceChar = board[i * 8 + j];
			if (pieceChar != '#') {
				bool isWhite = (pieceChar >= 'A' && pieceChar <= 'Z');
				switch (pieceChar) {
					case 'R':
						chessBoard.setPiece(i, j, std::make_unique<Rook>(isWhite));
						break;
					// Add other pieces here
					default:
						break;
				}
			}
		}
	}

	


	while (res != "exit")
	{
		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		*/

		/**/ 
		{
		
		}
		
		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}