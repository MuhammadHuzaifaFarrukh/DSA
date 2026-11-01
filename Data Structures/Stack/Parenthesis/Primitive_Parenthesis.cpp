#include <iostream>
#include <string>

using namespace std;

/*
A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.
Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.

Input: s = "(()())(())"
Output: "()()()"
Explanation:
The input string is "(()())(())", with primitive decomposition "(()())" + "(())".
After removing outer parentheses of each part, this is "()()" + "()" = "()()()".

Input: s = "(()())(())(()(()))"
Output: "()()()()(())"
Explanation:
The input string is "(()())(())(()(()))", with primitive decomposition "(()())" + "(())" + "(()(()))".
After removing outer parentheses of each part, this is "()()" + "()" + "()(())" = "()()()()(())".

Input: s = "()()"
Output: ""
Explanation:
The input string is "()()", with primitive decomposition "()" + "()".
After removing outer parentheses of each part, this is "" + "" = "".
*/

// Simulation :
// When depth increases , we increment depth and also check if its greater than 0.
// If its greater than 0 , it means that we are not at outermost portion so we just add this string char to our result.
// On closing braces we similarly decrease depth and check if its greater than 0 still , if yes then it means we are at inner portion because the strings are valid parenthesis , there will be more closing brackets.
// Its a simple algorithm where we just have to add the answer in our string if its depth is greater than 0.
// Time Complexity : O(n)
// Space Complexity : O(n)
string removeOuterParentheses(string &s)
{
    string result = "";
    int depth = 0;
    for (char c : s)
    {
        if (c == '(')
        {
            // If depth > 0, this '(' is NOT outermost
            if (depth > 0)
            {
                result += c;
            }
            depth++;
        }
        else
        {
            // Decrement depth first for closing bracket logic
            depth--;
            // If depth > 0, this ')' is NOT outermost
            if (depth > 0)
            {
                result += c;
            }
        }
    }
    return result;
}

int main()
{
    string s = "((()))";
    // "(()())(())(()(()))" -> "()()()()(())"
    cout << "Result: " << removeOuterParentheses(s) << endl;
    return 0;
}
