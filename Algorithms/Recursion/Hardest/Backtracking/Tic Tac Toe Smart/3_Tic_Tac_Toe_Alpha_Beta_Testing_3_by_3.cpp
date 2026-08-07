#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Fixed N = 3 for standard 3x3 Tic-Tac-Toe
const int N = 3;

// Forward Declarations
void printBoard(const vector<vector<char>> &board);
int evaluateBoard(const vector<vector<char>> &board);
bool isBoardFull(const vector<vector<char>> &board);
int minimaxAlphaBeta(vector<vector<char>> &board, bool isAI, int alpha, int beta);
void makeBestAIMove(vector<vector<char>> &board);

/*
Minimax relies on two opposing roles:

1. The Core Roles: Maximizer vs. Minimizer
In Tic-Tac-Toe, two players oppose each other with opposite goals:

Maximizer (The AI): Tries to achieve the highest score possible (+10 for a win, 0 for a draw).
Minimizer (The Human): Tries to force the lowest score possible (-10 for a human win, 0 for a draw).
When the AI calculates its turn, it simulates future moves assuming both sides will play with absolute perfection.

2. How Alpha-Beta Pruning Works
Standard Minimax explores every single path down to the end of the game, even for moves that are obviously terrible. Alpha-Beta Pruning speeds up this process by keeping track of two boundary values as it moves through the search tree:

Alpha: The minimum score the AI is guaranteed to achieve so far across all options checked.
Beta: The maximum score the Human is willing to allow so far across options checked.

At the start of the search:
Alpha is set to negative infinity (worst case for AI).
Beta is set to positive infinity (worst case for Human).
As the AI checks move sequences, these boundaries narrow down. If at any point Alpha becomes greater than or equal to Beta, the AI immediately stops evaluating that branch. This condition means: "The human opponent can already force a better outcome for themselves elsewhere, so they will never allow the game to reach this state."

3. Step-by-Step Traversal Example
Imagine you open the game by placing your mark at the top-left corner (0,0). The AI needs to pick its response from the remaining 8 empty spots.

Phase 1: Evaluating the First Option (0,1)
The AI starts with Alpha = -infinity and Beta = +infinity.
Because this is the very first option tested, no prior baseline exists. No pruning can happen yet.
The AI simulates deep into the game tree under (0,1).
It finds that against a smart human player, placing an 'O' at (0,1) allows the human to force a win (Score = -10).
The AI updates its baseline: Alpha becomes -10. The AI now knows it can get at least a score of -10 across its choices.

Phase 2: Testing the Second Option (0,2)
The AI resets the board and tests placing an 'O' at (0,2), passing along its baseline Alpha = -10.
It simulates the human's response to (0,2). It tests the human taking the center spot (1,1).
Down that sequence, the AI finds a line where the human forces a win (Score = -10).
Because the human is the Minimizer, the human chooses this winning line, setting Beta = -10.
The AI compares: Alpha (-10) >= Beta (-10).
PRUNED! The AI immediately drops (0,2). It does not bother testing what happens if the human plays other moves like (1,0) or (2,2) after (0,2), because (0,2) is already proven to be a losing option.

Phase 3: Testing the Center Move (1,1)
The AI tests placing 'O' at the center spot (1,1), carrying Alpha = -10.
It explores human responses and discovers that by taking the center, it can defend perfectly and guarantee a Draw (Score = 0) regardless of how smartly the human responds.
The AI upgrades its baseline: Alpha increases from -10 to 0.

Phase 4: Testing Remaining Options (1,0), (2,0), etc.
For every remaining empty square, the AI carries forward Alpha = 0.
When testing a bad spot like (1,0), the AI checks a single smart human counter-move that forces a win (Score = -10).
The human sets Beta = -10.

The AI checks: Alpha (0) >= Beta (-10).
Instant Pruning! The AI discards (1,0) after evaluating just 1 or 2 steps down that path instead of exploring thousands of deeper moves.
*/

// Time Complexity :
// Pruning usually happens deep inside a branch of the minimaxAlphaBeta() where it has alpha and gets a beta so it prunes inside each individual (0,1) , (0,2) , (1,1) etc.
// Pruning is also happening at upper levels as well.
// When we place a move at (0,0) , now AI simulates at (0,1) and for the first move , it usually has to play all the moves to get the answer (though inner pruning might help a bit inside ).
// Now when AI has simulated at (0,1) completely , it gets -10 that human can force a win easily at this , so now AI sets this as base -10 as alpha and beta as -1000.
// Now for (0,2) pruning might be earlier than (0,1). When Ai finds that at any branch human can win , it doesn't check any further because it comes to know that at this specific branch no matter how smart AI plays , human can outsmart AI so it discards the inner branch or some upper branches if it is a bit upper.
// So when it checks for (1,0) , same thing happens , now when it checks for (1,1) , AI tests and inner pruning occurs but now AI sees that the max it can do from this stage is a draw.
// Also when AI has alpha answer for one move i.e (0,1) , now when it tries for the place (0,2) ,  it can prune early if it finds the best human moves earlier cause that drops beta and branch is cut off  , and when human plays lazily then Beta remains high , so Beta <= ALpha fails , so pruning is done late.
// So in the worst case , there may be little to no pruning so time becomes still equivalent to the plain minimax : O((n^2)!)

