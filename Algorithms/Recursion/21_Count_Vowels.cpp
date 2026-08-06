#include <iostream>
#include <string>

using namespace std;

// Top-Down Approach Better because we send less arguments :
// We start from the last of string , and check if its vowel or not and go towards index 0.
// We get our answer by checking this index and counting all the vowels from the previous characters.

// E.g : racecar
// vowels(s,6) = vowels(s,5) = 3
// vowels(s,5) = 1 + vowels(s,4) = 1 + 2 = 3
// vowels(s,4) = vowels(s,3) = 2
// vowels(s,3) = 1 + vowels(s,2) = 1 + 1 = 2
// vowels(s,2) = vowels(s,1) = 1
// vowels(s,1) = 1 + vowels(s,0) = 1 + 0 = 1
// vowels(s,0) = vowels(s,-1) = 0
// vowels(s,-1) = 0 (Return)

// vowels(s,n) = vowels(s,n-1) or 1+vowels(s,n-1) where n is the array size - 1.
// We solve for 1 character and it solves for the rest as well.

// Time : O(n) , Space : O(n)
int vowels(string s, int n)
{
    if (n < 0)
    {
        return 0;
    }
    if (s[n] == 'a' || s[n] == 'e' || s[n] == 'i' || s[n] == 'o' || s[n] == 'u')
    {
        return 1 + vowels(s, n - 1);
    }
    return vowels(s, n - 1);
}

int main()
{
    string s = "racecar";
    cout << "Vowels Count : " << vowels(s, s.size() - 1) << endl;
    return 0;
}