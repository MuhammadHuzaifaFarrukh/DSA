#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
2->abc
3->def
4->ghi
5->jkl
6->mno
7->pqrs
8->tuv
9->wxyz
*/
// This is a combination question without repetition.

// 1) Using a For-Loop (usually we don't add for-loop in combinations)
// We maintain our map where we have the digits mapped to the alphabets.
// Then we call our Combination function which is gonna be recursive one.
// We take the first number and see what alphabets it represents say "234" , then we check '2' and then we see it is mapped to "abc".
// So now we are gonna iterate over "abc" and find the valid combinations by calling the same function but with index+1 for the next digits.
// Now it gets 3 and sees "def" are mapped , we try again and get 4 and see "ghi" are mapped to it.
// After our temp string becomes "adg" , we store it and since its of digits length , we return / backtrack and pop the last character.
// Now it becomes "ad" , now we see the next letter in the "ghi" which is 'h' and make another combination "adh".
// Again we make another combination "adi". Once "ghi" is over , it means we made all the combinations with "ad" , now we pop this and becomes "a".
// Now we use the next letter in the string "def" for "a" as "ae" and now start finding the combinations.

// Time Complexity :
// Every digit gives 3-4 choices.
// So if we have 'n' digits then we have 4*4*4*,...*4 (n times) = 4^n choices (nodes).
// Work done in each one is almost constant.
// Time : O(4^n) or O(n*4^n) if we count the time taken to copy the string.

// Space Complexity :
// Unordered map holds 8 values = O(1).
// Temp string grows at most 'n' = O(n)
// The maximum depth of the call stack is equal to the length of the input string, which is O(n).
// So space is O(n)
// If we include the answer space then answer holds upto 4^n rows and each row can be of 'n' size.
// So total space becomes : O(n*4^n).

vector<string> letterCombinations(string digits)
{
    unordered_map<int, string> m;
    m[2] = "abc";
    m[3] = "def";
    m[4] = "ghi";
    m[5] = "jkl";
    m[6] = "mno";
    m[7] = "pqrs";
    m[8] = "tuv";
    m[9] = "wxyz";
    vector<string> ans;
    string temp = "";
    Combinations(ans, temp, digits, m, 0);
    return ans;
}

void Combinations(vector<string> &ans, string &temp, string &digits, unordered_map<int, string> &m, int index)
{
    if (temp.size() == digits.size())
    {
        ans.push_back(temp);
        return;
    }

    string x = m[digits[index] - '0'];
    for (int i = 0; i < x.size(); i++)
    {
        temp.push_back(x[i]);
        Combinations(ans, temp, digits, m, index + 1);
        temp.pop_back();
    }
}

// 2) Typical method of combination questions :
// We take a choice of taking this alphabet by pushing it , and moving on to the next or skipping this one entirely and moving to the next letter.
// When we are going by taking an alphabet of a certain mapping , we are also watching the letterindex.
// Now once we've reached a alphabets of tempsize and stored , we backtrack and then try with the next letter of the same number if it exists otherwise we backtrack even more.

// Time : O(4^n) or O(n*4^n) if we count the time taken to copy the string.

// Space Complexity :
// Unordered map holds 8 values = O(1).
// Temp string grows at most 'n' = O(n)
// The maximum depth of the call stack is equal to the length of the input string, which is O(n).
// So space is O(n)
// If we include the answer space then answer holds upto 4^n rows and each row can be of 'n' size.
// So total space becomes : O(n*4^n).
vector<string> letterCombinations(string digits)
{
    unordered_map<int, string> m;
    m[2] = "abc";
    m[3] = "def";
    m[4] = "ghi";
    m[5] = "jkl";
    m[6] = "mno";
    m[7] = "pqrs";
    m[8] = "tuv";
    m[9] = "wxyz";

    vector<string> ans;
    string temp = "";
    Combinations(ans, temp, digits, m, 0, 0);
    return ans;
}

void Combinations(vector<string> &ans, string &temp, const string &digits, unordered_map<int, string> &m, int index, int letterIndex)
{

    if (temp.size() == digits.size())
    {
        ans.push_back(temp);
        return;
    }

    string x = m[digits[index] - '0'];

    if (letterIndex >= x.size())
    {
        return;
    }

    // Choice 1 : We use the next digit starting from letterIndex = 0.
    temp.push_back(x[letterIndex]);
    Combinations(ans, temp, digits, m, index + 1, 0);
    temp.pop_back();

    // Choice 2 : We use the same digit's next letter.
    Combinations(ans, temp, digits, m, index, letterIndex + 1);
}

int main()
{
    string digits = "234";
    vector<string> v = letterCombinations(digits);
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    return 0;
}
