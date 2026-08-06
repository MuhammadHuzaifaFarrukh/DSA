#include <iostream>
#include <string>

using namespace std;

// Top-Down Approach :
// We use two pointer approach and reverse each start and end index value.

// reverse(s,0,6) = swap(0,6) + reverse(s,1,5)
// reverse(s,1,5) = swap(1,5) + reverse(s,2,4)
// reverse(s,2,4) = swap(2,4) + reverse(s,3,3)
// reverse(3,3) = Now Return
// Base Case : When start and end are same.

// reverse(s,start,end) = Swap(s[start],s[end]) + reverse(s,start+1,end-1)

// Time : O(n/2) = O(n)  , Space : O(n/2) = O(n)
void reverse(string &s, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    swap(s[start], s[end]);
}

int main()
{
    string s = "Slam";
    cout << "Reversed Word : " << s << endl;
    return 0;
}