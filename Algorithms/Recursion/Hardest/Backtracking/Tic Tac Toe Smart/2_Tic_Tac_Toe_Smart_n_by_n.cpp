#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

// Global N to dynamically size the board logic
int N = 3;

// Forward Declarations :

void printBoard(const vector<vector<char>> &board);
int evaluateBoard(const vector<vector<char>> &board);
bool isBoardFull(const vector<vector<char>> &board);
int minimax(vector<vector<char>> &board, bool isAI);
void makeBestAIMove(vector<vector<char>> &board);

// In this , when there are total 9 boxes to fill , we fix one position and now ai has to take turn.
// So it searches for all the places and plays out a simulation on each place , which place would be the best.
// E.g if I place at (0,0) , then ai simulates on (0,1) and then plays as both human and ai by trying smartest moves from both perspectives.
// On (0,1) it sees that it cannot win if human plays smart , so it tries for the next position and plays the simulation on (0,2) with 7! combinations again.
// Then it tries on (1,0) -> 7! combinations and then it reaches (1,1). When it reaches (1,1) , it sees that it cannot win , but the best it can do at this place is draw if human plays smart, so it saves this row/col idx.
// It checks also for other places but it cannot find a position better than this one.
// This keeps going on , so we cannot beat AI (the answer usually for this game is draw if AI plays its best move and we play ours).
// So When AI is simulating , it uses makeBestAIMove() , and a minimax() without pruning , while simulation , when it reaches a conclusion , ai just backtracks and keeps the simulation until the next conclusion and so on.

// Time Complexity :
// AI uses 7! combinations for all 8 places when we make a move = 8*7! = 8!
// When AI takes its turn then we make a next move and that leaves AI for 6 places so it makes combinations 6!.
// Going forward : 8!+6!+4!+2! = ((n-1)^2)! + ((n-3)^2)! + ((n-5)^2)! + ... + ((n-7)^2)! ~ O(((n-1)^2)!) ~ O((n^2)!)
// Time : O((n^2)!)

// Space Complexity :
// The Board takes n^2 space. = O(n^2)
// Maximum recursive depth that can go is of the size of boards : n^2 = O(n^2)
// Space : O(n^2)

// Incase we put n = 4 or more , the board gets stuck because for first move it has to try almost upto 15! combinations (very huge) without any pruning.

