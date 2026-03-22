#include <iostream>
#include <stack>

using namespace std;
bool evaluateBooleanExpression(string expression) 
{
    stack<char> st;

    for (int i = 0; i < expression.length(); i++) 
    {
        char c = expression[i];

        // Skip commas and spaces
        if (c == ',' || c == ' ') 
        {
            continue;
        }

        if (c != ')') 
        {
            // Push everything (t, f, !, &, |, () onto stack
            st.push(c);
        } 
        else 
        {
            // 1. We hit ')', start collecting values until '('
            // We'll track the result for this specific bracket set
            bool isTrue = false;
            bool isFalse = false;
            int count = 0;

            while (!st.empty() && st.top() != '(') 
            {
                char top = st.top();
                st.pop();
                if (top == 't')
                {
                    isTrue = true;
                }
                if (top == 'f')
                {
                    isFalse = true;
                }
                count++;
            }

            // 2. Pop the opening '('
            if (!st.empty()) st.pop();

            // 3. The character before '(' is our operator
            char op = st.top();
            st.pop();

            char c;
            if (op == '!') 
            {
                // Rule: '!(subExpr)' represents logical NOT
                c = (isTrue ? 'f' : 't');
                // c = (isFalse ? 't' : 'f');   // This can be used as well.
            } 
            else if (op == '&') 
            {
                // Rule: '&(subExprs)' is AND (needs ALL to be true)
                // If any 'f' exists, result is 'f'
                c = (isFalse ? 'f' : 't');
            } 
            else if (op == '|') 
            {
                // Rule: '|(subExprs)' is OR (needs AT LEAST one true)
                // If any 't' exists, result is 't'
                c = (isTrue ? 't' : 'f');
            }

            // 4. Push this sub-result back to the stack to be used by outer operators
            st.push(c);
        }
    }

    // The last remaining element on the stack is our final answer
    return st.top() == 't';
}

int main()
{
    string s;
    cout<<"Enter a string : ";
    getline(cin,s);
    bool f = evaluateBooleanExpression(s);
    cout<<boolalpha;
    cout<<f<<endl;

    return 0;
}