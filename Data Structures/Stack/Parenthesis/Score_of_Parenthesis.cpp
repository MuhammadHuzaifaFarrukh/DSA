#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

// Balanced String is given
// The Outer Parentheses will double the score (like multiplier).
// Empty Parentheses will be used in score.
int scoreOfParenthesis(string s)
{
    int score = 0;
    int depth = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(')
        {
            depth++;
        }
        else
        {
            depth--;
            // Only add score if this ')' is closing an immediate '('
            if (s[i - 1] == '(')
            {
                // 1 << depth is the same as pow(2, depth) but faster
                score += (1 << depth);
            }
        }
    }
    return score;
}

int main()
{
    string exp = "((()((()()))))";
    cout << "Score : " << scoreOfParenthesis(exp) << endl;
}