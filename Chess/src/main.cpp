// Chess 
#include "Chess.h"
#include <iostream>
#include <string>
#include "GameManager.h"
#include "Utils/ThreadPool.h"

// // int main()
// {
// 	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
// //	string board = "##########K###############################R#############r#r#####";
// 	Chess a(board);
// 	int codeResponse = 0;
// 	string res = a.getInput();
	


// 	// chacking if ai recom works
// 	// auto hints = AI::findBestMoves(gm.currentBoard(), true, 5);

// 	// for(const auto& h: hints){
// 	// 	std::cout << h << '\n';
// 	// }

// 	int currentTurn = 1; // 1 for white, 0 for black

// 	while (res != "exit")
// 	{
// 		/* 
// 		codeResponse value : 
// 		Illegal movements : 
// 		11 - there is not piece at the source  
// 		12 - the piece in the source is piece of your opponent
// 		13 - there one of your pieces at the destination 
// 		21 - illegal movement of that piece 
// 		31 - this movement will cause you checkmate

// 		legal movements : 
// 		41 - the last movement was legal and cause check 
// 		42 - the last movement was legal, next turn 
// 		*/

// 		/**/ 
// 		codeResponse = a.validateMoveViaManager(res);

// 		// if turn was legal, switch turn
// 		currentTurn = (currentTurn + 1) % 2; // switch turn


// 		a.setCodeResponse(codeResponse);
// 		res = a.getInput(); 
// 	}

// 	cout << endl << "Exiting " << endl; 
// 	return 0;
// }




// smoke test for ThreadPool
int main()
{
    ThreadPool pool{4};

    std::vector<std::future<void>> futs;
    for (int i = 0; i < 10; ++i){
		futs.push_back(
			pool.enqueue(
				[i]{std::cout << "task " << i << " on thread " << std::this_thread::get_id() << '\n';}
			)
		);
	}
	for (auto& f : futs){ 
		f.get(); 
	}
}