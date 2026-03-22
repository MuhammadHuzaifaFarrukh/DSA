#include <iostream>
#include <stack>
#include <string>
using namespace std;

int findscore(string s)
{
    int score = 0;
    int depth = 0;
    stack<char> st;
    for(int i = 0 ; i<s.length() ; i++)
    {
        if(s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            st.push(s[i]);
            depth++;
        }
        else
        {
            if(st.empty())
            {
                cout<<"Invalid"<<endl;
                return -1;
            }
            else
            {
                char top = st.top();
                if( (s[i] == '}' && top == '{') || (s[i] == ')' && top == '(' )  || (s[i] == ']' && top == '[')  )
                {
                    if(s[i] == '}' && top == '{')
                    {
                        score = score + (depth*3);
                    }
                    else if(s[i] == ')' && top == '(')
                    {
                        score = score + (depth);
                    }
                    else if(s[i] == ']' && top == '[')
                    {
                        score = score + (depth*2);
                    }
                    st.pop();
                    depth--;
                }
                else
                {
                    cout<<"Invalid"<<endl;
                    return -1;
                }
            }
        }
    }
    if(st.empty())	// Stack gets emptied after all popped out with matches successful or if an Empty String is given, then that case is also handled
    {
        return score;   
    }
    else
    {
        return -1;   
    }
}

int main()
{
    string s;
    cout<<"Enter string : ";
    getline(cin, s);
    int x = findscore(s);
    if(x != -1)
    {
        cout<<"Valid String Score : "<<x<<endl;
    }
    return 0;
}