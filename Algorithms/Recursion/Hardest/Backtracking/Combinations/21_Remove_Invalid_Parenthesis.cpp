#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

/*
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
Return a list of unique strings that are valid with the minimum number of removals.
You may return the answer in any order.

Input: s = "()())()"
Output: ["(())()","()()()"]

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]

Input: s = ")("
Output: [""]
*/

// We use backtracking and some maths.
// First we see when a string is valid parenthesis , its left and right parenthesis counts are equal.
// So we maintain a counts variable to check if its count is equal it means its valid parenthesis.
// If count ever gets < 0 it means right parenthesis are more than the left ones so it will always be invalid so we prune from there.
// But here if we generate all the valid parenthesis tree out of an invalid parenthesis string, it may generate some duplicate valid strings , however we want only 1.
// So we can use a set for that.
// One way would be generating all the valid parenthesis and then getting only those that are not duplicate using set, but again we might end up generating those parenthesis also like () , ()(), out of a string (()().
// But we are asked to remove minimum number of parenthesis so we can only choose (()) out of (()() not this ().
// So for that we maintain a maxlen variable so that if curr string made has a size more than maxlen it means we've found a valid parenthesis that is obtained by removing even more minimal parenthesis and so we clear up the set and push it into our set.
// Otherwise if both sizes are same, we push the string inside the set. (We could just again generate all the possible balanced parenthesis using count and then in the main() we select those in our vector which are of maxlen however that would take again more time which is a good pruning).
// Also if we encounter alphabets , we just push them , recurse with next index only , and then pop the alphabet (Backtrack) and return from there , not go further in that branch.
// Otherwise if we don't return , it will just go through the last else e.g ")(f" where it takes the else part of the brackets checking part and then takes the path where we are actually skipping.
// After this we take a choice of taking this parenthesis or skipping it.
// If we take it then we add +1 for left parenthesis and -1 for right parenthesis in the count.
// Once we have every string in our set we just add all them in a vector and return.
// So we only add into our answer, if i==size and count==0, the other pruning of maxlen is only done for optimization otherwise we can also generate all possible parenthesis of maxlen 2,4, ... and then select maxlen parenthesis in the main loop but that wouldn't be an efficient approach.

// Time Complexity :
// 2^n total possible leaf nodes = O(2^n)
// At each successful leaf node, we store it inside set, set computes hash (worst case O(n)) and then insert the string char by char taking 'n' time.
// Total time : O(n*2^n)

// Space Complexity :
// Recursive space : Tree depth goes at max 'n' string size : O(n)
// Temporary string : Goes at max 'n' = O(n)
// The answer set / vector storing all those n-sized 2^n strings = O(n*2^n)
// Total Space : O(n*2^n)

// This is a combination question with only 2 choices as our order doesn't matter, only the strings that we selected matter.
// Its also not catalan number (Cn ) because we aren't generating the valid parenthesis from scratch , we are using the string given to us only and only taking 2 choices from it (ignoring alphabets).
void traverse(string &s, int i, string &curr, unordered_set<string> &ans, int count, int &maxlen);
vector<string> removeInvalidParentheses(string s)
{
    unordered_set<string> ans;
    int maxlen = 0;
    string temp = "";
    int count = 0;
    traverse(s, 0, temp, ans, 0, maxlen);
    return vector<string>(ans.begin(), ans.end());
}

void traverse(string &s, int i, string &curr, unordered_set<string> &ans, int count, int &maxlen)
{
    if (count < 0)
    {
        return;
    }
    if (i == s.size())
    {
        if (count == 0)
        {
            if (curr.size() > maxlen)
            {
                maxlen = curr.size();
                ans.clear();
                ans.insert(curr);
            }
            else if (curr.size() == maxlen)
            {
                ans.insert(curr);
            }
        }
        return;
    }

    if (s[i] != '(' && s[i] != ')')
    {
        curr.push_back(s[i]);
        traverse(s, i + 1, curr, ans, count, maxlen);
        curr.pop_back(); // Backtrack
        return;
    }

    // Check if it is left or right parenthesis for +1 or -1 addition in the balance count
    if (s[i] == '(')
    {
        curr.push_back(s[i]);
        traverse(s, i + 1, curr, ans, count + 1, maxlen); // Take (
        curr.pop_back();
        traverse(s, i + 1, curr, ans, count, maxlen); // Skip )
    }
    else // s[i]==')'
    {
        curr.push_back(s[i]);
        traverse(s, i + 1, curr, ans, count - 1, maxlen); // Take )
        curr.pop_back();
        traverse(s, i + 1, curr, ans, count, maxlen); // Skip )
    }
}

int main()
{
    string s = "()())()";
    vector<string> ans = removeInvalidParentheses(s);
    for (string x : ans)
    {
        cout << x << "  ";
    }
    return 0;
}

/*
TOP-TO-BOTTOM HIERARCHICAL RECURSION TREE FOR s = "(()()"
Root (Level 0): i = 0, char = '('
                       [ curr = "", count = 0 ]
                              /        \
               Include '('   /          \   Exclude '('
                            v            v
Level 1: i = 1, char = '('
       [ curr = "(", count = 1 ]      [ curr = "", count = 0 ]
              /          \                   /          \
  Inc '('    /            \ Exc '('  Inc ')'  /            \ Exc ')'
            v              v                  v              v
Level 2: i = 2, char = ')'
   [ curr = "((", cnt=2 ]  [ curr = "(", cnt=1 ]  [ curr = "(", cnt=1 ]  [ curr = "", cnt=0 ]
       /        \              /        \              /        \              /        \
  Inc ')'      Exc ')'    Inc ')'      Exc ')'    Inc ')'      Exc ')'    Inc ')'      Exc ')'
     v            v          v            v          v            v          v            v
Level 3: i = 3, char = '('
[ curr="(()",  [ curr="((",   [ curr="()",   [ curr="(",   [ curr="()",   [ curr="(",   [PRUNED]     [ curr="",
  cnt=1 ]        cnt=2 ]        cnt=0 ]        cnt=1 ]        cnt=0 ]        cnt=1 ]     cnt < 0        cnt=0 ]
   /    \          /    \         /    \         /    \         /    \         /    \                      /    \
Inc      Exc     Inc     Exc    Inc     Exc    Inc     Exc    Inc     Exc    Inc     Exc                  Inc    Exc
 v        v       v       v      v       v      v       v      v       v      v       v                    v      v

Level 4 & 5 (BRANCHING DOWN TO LEAVES / BASE CASES):
* Notable valid paths of maximum length (maxlen = 4) found in this tree:
  1. Path via `Exc(s[0]), Inc(s[1]), Inc(s[2]), Inc(s[3]), Inc(s[4])` -> curr = "()()" [VALID, len = 4]
  2. Path via `Inc(s[0]), Inc(s[1]), Exc(s[2]), Inc(s[3]), Inc(s[4])` -> curr = "()()" [VALID, len = 4]
  3. Path via `Inc(s[0]), Exc(s[1]), Inc(s[2]), Inc(s[3]), Inc(s[4])` -> curr = "(())" [VALID, len = 4]
* Invalid/Pruned paths: Multiple branches with mismatched `count != 0` or dead paths caught by `count < 0` (like standalone closing brackets at the start).
*/