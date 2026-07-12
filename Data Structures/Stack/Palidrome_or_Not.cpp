#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 1) We can use Two Pointer Approach by start = 0 , end = string.size()-1.
// Time : O(n/2) = O(n) , Space : O(1)
// Most Optimized.
/*
bool isPalindrome(const string &s)
{
    int start = 0, end = s.size() - 1;
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return 0;
        }
        start++;
        end--;
    }
    return 1;
}
*/

// 2) We use stack to store all the elements and then check the string in reversed order.
// Time : O(n) , Space : O(n)
bool isPalindrome(const string &s)
{
    stack<char> st;

    // Step 1: Push all characters onto the stack
    for (char ch : s)
    {
        st.push(ch);
    }

    // Step 2: Compare the string from the beginning with the stack elements
    for (char ch : s)
    {
        // st.top() gives us the string in reverse order
        if (ch != st.top())
        {
            return false; // Mismatch found, not a palindrome
        }
        st.pop(); // Move to the next element in the stack
    }

    return true; // All characters matched
}

// We use stack to push half elements into stack and then compare with the other half.
// Time : O(n) , Space : O(n/2) = O(n)
bool isPalindromeOptimized(const string &s)
{
    int n = s.length();
    if (n <= 1)
        return true;

    stack<char> st;
    int mid = n / 2;

    // Step 1: Push only the first half onto the stack
    for (int i = 0; i < mid; i++)
    {
        st.push(s[i]);
    }

    // Step 2: Determine where the second half starts
    // If length is odd, skip the exact middle character
    int startIndex;
    if (n % 2 == 0)
    {
        int startIndex = mid;
    }
    else
    {
        int startIndex = mid + 1;
    }

    // Step 3: Compare the second half directly with the stack
    for (int i = startIndex; i < n; i++)
    {
        if (s[i] != st.top())
        {
            return false; // Mismatch found
        }
        st.pop();
    }

    return true;
}

int main()
{
    string word = "radar";
    cout << isPalindromeOptimized(word) << endl;
    return 0;
}