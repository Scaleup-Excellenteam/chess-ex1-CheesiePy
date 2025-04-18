// Chess 
#include "Chess.h"
#include <iostream>
#include <string>
#include "GameManager.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
	GameManager gm;
	gm.initGame();

	int currentTurn = 0; // 0 for white, 1 for black

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
		codeResponse = gm.validateMove(res, currentTurn);

		// if turn was legal, switch turn
		currentTurn = (currentTurn + 1) % 2; // switch turn


		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}