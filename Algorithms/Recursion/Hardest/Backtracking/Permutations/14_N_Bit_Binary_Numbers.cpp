#include <iostream>
#include <string>
#include <vector>

using namespace std;

// We have to print binary bitstrings for 'n' input.
// E.g If n = 3 then output must be : [ "000", "001", "010" , "011" , "100" , "101" , "110" , "111"]
// Total combinations 2^n

// So we will use the combination generation mechanism.
// Our first choice is zero and 2nd choice is One.
// We keep calling functions until temp reaches size of 'n'.
// Then we store it in our answer array and backtrack.
/*
""
               /      \
            "0"        "1"
           /   \      /   \
        "00"  "01"  "10"  "11"
*/

// Time Complexity :
// There are total 2^n nodes.
// Work done in each node is constant (if we neglect the push_back() for string into a vector which can take 'n' at worst time).
// So total time : O(2^n) neglecting the push_back.

// Space Complexity :
// Max depth of the tree goes upto 'n' so space becomes O(n)
// Space in this max depth each node is constant.
// Including answer array which contains 2^n total answers and each answer row is of 'n' size takes O(n*2^n) space.
// So total space : O(n*2^n).

// Actually these are the permutations if we look , "01" and "10" are considered different only in permutation.
// This is permutation with repetition allowed.
// However there are only 2 choices at each step , we write those choices ourselves instead of doing it in a for loop.
void generateNBitStrings(int n, vector<string> &ans, string &temp)
{
    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }

    temp.push_back('0');
    generateNBitStrings(n, ans, temp);
    temp.pop_back();

    temp.push_back('1');
    generateNBitStrings(n, ans, temp);
    temp.pop_back();
}

// Follow-up :
/*
Same question but now we want that 0001 be as 1 and 0010 as 10 meaning that we trail out the left most zeroes.
So for that we can just make changes in our base case.
Base case remains same but we will use a loop each time we go on base case to see where does the first '1' start.
When we find its index , we can just get that substring till the end.

if (temp.size() == n)
    {
        // 1. Find the index of the first '1'
        int i = 0;
        while (i < n && temp[i] == '0')
        {
            i++;
        }

        // 2. If all characters are '0', push "0", otherwise push substring starting from first '1'
        if (i == n)
        {
            ans.push_back("0");
        }
        else
        {
            ans.push_back(temp.substr(i)); // Strips leading zeros!
        }
        return;
    }
// string.substr(int) will extract everything starting from index i all the way to the end of the string.
// If we wrote our program like this then :
// Time complexity :
There are total 2^n nodes.
If we neglect push_back , the work done in base cases is 'n' times finding the index and also using the substr() function adds a load of 'n' times and more.
Seeing this total time becomes O(n*2^n).

// Space Complexity :
Space taken in max depth is 'n' and in those nodes is constant so space here is O(n)
Total space taken by answer array is rows*cols:
Total rows will be 2^n.
At worst the answer array will have 'n' bit strings.
So total space by answer array : n*2^n.
Space : O(n*2^n)
*/

int main()
{
    int n;
    cout << "Enter n : ";
    cin >> n;

    vector<string> ans;
    string temp = "";
    generateNBitStrings(n, ans, temp);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}