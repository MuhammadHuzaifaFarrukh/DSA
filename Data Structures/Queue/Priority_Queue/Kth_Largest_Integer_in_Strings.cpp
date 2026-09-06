#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

/*
You are given an array of strings nums and an integer k. Each string in nums represents an integer without leading zeros.
Return the string that represents the kth largest integer in nums.
Note: Duplicate numbers should be counted distinctly. For example, if nums is ["1","2","2"], "2" is the first largest integer, "2" is the second-largest integer, and "1" is the third-largest integer.

Input: nums = ["3","6","7","10"], k = 4
Output: "3"
Explanation:
The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
The 4th largest integer in nums is "3".

Input: nums = ["2","21","12","1"], k = 3
Output: "2"
Explanation:
The numbers in nums sorted in non-decreasing order are ["1","2","12","21"].
The 3rd largest integer in nums is "2".

Input: nums = ["0","0"], k = 2
Output: "0"
Explanation:
The numbers in nums sorted in non-decreasing order are ["0","0"].
The 2nd largest integer in nums is "0".
*/

// We use Max Heap.
// Also for strings , if we put them and use stoi or to_string() that would get us TLE , since it would be lots of digits.
// Even stod() or stol() would fail.
// For strings , if we use pq with it , it compares in lexicographical order.
// Meaning , it would tell "97" > "233" because it compares for every character and then gives the answer instantly as soon as it finds the answer.
// So we make a comparator ourselves named 'String'.
// For Min-Heap greater<int>() is used , so we use the '>' sign in it.
// We check if both lengths are not equal then return the string with greater length.
// If both lengths are same , only then check them lexicographically character by character.
// Once we have made this comparator we can make our min-heap as :  priority_queue<string, vector<string>, String> pq.
// Then we push 'k' numbers into it.
// Then we check for (n-k) numbers in it using the same comparator 'String'.
// If we just checked using '>' , it would get the wrong answers like saying "97" > "233".
// So we use this comparator again.
// Time : O(kL + (n-k)*Llogk) or O(L + nLlogk)
// Space : O(kL) where 'L' is the max length of the string.
struct String
{
    bool operator()(const string &a, const string &b) const
    {
        if (a.length() != b.length())
        {
            return a.length() > b.length();
        }
        return a > b;
    }
};

string kthLargestNumber(vector<string> &nums, int k)
{
    priority_queue<string, vector<string>, String> pq(nums.begin(), nums.begin() + k);

    String comp;
    for (int i = k; i < nums.size(); i++)
    {
        if (comp(nums[i], pq.top()))
        {
            pq.pop();
            pq.push((nums[i]));
        }
    }
    return (pq.top());
}

// Using Binary Search here can cost more time than it did while finding kth largest in an integer array = O(nL*log(max-min)).
// While quickselect can be a bit optimal here as its average case can get us time to O(nL) and Space : O(logn). and its worst time will be O(n^2*L) and total space as : O(n)

int main()
{
    vector<string> v = {"233", "97"};
    int k = 1;
    cout << "Kth Largest Element : " << kthLargestNumber(v, k) << endl;
    return 0;
}