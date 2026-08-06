#include <iostream>
#include <vector>

using namespace std;

/*
We have to store the sum of all the subsets of a given array.
// E.g : [1,2,3] ->[(),(1),(2),(3),(1,2),(2,3),(1,3),(1,2,3) ]
// So the Sums are : [0,1,2,3,3,5,4,6] for each set of sets.
*/

// We generate all the subsets using the choice of yes or no logic.
// For choice of no : We just send it as it is with index + 1.
// For choice of yes : We send it as the next index along included the sum of this number.
// This is not a specific nCr , this is a powerset.
// The Powerset contains all the nCr like nC0 + nC1 + ... + nCn without any repetition.

// For time comp we have generate a binary tree structure with work done in each node is constant.
// Total nodes will be our time taken.
// Level 0 : 1 , Level 1 : 2 , Level 2 : 4 , Level 3 : 8 and so on.
// 1 + 2 + 4 + 8 +...+ 2^n = 2^(n+1) - 1 = O(2^n)

// The Maximum depth of this binary tree goes upto 'n' for n length subsets and space taken in each nodes or levels is also constant.
// So total space is the maximum depth of the tree = O(n)
// Time : O(2^n) if we neglect the pushback time
// Space : O(n)
void printSubsetSum(vector<int> &arr, int index, int n, vector<int> &ans, int sum)
{
    if (index == n)
    {
        ans.push_back(sum);
        return;
    }
    printSubsetSum(arr, index + 1, n, ans, sum);              // Choice of No
    printSubsetSum(arr, index + 1, n, ans, sum + arr[index]); // Choice of Yes as we included the sum.
}

int main()
{
    vector<int> v = {1, 2, 3};
    vector<int> ans;
    printSubsetSum(v, 0, v.size(), ans, 0);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    return 0;
}