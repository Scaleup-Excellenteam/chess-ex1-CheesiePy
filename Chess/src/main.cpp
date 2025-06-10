// Chess 
#include <iostream>
#include <string>
#include <thread>
#include <cstdlib>      // std::strtol
#include <iostream>
#include <string>

#include "Utils/ThreadPoolSingleton.h"     
#include "AI/BestMoveFinder.h"      
#include "GameManager.h"
#include "Chess.h"


/* ───────── simple CLI helper ───────── */
static std::size_t argToSize(const char* s, std::size_t fallback)
{
    if (!s) return fallback;
    char* end{};
    long v = std::strtol(s, &end, 10);
    return (end != s && v > 0) ? static_cast<std::size_t>(v) : fallback;
}

int main(int argc, char* argv[])
{

	    std::size_t threadCount = std::thread::hardware_concurrency();   // default
    int depthOverride       = -1;

    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--threads" && i + 1 < argc)
            threadCount = argToSize(argv[++i], threadCount);
        else if (std::string(argv[i]) == "--depth" && i + 1 < argc)
            depthOverride = static_cast<int>(argToSize(argv[++i], 0));
        else if (std::string(argv[i]) == "--help")
        {
            std::cout << "Usage: Chess [--threads N] [--depth D]\n";
            return 0;
        }
    }

    /*FIRST (and only) construction of the pool */
    globalPool(threadCount);

    // /* optional depth override */
    // if (depthOverride > 0)
    //     AI::BestMoveFinder::DEFAULT_DEPTH = depthOverride;


	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
	


	// chacking if ai recom works
	// auto hints = AI::findBestMoves(gm.currentBoard(), true, 5);

	// for(const auto& h: hints){
	// 	std::cout << h << '\n';
	// }

	int currentTurn = 1; // 1 for white, 0 for black

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
		codeResponse = a.validateMoveViaManager(res);

		// if turn was legal, switch turn
		currentTurn = (currentTurn + 1) % 2; // switch turn


		a.setCodeResponse(codeResponse);
		res = a.getInput(); 
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}




// smoke test for ThreadPool
//#include "Utils/ThreadPool.h"
// int main()
// {
//     ThreadPool pool{4};

//     std::vector<std::future<void>> futs;
//     for (int i = 0; i < 10; ++i){
// 		futs.push_back(
// 			pool.enqueue(
// 				[i]{std::cout << "task " << i << " on thread " << std::this_thread::get_id() << '\n';}
// 			)
// 		);
// 	}
// 	for (auto& f : futs){ 
// 		f.get(); 
// 	}
// }


// #include "Utils/ThreadPool.h"
// #include "Utils/SafeMovePQ.h"
// #include <iostream>

// int main()
// {
//     ThreadPool pool{4};
//     SafeMovePQ q;

//     /* launch 8 worker tasks pushing scored moves */
//     for (int i = 0; i < 8; ++i)
//         pool.enqueue([i, &q]{
//             for (int j = 0; j < 5; ++j)
//                 q.push({CMove{}, i*10 + j});   // dummy moves
//         });

//     pool.enqueue([&q]{ q.push({CMove{}, 999}); });  // clearly best

//     /* wait implicitly in pool dtor (main returns) */
//     /* pop all */
//     while (!q.empty())
//         if (auto item = q.try_pop(); item)
//             std::cout << "popped " << item->score << '\n';
// }
