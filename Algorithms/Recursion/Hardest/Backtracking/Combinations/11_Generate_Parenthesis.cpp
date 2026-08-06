#include <iostream>
#include <vector>
#include <string>

using namespace std;

// For given 'n' , we need to generate all the valid parenthesis.
// For n = 3 :
// [ ((())) , ()()() , ( ()() ) , () (()) , (())()  ]
// So we have total 5 parenthesis valid for n = 3.
void Parenthesis(int n, int left, int right, string &temp, vector<string> &ans); // Forward Declaration

// We can see that for valid parenthesis for any 'n', number of closing parenthesis  <= number of opening parenthesis and sum of opening / closing parenthesis is equal to 2n.
// We try to generate all the parenthesis combination in the same way as a choice of yes or no.
// For yes choice we take left parenthesis and checking if its less than 'n' or not.
// For no choice we take the right parenthesis and checking it must be less than left one otherwise it won't generate valid parenthesis.

// If we see this n = 3 , we get 5 answers.
// Observing this series gives us the series of Catalan Numbers Cn = C(2n,n)

// Time Comp :
// If we see , our structure again becomes like a binary tree with some nodes left out.
// But if we don't neglect them it becomes a total binary tree structure with time comp approx = 2^n.
// But we can see that we find our valid parenthesis at length of 2n for any 'n' branch so 2(2^n) = 4^n.

// Space :
// The tree structure goes upto maximum length of '2n' which becomes O(2n) = O(n).
// The temp string holds at most 2n characters = O(2n) = O(n)
// The Ans array takes all of the valid parenthesis which are total Catalan Numbers.
// Size of each row inside our answer array is 2n.
// So Ans total space is 2n*Cn = O(2n*Cn) = O(n*Cn)
// Total Space : O(n*Cn) + O(n) + O(n) = O(n*Cn)

// Time Comp = O(4^n) (neglecting the pushback of the temp into ans).
// Exact Time Comp : O(Cn) where Cn is the Catalan Number , so O(4^n / n^(1.5) )
// Space : O(n*Cn) or maybe O(n*4^n) is approximation
vector<string> generateParenthesis(int n)
{
    vector<string> ans;
    string temp = "";
    Parenthesis(n, 0, 0, temp, ans);
    return ans;
}
void Parenthesis(int n, int left, int right, string &temp, vector<string> &ans)
{
    if (left + right == 2 * n) // We can also write temp.size() == 2*n as base case
    {
        ans.push_back(temp);
        return;
    }
    if (left < n) // This check is must since the count of left '(' cannot exceed 'n'.
    {
        temp.push_back('(');
        Parenthesis(n, left + 1, right, temp, ans);
        temp.pop_back();
    }
    if (right < left) // This checks if right ')' can be added or not.
    {
        temp.push_back(')');
        Parenthesis(n, left, right + 1, temp, ans);
        temp.pop_back();
    }
}

int main()
{
    int n = 3;
    vector<string> ans = generateParenthesis(n);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}