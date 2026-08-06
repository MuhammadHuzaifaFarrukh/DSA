#include <iostream>
#include <string>

using namespace std;

// Reverse string by these 2 formulas , both work :
// 1) Char - 32  Because 'a' -'A' = 32
// 2) 'A' + Char - 'a'

// lowertoUpper(s,3) = Capitalize + lowertoUpper(s,2)
// lowertoUpper(s,2) = Capitalize + lowertoUpper(s,1)
// lowertoUpper(s,1) = Capitalize + lowertoUpper(s,0)
// lowertoUpper(s,0) = Capitalize + lowertoUpper(s,-1)
// lowertoUpper(s,-1) = Return
// Base Case : When index becomes negative

// lowertoUpper(s,n) = Capitalize + lowertoUpper(s,n-1) where n is array.size()-1.

// Time : O(n) , Space : O(n)
void lowertoUpper(string &s, int n)
{
    if (n < 0)
    {
        return;
    }
    if ('a' <= s[n] && s[n] <= 'z')
    {
        s[n] = s[n] - 32;
    }
    lowertoUpper(s, n - 1);
}
int main()
{
    string s = "word";
    lowertoUpper(s, s.size() - 1);
    cout << "Uppercase : " << s;
    return 0;
}