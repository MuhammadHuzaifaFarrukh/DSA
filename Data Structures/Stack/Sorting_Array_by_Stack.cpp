#include <iostream>
#include <stack>
#include <vector>
using namespace std;

void sortArray(vector<int> &arr)
{
    stack<int> input;
    for (int x : arr)
    {
        input.push(x); // Put array into a stack
    }

    stack<int> sortedStack;

    while (!input.empty())
    {
        int temp = input.top();
        input.pop();

        // While sortedStack has elements greater than temp,
        // move them back to the input stack
        while (!sortedStack.empty() && sortedStack.top() > temp)
        {
            input.push(sortedStack.top());
            sortedStack.pop();
        }

        sortedStack.push(temp);
    }

    // Put elements back into the array
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        arr[i] = sortedStack.top();
        sortedStack.pop();
    }
}

int main()
{
    vector<int> v = {4, 6, 1, 2, 9, 5};
    sortArray(v);
    for (int c : v)
    {
        cout << c << endl;
    }
    return 0;
}