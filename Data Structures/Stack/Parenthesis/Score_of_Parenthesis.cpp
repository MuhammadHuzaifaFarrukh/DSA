#include <iostream>
#include <stack>
#include <string>
#include <cmath>
using namespace std;

/*
Given a balanced parentheses string s, return the score of the string.
The score of a balanced parentheses string is based on the following rule:

"()" has score 1.
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.

Input: s = "()"
Output: 1

Input: s = "(())"
Output: 2

Input: s = "()()"
Output: 2
*/

// Balanced String is given
// The Outer Parentheses will double the score (like multiplier).
// Empty Parentheses will be used in score.

// Simulation / Maths :
// When we see '(' , we increase a depth variable.
// Now since its a balanced parenthesis , it will also have a closing parenthesis.
// When we encounter this ')' , we simply decrease the depth because our depth increases 1 step further always e.g string "()" , then its score is 1<<0 so we decrease depth before finding out.
// If we have a string (()) then our depth again increases 1 step further depth = 2 , so we decrease it when we encounter first ')' and we add score to 1<<1 which multiplies it by 2.
// Now we also need to check if we have '(' right before ')' very necessary because for strings like (()) they have score of 2 , but if we don't check that condition it may give answer 3 , because we know that those parenthesis inside make it upto total 2 so ) cannot be before ).
// If we have this string (()()) , they each have a score of 2 as depth inside of first pair makes both of them 2 , giving total of 4 score.
// Time Complexity : O(n)
// Space Complexity : O(1)
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
                // 1 << depth is the same as pow(2, depth) or mul by 2 but faster
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