// When we account for the cases where human pruning is done , suppose n = 3, and ai knows (0,1) is human win so alpha = -10, now it sees for the (0,2).
// When it reaches for the conclusion , then when the answer is returned to AI's move , it still goes to find more , but when answer is returned to a turn human had previously , it doesn't go ahead to check more and just returns from there.
// On every human turn (odd positions: 7, 5, 3, 1), the algorithm evaluates only 1 move before pruning the rest.
// So this becomes a chain : 8 * 1 * 6 * 1 * 4 * 1 * 2 * 1.
// Now it happens for every other move ai has to simulate for all other places :
// 8! in plain minimax becomes here as : 8 * 1 * 6 * 1 * 4 * 1 * 2 * 1.
// 6! in plain minimax becomes here as : 6 * 1 * 4 * 1 * 2 * 1.
// 4! in plain minimax becomes here as : 4 * 1 * 2 * 1.
// 2! in plain minimax becomes here as : 2 * 1.
// However for the first move , AI may still go through more than (8*6*4*2) because it doesn't have a baseline set for the first move so while checking (0,1) it may need to perform like 1*7*6*4*2 (observe the local pruning also) , and now once it gets the baseline (alpha) , it can do the pruning more than the first move's first simulation check (0,1).
// So computing all , it is approx : sqrt((n^2)!).

// Time in worst case : O((n^2)!)
// Time in best case : O(sqrt((n^2)!))

// Space Complexity :
// Same as Plain Minimax => O(n^2)

int main()
{
    vector<vector<char>> board(3, vector<char>(3, ' '));

    cout << "=== Tic-Tac-Toe (3x3): You (X) vs Unbeatable Alpha-Beta AI (O) ===\n";

    while (true)
    {
        printBoard(board);

        // --- Human Turn ---
        int r, c;
        cout << "Enter your move row (0-2) and col (0-2): ";
        cin >> r >> c;

        if (r < 0 || r >= 3 || c < 0 || c >= 3 || board[r][c] != ' ')
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
        makeBestAIMove(board); // Finds best move using Alpha-Beta and places 'O'

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
                cout << " \xB3 "; // \xB3 is vertical bar (│)
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
    // Check rows and columns
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

    // Main Diagonal (Left-to-Right)
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

    // Anti Diagonal (Right-to-Left)
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
                return false;
            }
        }
    }
    return true;
}

// Finds the best move and places 'O' on the board directly
void makeBestAIMove(vector<vector<char>> &board)
{
    int bestVal = -1000;
    int bestRow = -1;
    int bestCol = -1;
    int alpha = -1000, beta = 1000;

    for (int r = 0; r < N; r++)
    {
        for (int c = 0; c < N; c++)
        {
            if (board[r][c] == ' ')
            {
                board[r][c] = 'O'; // Pretend to place 'O'

                // Call Minimax with initial alpha = -1000 and beta = 1000
                // ALpha belongs to AI and Beta belongs to Human
                int moveVal = minimaxAlphaBeta(board, false, alpha, beta);

                board[r][c] = ' '; // Undo (Backtrack)

                if (moveVal > bestVal)
                {
                    bestRow = r;
                    bestCol = c;
                    bestVal = moveVal;
                }
                if (bestVal > alpha)
                {
                    alpha = bestVal;
                }
            }
        }
    }

    // Make the actual move on the real game board
    board[bestRow][bestCol] = 'O';
}

// Recursive Alpha-Beta Pruning AI Brain
int minimaxAlphaBeta(vector<vector<char>> &board, bool isAI, int alpha, int beta)
{
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
        int bestScore = -1000;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = 'O';
                    int currentScore = minimaxAlphaBeta(board, false, alpha, beta);
                    board[r][c] = ' '; // Backtrack

                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                    }
                    if (bestScore > alpha)
                    {
                        alpha = bestScore;
                    }

                    // Prune condition
                    if (beta <= alpha)
                    {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
    else
    {
        int bestScore = 1000;
        for (int r = 0; r < N; r++)
        {
            for (int c = 0; c < N; c++)
            {
                if (board[r][c] == ' ')
                {
                    board[r][c] = 'X';
                    int currentScore = minimaxAlphaBeta(board, true, alpha, beta);
                    board[r][c] = ' '; // Backtrack

                    if (currentScore < bestScore)
                    {
                        bestScore = currentScore;
                    }
                    if (bestScore < beta)
                    {
                        beta = bestScore;
                    }

                    // Prune condition
                    if (beta <= alpha)
                    {
                        return bestScore;
                    }
                }
            }
        }
        return bestScore;
    }
}