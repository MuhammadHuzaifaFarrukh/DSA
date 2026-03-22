#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

string removeKdigits(string num, int k)
{
    string stack = "";      // Using string as a stack
    int n = num.length();

    for (int i = 0; i < n; i++)
    {
        char current = num[i];

        // While current digit is smaller than the top of stack,
        // and we still need to remove digits (k > 0)
        while (k > 0 && !stack.empty() && stack.back() > current)
        {
            stack.pop_back();
            k--;
        }
        stack.push_back(current);
    }

    // If we still have k left (e.g., input "1234"), remove from the end
    while (k > 0 && !stack.empty())
    {
        stack.pop_back();
        k--;
    }

    // Handle leading zeros: find where the first non-zero digit is
    int firstNonZero = 0;
    while (firstNonZero < stack.length() && stack[firstNonZero] == '0')
    {
        firstNonZero++;
    }

    // Extract the substring from the first non-zero digit
    string result = "";
    for (int i = firstNonZero; i < stack.length(); i++)
    {
        result += stack[i];
    }

    return result == "" ? "0" : result;
}

int main()
{
    int k;
    cout << "Enter k : ";
    cin >> k;
    cin.ignore();

    string s;
    cout << "Enter string : ";
    getline(cin, s);

    s = removeKdigits(s, k);
    cout << "Answer : " << s << endl;
    return 0;
}