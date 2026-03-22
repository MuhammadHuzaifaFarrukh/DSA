#include <iostream>
#include <string>

using namespace std;

string removeOuterParentheses(string s)
{
    string result = "";
    int balance = 0;

    for (char c : s)
    {
        if (c == '(')
        {
            // If balance > 0, this '(' is NOT outermost
            if (balance > 0)
            {
                result += c;
            }
            balance++;
        }
        else
        {
            // Decrement balance first for closing bracket logic
            balance--;
            // If balance > 0, this ')' is NOT outermost
            if (balance > 0)
            {
                result += c;
            }
        }
    }
    return result;
}

int main()
{
    string s = "(()())(()(()))";
    // Example 2 from your image: "(()())(())(()(()))" -> "()()()()(())"
    cout << "Result: " << removeOuterParentheses("(()())(())") << endl;
    return 0;
}