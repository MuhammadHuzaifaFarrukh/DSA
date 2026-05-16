#include <iostream>
#include <string>
#include <stack>

using namespace std;

// You can either evaluate directly or use conversion.
// Converting to postfix is easier to debug and evaulate an expression.
// This function is the leetcode implementation (supports only addition and subtraction).
int calculate(string s)
{
    stack<int> st;
    int current_result = 0;
    int sign = 1; // 1 for '+', -1 for '-'

    for (int i = 0; i < s.length(); i++)
    {
        // 1. Skip whitespace
        if (s[i] == ' ')
            continue;

        // 2. If it's a digit, find the full number and use stoi
        if (isdigit(s[i]))
        {
            int start = i;
            while (i < s.length() && isdigit(s[i]))
            {
                i++;
            }
            // Extract substring and convert
            string numStr = s.substr(start, i - start);
            int val = stoi(numStr);

            current_result += sign * val;
            i--; // Step back because the for-loop will increment i
        }
        else if (s[i] == '+')
        {
            sign = 1;
        }
        else if (s[i] == '-')
        {
            sign = -1;
        }
        else if (s[i] == '(')
        {
            // Push current result and sign to "save" state
            st.push(current_result);
            st.push(sign);

            // Reset for expression inside brackets
            current_result = 0;
            sign = 1;
        }
        else if (s[i] == ')')
        {
            // Pop sign that was before '(', then pop the previous result
            int prev_sign = st.top();
            st.pop();
            int prev_result = st.top();
            st.pop();

            current_result = prev_result + (prev_sign * current_result);
        }
    }
    return current_result;
}

int calculate2(string);
int getPrecedence(char);

int main()
{
    // Test case: 10 plus the result of (40 - 5)
    string expr = "10 + ( 40 - 5 )";
    cout << "Result: " << calculate(expr) << endl;
    return 0;
}

// This function is the normal daily implementation (supports all basic operations).
/*

int getPrecedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

int calculate(string s)
{
    stack<int> numbers;
    stack<char> operators;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
        {
            continue; // Skip spaces safely
        }

        // 1. If it's a digit, extract the whole number inline
        if (isdigit(s[i]))
        {
            long long val = 0;
            while (i < s.length() && isdigit(s[i]))
            {
                val = val * 10 + (s[i] - '0');
                i++;
            }
            i--; // Step back so the for-loop lands correctly
            numbers.push(val);
        }
        // 2. If it's an opening bracket, push it to wait
        else if (s[i] == '(')
        {
            operators.push(s[i]);
        }
        // 3. If it's a closing bracket, process everything inside it right now
        else if (s[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                int val2 = numbers.top();
                numbers.pop();
                int val1 = numbers.top();
                numbers.pop();

                if (op == '+')
                {
                    numbers.push(val1 + val2);
                }
                else if (op == '-')
                {
                    numbers.push(val1 - val2);
                }
                else if (op == '*')
                {
                    numbers.push(val1 * val2);
                }
                else if (op == '/')
                {
                    numbers.push(val1 / val2);
                    // You may check here for the division by zero and throw error using try-catch.
                }
            }
            if (!operators.empty())
            {
                operators.pop(); // Discard the matching '('
            }
        }
        // 4. If it's an operator (+, -, *, /)
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
        {
            // Clean loop condition using the precedence function
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(s[i]))
            {
                char op = operators.top();
                operators.pop();
                int val2 = numbers.top();
                numbers.pop();
                int val1 = numbers.top();
                numbers.pop();

                if (op == '+')
                {
                    numbers.push(val1 + val2);
                }
                else if (op == '-')
                {
                    numbers.push(val1 - val2);
                }
                else if (op == '*')
                {
                    numbers.push(val1 * val2);
                }
                else if (op == '/')
                {
                    numbers.push(val1 / val2);
                    // You may check here for the division by zero and throw error using try-catch.
                }
            }
            operators.push(s[i]); // Store current operator
        }
    }

    // 5. Clean up any remaining operations left over at the end
    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        int val2 = numbers.top();
        numbers.pop();
        int val1 = numbers.top();
        numbers.pop();

        if (op == '+')
        {
            numbers.push(val1 + val2);
        }
        else if (op == '-')
        {
            numbers.push(val1 - val2);
        }
        else if (op == '*')
        {
            numbers.push(val1 * val2);
        }
        else if (op == '/')
        {
            numbers.push(val1 / val2);
            // You may check here for the division by zero and throw error using try-catch.
        }
    }

    // The last standing element on the numbers stack is the final answer
    if (numbers.empty())
    {
        return 0;
    }
    return numbers.top();
}

*/
