#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Given a positive integer n, generate all n-bit binary numbers such that,
for every prefix of each binary number, the count of 1's is greater than or equal to the count of 0's.
Input: n = 3
Output: ["111", "110", "101"]
Explanation: Valid numbers are those where each prefix has more 1s than 0s.
111: all its prefixes (1, 11, and 111) have more 1s than 0s.
110: all its prefixes (1, 11, and 110) have more 1s than 0s.
101: all its prefixes (1, 10, and 101) have more 1s than 0s.
So, the output is "111, 110, 101".
*/

// 1) Generate all the N-Bit binary numbers , and then at the base case for each , check the count 1s and 0s in it to decide to take this number or not.

// 2) We solve this using the same way we solved generating parenthesis.
// We take a choice of 1 or 0.
// We can take a choice of 1 as much as we want because for n = 3 : 111 is still valid (unlike generating parenthesis where we had to check left < n)
// So we can place the choice of 1 before or after 0.
// But for the choice of 0 , we need to check if the counts of zero is less than counts of 1s.
// If yes only then we take the choice of 0 (just like generating parenthesis right < left ).

// Time Complexity :
/*
For generating N Bit strings , we are generating atmost 2^n choices. (just an approximation because in the first step whole subtree of zero gets cutoff and even further branches).
So if we neglect time to push back :
Time : O(2^n)   or O(n*2^n) if we don't neglect time for push_back()

The exact number of valid strings generated for length n is given by the central binomial coefficient: n C (floor(n/2))
Using Stirling's Approximation , this becomes : 2^n / (sqrt(n)) excluding the push_back() time.
//
*/

// Space Complexity :
/*
Stack can go at max depth upto 'n' so extra space becomes at most : O(n)
Total strings are like n C (floor(n/2)) so solving it gives 2^n / (sqrt(n))
Each string has length 'n' so n*2^n / (sqrt(n)) = O(n*2^n / sqrt(n) )
*/

void nBitBinary(int n, vector<string> &ans, int zero, int one, string &temp)
{
    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }

    if (zero < one)
    {
        temp.push_back('0');
        nBitBinary(n, ans, zero + 1, one, temp);
        temp.pop_back();
    }

    temp.push_back('1');
    nBitBinary(n, ans, zero, one + 1, temp);
    temp.pop_back();
}

// Actually these are the permutations if we look , "110" and "101" are considered different only in permutation.
// This is permutation with repetition allowed.
// However there are only 2 choices at each step , we write those choices ourselves instead of doing it in a for loop.

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;
    vector<string> ans;
    string temp = "";
    nBitBinary(n, ans, 0, 0, temp);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}