int main()
{
    cout << "Enter board size N (3-6 recommended, 3 for fast play): ";
    cin >> N;

    if (N < 3)
    {
        N = 3;
    }

    vector<vector<char>> board(N, vector<char>(N, ' '));

    cout << "=== Tic-Tac-Toe: You (X) vs Unbeatable AI (O) ===\n";

    while (true)
    {
        printBoard(board);

        // --- Human Turn ---
        int r, c;
        cout << "Enter your move row (0-" << N - 1 << ") and col (0-" << N - 1 << "): ";
        cin >> r >> c;

        if (r < 0 || r >= N || c < 0 || c >= N || board[r][c] != ' ')
        {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[r][c] = 'X'; // Place Human move

        if (evaluateBoard(board) == -10)
        {
            printBoard(board);
            cout << "You somehow won!\n";
            break;
        }
        if (isBoardFull(board))
        {
            printBoard(board);
            cout << "It's a DRAW!\n";
            break;
        }

        // --- AI Turn ---
        cout << "Smart AI is calculating moves...\n";
        makeBestAIMove(board); // Finds best move using simple variables and places 'O'

        if (evaluateBoard(board) == 10)
        {
            printBoard(board);
            cout << "AI Wins! Better luck next time.\n";
            break;
        }
        if (isBoardFull(board))
        {
            printBoard(board);
            cout << "It's a DRAW!\n";
            break;
        }
    }
    return 0;
}

void printCell(char cell)
{
    if (cell == 'X')
    {
        cout << "\x1b[31m\x1b[1mX\x1b[0m"; // Red
    }
    else if (cell == 'O')
    {
        cout << "\x1b[34m\x1b[1mO\x1b[0m"; // Blue
    }
    else
    {
        cout << "\x1b[90m.\x1b[0m"; // Gray dot for empty space
    }
}

void printBoard(const vector<vector<char>> &board)
{
    cout << "\n";
    for (int i = 0; i < N; i++)
    {
        cout << " ";
        for (int j = 0; j < N; j++)
        {
            printCell(board[i][j]);
            if (j < N - 1)
            {
                cout << " \xB3 "; // \xB3 is the vertical bar (│)
            }
        }
        cout << "\n";

        if (i < N - 1)
        {
            // \xC4 is horizontal bar (─), \xC5 is cross intersection (┼)
            for (int j = 0; j < N; j++)
            {
                cout << "\xC4\xC4\xC4";
                if (j < N - 1)
                {
                    cout << "\xC5";
                }
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

int evaluateBoard(const vector<vector<char>> &board)
{
    // Check rows and columns.
    // 10 means computer won and -10 means user.
    // 0 means no winner yet.
    for (int i = 0; i < N; i++)
    {
        // Check Row i
        char firstRow = board[i][0];
        if (firstRow != ' ')
        {
            bool rowWin = true;
            for (int j = 1; j < N; j++)
            {
                if (board[i][j] != firstRow)
                {
                    rowWin = false;
                    break;
                }
            }
            if (rowWin)
            {
                if (firstRow == 'O')
                {
                    return 10;
                }
                else
                {
                    return -10;
                }
            }
        }

        // Check Column i
        char firstCol = board[0][i];
        if (firstCol != ' ')
        {
            bool colWin = true;
            for (int j = 1; j < N; j++)
            {
                if (board[j][i] != firstCol)
                {
                    colWin = false;
                    break;
                }
            }
            if (colWin)
            {
                if (firstCol == 'O')
                {
                    return 10;
                }
                else
                {
                    return -10;
                }
            }
        }
    }

    // Left Diagonal
    char mainDiag = board[0][0];
    if (mainDiag != ' ')
    {
        bool diagWin = true;
        for (int i = 1; i < N; i++)
        {
            if (board[i][i] != mainDiag)
            {
                diagWin = false;
                break;
            }
        }
        if (diagWin)
        {
            if (mainDiag == 'O')
            {
                return 10;
            }
            else
            {
                return -10;
            }
        }
    }

    // Right Diagonal
    char antiDiag = board[0][N - 1];
    if (antiDiag != ' ')
    {
        bool antiDiagWin = true;
        for (int i = 1; i < N; i++)
        {
            if (board[i][N - 1 - i] != antiDiag)
            {
                antiDiagWin = false;
                break;
            }
        }
        if (antiDiagWin)
        {
            if (antiDiag == 'O')
            {
                return 10;
            }
            else
            {
                return -10;
            }
        }
    }

    return 0; // No winner yet
}

bool isBoardFull(const vector<vector<char>> &board)
{
    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (board[r][c] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

// Finds the best move and places 'O' on the board directly
void makeBestAIMove(vector<vector<char>> &board)
{
    int bestVal = -1000; // Start with a super low score
    int bestRow = -1;
    int bestCol = -1;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (board[r][c] == ' ')
            {
                // Found an empty spot!
                board[r][c] = 'O'; // 1. Pretend to place 'O' here

                // 2. Ask minimax: "If I play here, what is the score?"
                int moveVal = minimax(board, false);

                board[r][c] = ' '; // 3. UNDO (Backtrack) so the real board isn't ruined

                // 4. Is this the best score we've seen so far?
                if (moveVal > bestVal)
                {
                    bestRow = r;
                    bestCol = c;
                    bestVal = moveVal;
                }
            }
        }
    }

    // 5. Finally, make the actual move on the real game board!
    board[bestRow][bestCol] = 'O';
}

// --- 2. RECURSIVE AI BRAIN (MINIMAX) ---
// makeBestAIMove() uses this function actually.
// The Imaginary Simulator
int minimax(vector<vector<char>> &board, bool isAI)
{
    // Is the game over yet?
    int score = evaluateBoard(board);

    // Base cases
    if (score == 10)
    {
        return score; // AI wins
    }
    if (score == -10)
    {
        return score; // Human wins
    }
    if (isBoardFull(board))
    {
        return 0; // Draw
    }

    if (isAI)
    {
        // AI's turn (Maximizing)
        int bestScore = -1000;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = 'O'; // Try move
                    int currentScore = minimax(board, false);
                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                    }
                    board[r][c] = ' '; // Backtrack
                }
            }
        }
        return bestScore;
    }
    else
    {
        // Human's turn (Minimizing)
        int bestScore = 1000;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = 'X'; // Try move
                    int currentScore = minimax(board, true);
                    if (currentScore < bestScore)
                    {
                        bestScore = currentScore;
                    }
                    board[r][c] = ' '; // Backtrack
                }
            }
        }
        return bestScore;
    }
}