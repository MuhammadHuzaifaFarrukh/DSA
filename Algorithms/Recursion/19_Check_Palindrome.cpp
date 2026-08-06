#include <iostream>
#include <string>

using namespace std;

// Top-Down Approach Better here :
// We used two pointer approach but in recursive way
// We check if our start and end indexed are same or not.
// If they match then we go on to check next indices.
// If not then we return 0.
// When start >= end , it means we have checked correctly till half so the other half must be same and it must be palindrome.

// isPalindrome(s,0,6) = Comparison + isPalindrome(s,1,5) = Yes
// isPalindrome(s,1,5) = Comparison + isPalindrome(s,2,4) = Yes
// isPalindrome(s,2,4) = Comparison + isPalindrome(s,3,3) = Yes
// isPalindrome(3,3) = Yes its a palindrome
// Base Case : When start and end are same.
// isPalindrome(s,start,end) = isPalindrome(s,start+1,end-1).

// Time : O(n/2) = O(n) , Space : O(n/2) = O(n)
bool isPalindrome(const string &s, int start, int end)
{
    if (start >= end)
    {
        return 1;
    }

    if (s[start] != s[end])
    {
        return 0;
    }
    return isPalindrome(s, start + 1, end - 1);
}

int main()
{
    string s = "racecar";
    cout << "Palidrome ? " << isPalindrome(s, 0, s.size() - 1) << endl;
    return 0;
}