#include "GameManager.h"
#include "AI/BestMoveFinder.h"
#include "Chess.h"
#include <iostream>
#include <string>

using namespace std;

#ifdef _WIN32

// clear the screen "cls"
void Chess::clear() const
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// create the GUI - ASCII art
void Chess::setFrames()
{
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = 32;

	m_board[0][0] = 201;  m_board[0][20] = 187;
	m_board[20][0] = 200; m_board[20][20] = 188;

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = 205;
		m_board[20][i] = 205;
		m_board[i][0] = 186;
		m_board[i][20] = 186;
	}

	m_board[2][2] = 218;  m_board[2][18] = 191;
	m_board[18][2] = 192; m_board[18][18] = 217;

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = 194;
		m_board[18][i] = 193;
		m_board[i][2] = 195;
		m_board[i][18] = 180;
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = 196;

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = 179;

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = 197;

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = 194;
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = 193;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = 195;
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = 180;

    // --- CORRECTED GUI LABELS ---
    // Draw letters 'A' through 'H' on the top and bottom (the file/column)
	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('A' + t);

    // Draw numbers '8' down to '1' on the left and right (the rank/row)
	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('8' - t);
    // --- END CORRECTION ---
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}

#else // non-Windows

void Chess::clear() const
{
	cout << "\033[2J\033[3J\033[H";
}

void Chess::setFrames()
{
	for (size_t row = 0; row < _SIZE; ++row)
		for (size_t col = 0; col < _SIZE; ++col)
			m_board[row][col] = ' ';

	m_board[0][0] = '+';
	m_board[0][20] = '+';
	m_board[20][0] = '+';
	m_board[20][20] = '+';

	for (size_t i = 1; i < 20; ++i)
	{
		m_board[0][i] = '-';
		m_board[20][i] = '-';
		m_board[i][0] = '|';
		m_board[i][20] = '|';
	}

	m_board[2][2] = '+';
	m_board[2][18] = '+';
	m_board[18][2] = '+';
	m_board[18][18] = '+';

	for (size_t i = 4; i < 17; i += 2)
	{
		m_board[2][i] = '+';
		m_board[18][i] = '+';
		m_board[i][2] = '+';
		m_board[i][18] = '+';
	}

	for (size_t i = 2; i < 19; i += 2)
		for (size_t j = 3; j < 19; j += 2)
			m_board[i][j] = '-';

	for (size_t i = 3; i < 18; i += 2)
		for (size_t j = 2; j < 19; j += 2)
			m_board[i][j] = '|';

	for (size_t i = 4; i < 17; i += 2)
		for (size_t j = 4; j < 17; j += 2)
			m_board[i][j] = '+';

	for (size_t i = 4; i < 17; i += 2)
		m_board[2][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[18][i] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][2] = '+';
	for (size_t i = 4; i < 17; i += 2)
		m_board[i][18] = '+';

    // --- CORRECTED GUI LABELS ---
    // Draw letters 'A' through 'H' on the top and bottom (the file/column)
	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[1][i] = m_board[19][i] = ('A' + t);

    // Draw numbers '8' down to '1' on the left and right (the rank/row)
	for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
		m_board[i][1] = m_board[i][19] = ('8' - t);
    // --- END CORRECTION ---
}

void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? ' ' : m_boardString[t]);
}

#endif // WINDOWS


void Chess::syncBoardStringWithBoard()
{
    m_boardString.clear();
    m_boardString.reserve(64);

    const Board& b = manager_.currentBoard();

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            if (const Piece* p = b.getPiece(r, c))
                m_boardString.push_back(p->getSymbol());
            else
                m_boardString.push_back('#');
}

void Chess::show() const
{
	for (size_t row = 0; row < _SIZE; ++row)
	{
		for (size_t col = 0; col < _SIZE; ++col)
			cout << m_board[row][col];
		cout << endl;
	}
}

void Chess::displayBoard() const
{
	clear();
	show();
	cout << m_msg << m_errorMsg << m_hint;
}

void Chess::showAskInput() const
{
	if (m_turn)
		cout << "Player 1 (White - Small letters) >> ";
	else
		cout << "Player 2 (Black - Capital letters) >> ";
}

bool Chess::isSame() const
{
	return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
}

bool Chess::isValid() const
{
    // This function just checks the basic format, which is still valid.
	return ((('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
		(('1' <= m_input[1]) && (m_input[1] <= '8')) &&
		(('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
		(('1' <= m_input[3]) && (m_input[3] <= '8')));
}

bool Chess::isExit() const
{
	return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}

void Chess::excute()
{
    // --- START OF CORRECTION ---
    // This function is called after a move has been validated.
    // We convert the coordinates using the standard system and pass them to the GameManager.
    int srcCol = m_input[0] - 'a';
    int dstCol = m_input[2] - 'a';
    int srcRow = 7 - (m_input[1] - '1');
    int dstRow = 7 - (m_input[3] - '1');

    // Let the engine make the move using the correct integer coordinates
    manager_.makeMove(srcRow, srcCol, dstRow, dstCol);

    // Sync the GUI with the new board state
    syncBoardStringWithBoard();
    setPieces();
    // --- END OF CORRECTION ---
}


void Chess::doTurn()
{
	m_errorMsg = "\n";
	switch (m_codeResponse)
	{
	case 11:
		m_msg = "Invalid move: No piece at source or invalid format.\n";
		break;
	case 12:
		m_msg = "Invalid move: It's not your piece.\n";
		break;
	case 13:
		m_msg = "Invalid move: You already have a piece at the destination.\n";
		break;
	case 21:
		m_msg = "Invalid move: This piece doesn't move that way.\n";
		break;
	case 31:
		m_msg = "Invalid move: This would leave your king in check.\n";
		break;
	case 41: // Legal move that caused a check
	case 42: // Legal move
		excute(); // Execute the move and update the GUI
		m_turn = !m_turn; // Switch turns

        // Update hint for the next player
		auto recs = AI::findBestMoves(manager_.currentBoard(), m_turn, 2);
		if (!recs.empty()) {
		    m_hint = "Hint: " + recs.front().toString() + '\n';
		} else {
		    m_hint.clear();
		}

        // Set the message based on whether it was a check or not.
		if (m_codeResponse == 41) {
			m_msg = "Legal move. The opponent is in check!\n";
		} else {
			m_msg = "Legal move.\n";
		}
		break;
	}
}

// C'tor
Chess::Chess(const string& start)
	: m_boardString(start),m_codeResponse(-1), m_turn(true)
{
	setFrames();
	manager_.initGame();
	syncBoardStringWithBoard();
	setPieces();
}

// get the source and destination
string Chess::getInput()
{
	static bool isFirst = true;

	if (isFirst)
		isFirst = false;
	else
		doTurn();

	displayBoard();
	showAskInput();

	cin >> m_input;
    // Standardize input to lowercase
    for (char& c : m_input) {
        c = std::tolower(c);
    }

	if (isExit())
		return "exit";

	while (m_input.length() != 4 || !isValid() || isSame())
	{
		if (m_input.length() != 4 || !isValid())
			m_errorMsg = "Invalid input format! Use 4 chars like 'e2e4'.\n";
		else
			m_errorMsg = "The source and the destination are the same!\n";
		displayBoard();
		showAskInput();
		cin >> m_input;
        for (char& c : m_input) {
            c = std::tolower(c);
        }
		if (isExit())
			return "exit";
	}
	return m_input;
}

void Chess::setCodeResponse(int codeResponse)
{
	m_codeResponse = codeResponse;
}

int Chess::validateMoveViaManager(const std::string& mv) const
{
    return manager_.validateMove(mv);
}