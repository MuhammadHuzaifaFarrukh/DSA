#include <iostream>
#include <vector>
using namespace std;

/*
A valid IP address consists of exactly four integers separated by single dots.
Each integer is between 0 and 255 (inclusive) and cannot have leading zeros.
For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
Given a string s containing only digits, return all possible valid IP addresses that can be formed by inserting dots into s. You are not allowed to reorder or remove any digits in s.
You may return the valid IP addresses in any order.

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Input: s = "0000"
Output: ["0.0.0.0"]

Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
*/

// This is a combination + partitioning question.
// We are making partitions at each iteration.
// We take the string and try cutting it into 4 parts.
// If we have successfully done , then we check if we have used up all the characters , or not.
// If we have used up all the characters then we save this answer , and backtrack to find the next one.
// Otherwise , we don't save this answer and backtrack as well.
// We can only cut into 3 digit numbers.
// While cutting , we have to check if this cutting is not exceeding the string size.
// We also check for the leading zeroes , and if the number cut out is greater than 255.

// Time Complexity :
// We have only 3 choices of cutting.
// Since we are trying all possible combinations of 1 to 3 digit numbers , tree's maximum level remains 3.
// We fix 1 number and fix 2 and fix 3 number , then we try to find the 4th partition in 3 different ways = 3.
// After this , we fix 3 number again with 2,3 digit values , then try to find the 4th partition again in 3 different ways = 3+6 = 9 = 3^2.
// After this , we fix 2 number with 2,3 digit values , and try to fix 3 number in 2,3 digit values and try to find the 4th partition in 3 different ways = 27 = 3^3.
// After this , we fix 1 number with 2,3 digit values , try to fix 2 number with 2,3 digit values , try to fix 3 number with 3 digit values and try to fix 4th number in 3 different ways = 81 = 3^4.
// The total number of nodes checked is bounded by 3^1 + 3^2 + 3^3 + 3^4 = 120 operations.
// Time : O(3^m) where m = min(n,12) , n = string length.
// Time : O(3^m) = O(1)

// Space Complexity :
// The maximum depth of the call stack is strictly 4 (one stack frame per IP segment). = O(1)
// The temporary string temp holds at most 15 characters (255.255.255.255). = O(1)
// The Output strings are always done at the leaf nodes (3^4 = 81) and each answer can be at most 15 , (81*15) so it is also bound by the 3^4 = O(1)
// Total Space : O(3^4 * 15) = O(1)

vector<string> restoreIpAddresses(string s)
{
    vector<string> ans;
    if (s.size() < 4 || s.size() > 12)
    {
        return ans;
    }
    string temp = "";
    find1(ans, temp, 0, 0, s);
    return ans;
}
void find1(vector<string> &ans, string temp, int index, int parts, string &s)
{
    if (parts == 4)
    {
        if (index == s.size())
        {
            temp.pop_back();
            ans.push_back(temp);
        }
        return;
    }

    for (int len = 1; len <= 3; len++)
    {
        if (index + len > s.size())
        {
            break;
        }

        string sub = s.substr(index, len);

        // This condition is required for leading zeroes and for the numbers that exceed 255.
        if ((sub.size() > 1 && sub[0] == '0') || stoi(sub) > 255)
        {
            continue;
        }
        find1(ans, temp + sub + ".", index + len, parts + 1, s);
    }
}

// Same as above but with string temp as reference string.
// We store the original size of the string at each level , and when we are about to backtrack , we revert back to the original size.
// Time : O(1)
// Space : O(1)
/*
void find2(vector<string> &ans, string &temp, int index, int parts, string &s)
{

    if (parts == 4)
    {
        if (index == s.size())
        {
            temp.pop_back();
            ans.push_back(temp);
            temp.push_back('.');
        }
        return;
    }

    int original = temp.size();

    for (int len = 1; len <= 3; len++)
    {
        if (index + len > s.size())
        {
            break;
        }

        string sub = s.substr(index, len);

        if ((len > 1 && sub[0] == '0') || stoi(sub) > 255)
        {
            continue;
        }

        temp += sub + ".";

        find2(ans, temp, index + len, parts + 1, s);
        temp.resize(original);
    }
}
*/
int main()
{
    string s = "25525511135";
    vector<string> ans = restoreIpAddresses(s);
    for (string s : ans)
    {
        cout << s << endl;
    }
    return 0;
}

// Recursive Tree :
/*
                            [ "255255" ]  (index 0, parts 0)
                                |
        +-----------------------+-----------------------+
        |                                               |
     P1: "2" (idx 1)                                P1: "25" (idx 2)
        |                                               |
  +-----+-----+                                   +-----+-----+
  |           |                                   |           |
P2: "5"     P2: "55"                            P2: "5"     P2: "52"
(idx 2)     (idx 3)                             (idx 3)     (idx 4)
  |           |                                   |           |
  +----+      +----+------+                       +----+      |
  |    |      |    |      |                       |    |      |
 P3:  P3:    P3:  P3:    P3:                     P3:  P3:    P3:
 "5"  "52"   "2"  "25"   "255"                   "2"  "25"   "5"
 (3)  (4)    (4)  (5)    (6)                     (4)  (5)    (5)
  |    |      |    |      |                       |    |      |
  |    |      |    |      ❌ Out of chars         |    |      |
  |    |      |    |      (Parts=3, idx=6)        |    |      |
  |    |      |    +----------+                   |    +----+ |
  |    |      |               |                   |         | |
 P4:  P4:    P4:             P4:                 P4:       P4:P4:
"255""55"    "55"            "5"                 "55"      "5""5"
 (6)  (6)    (6)             (6)                 (6)       (6)(6)
  |    |      |               |                   |         |  |
Yes   Yes    Yes             Yes                 Yes       Yes Yes
*/