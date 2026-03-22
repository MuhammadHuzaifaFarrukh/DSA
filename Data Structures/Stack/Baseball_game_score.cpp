#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int score(vector<string> &operations)
{
    int sum = 0;
    if (operations.size() == 0)
    {
        return sum;
    }
    stack<int> st;
    for (int i = 0; i < operations.size(); i++)
    {
        if (operations[i] != "C" && operations[i] != "D" && operations[i] != "+")
        {
            st.push(stoi(operations[i]));
        }
        else if (operations[i] == "C")
        {
            if (!st.empty())
            {
                st.pop();
            }
        }
        else if (operations[i] == "D")
        {
            if (!st.empty())
            {
                int temp = st.top();
                st.push(temp * 2);
                
            }
        }
        else if (operations[i] == "+")
        {
            if(st.size()>=2)
            {
                int temp1 = st.top();
                st.pop();
                int temp2 = st.top();
                st.push(temp1);
                st.push(temp1 + temp2);
            }
            
        }
    }

    while(!st.empty())
    {
        sum +=st.top();
        st.pop();
    }
    return sum;
}
int main()
{
    int n;
    cout << "Enter n :";
    cin >> n;
    while (n >= 1)
    {
        int x;
        cout << "Enter values of vector : ";
        cin >> x;

        vector<string> v(x);
        for (int i = 0; i < v.size(); i++)
        {
            cout << "Enter index [" << i << "] : ";
            cin >> v[i];
        }
        int y = score(v);
        cout << "Answer : " << y << endl;
        n--;
    }

    return 0;
}