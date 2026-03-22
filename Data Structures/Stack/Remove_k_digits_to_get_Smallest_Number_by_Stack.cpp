#include <iostream>
#include <string>
#include <stack>

using namespace std;

string remove_k_digits(string num, int k)
{
    stack<char> s;

    // Phase 1: Build the monotonic stack
    for (int i = 0; i < num.length(); i++)
    {
        char c = num[i];
        // If current digit is smaller than stack top, pop the top
        while (k > 0 && !s.empty() && s.top() > c)
        {
            s.pop();
            k--;
        }
        s.push(c);
    }

    // Phase 2: If we still need to remove digits (e.g., input was "123")
    while (k > 0 && !s.empty())
    {
        s.pop();
        k--;
    }

    // Phase 3: Move from stack 's' to 'temp' to reverse the order manually
    stack<char> temp;
    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    // Phase 4: Build the string and skip leading zeros
    string result = "";
    bool leadingZero = true;

    while (!temp.empty())
    {
        char current = temp.top();
        temp.pop();

        // Only start adding to result if we encounter a non-zero
        // or if we've already started the number
        if (leadingZero && current == '0')
        {
            continue;
        }
        else
        {
            leadingZero = false;
            result += current;
        }
    }

    // Phase 5: Final check
    if (result == "")
    {
        return "0";
    }

    return result;
}

int main()
{
    string num;
    int k;

    cout << "Enter a string: ";
    cin >> num;
    cout << "Enter k: ";
    cin >> k;

    string ans = remove_k_digits(num, k);
    cout << "Output: " << ans << endl;

    return 0;
}