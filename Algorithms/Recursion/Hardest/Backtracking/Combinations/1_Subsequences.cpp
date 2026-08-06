#include <iostream>
#include <vector>

using namespace std;

// Generate all subsequences (subsets / powersets / combinations) of a set.
// Like powerset (or combinations)
// E.g : [1,2,3] -> [ [1] , [2] , [3] , [1,2] , [1,3] , [2,3] , [1,2,3] , [] ]
//  We can return answer in any order.
// Even the internal order won't matter here like {1,3} = {3,1}.
// This is not a specific nCr , this is a powerset.
// The Powerset contains all the nCr like nC0 + nC1 + ... + nCn without any repetition.

// Iterative way :
// Might be difficult

/*
The Outer Loop (for (int num : nums)):
This loop runs exactly n, once for every element in the input array.
The Inner Loop (for (int i = 0; i < n; i++)):This loop steps through the current elements of ans and duplicates them.
The size of ans doubles with every iteration of the outer loop (1 2 4 8 ... ).
In the 1st outer iteration, the inner loop runs 1 time.
In the 2nd outer iteration, the inner loop runs 2 times.
In the 3rd outer iteration, the inner loop runs 4 times.
In the n-th outer iteration, the inner loop runs 2^(n-1) times.
If we add up all the iterations of the inner loop across the entire program, it runs a total of:
1 + 2 + 4 + 8 +...+ 2^(n-1) = 2^n - 1
// And each row of ans[i] can at max go to 'n'.
// So copying each row of ans[i] into temp can take 'n' time for each time inner loop runs, so total time for 2^n times approx takes : n*2^n.
// Time : O(n*2^n) or O(2^n) if we neglect the copying time of each row of ans[i] into temp.
*/

/*
Number of subsets: An array of size n has exactly 2^n subsets.
Our loop will perfectly generate all 2^n vectors inside ans.
Average size of a subset: Some subsets are empty, some have 1 element, and one has n elements.
On average, each subset contains exactly n/2 elements.
Multiplying the number of subsets by their average size gives:  2^n * n/2 = n*2^(n-1).
*/
// Space : O(n*2^n)
vector<vector<int>> generateSubsets(vector<int> &nums)
{
    vector<vector<int>> ans = {{}};

    for (int i = 0; i < nums.size(); i++)
    {
        int n = ans.size(); // Lock the current size so the loop doesn't run infinitely
        for (int i = 0; i < n; i++)
        {
            vector<int> temp = ans[i]; // Copy an existing subset
            temp.push_back(nums[i]);   // Add the current number
            ans.push_back(temp);       // Push it back into our answers
        }
    }
    return ans;
}

// Recursive Approach :
// We generate all the subsets by taking a particular choice.
/*
                                   ()
                             /              \
                           ()               (1)
                          /   \            /    \
                        ()    (2)         (1)    (1,2)
                        /\     /\         /  \       / \
                       () (3) (2)(2,3)   (1) (1,3)(1,2) (1,2,3)
*/
// If we say no , then we don't take a particular number and move on to the next index asking the same question.
// When we run out of the indices , then we backtrack.
// While backtracking , we then look for the 'yes' answers and for that we store our answer inside a temp array.
// For that 'yes' we can look for more 'no' or 'yes' if more indices left.
// We can pass temp vector by value , then it takes more memory and we can also pass it as a reference (for that we need to pop_back() as well cause changes are made in only same temp vector).
// temp vector stores our each subset , and when it reaches leaf node , we can push it in our ans vector.

// Time : O(n*2^n)
// This loop grows for n = 3 , level 0 : 1
// Level 1 : 2 , Level 2 : 4 , Level 3 : 8 = 2^3
// So we sum all work done in each nodes which is constant.
// Sum of all nodes : 1+2+4+8+...+2^n = 2^(n+1) - 1 = O(2^n)
// But copying 1D vector inside 2D vector takes O(n) at worst case or if reallocation happens.
// So its time comp becomes : n*2^n.
// If we neglect this push_back() operation as O(1) , then it takes time : O(2^n)

// Space : O(n*2^n)
// The maximum depth of the stack is n.
// When we look at the rightmost side , we can see all the yes answers , so temp stores our temporary one length increased in each level.
// So space taken  by temp in 'n' levels :
// 1 , 2, 3 , 4 ,....,n = O(n^2)
// Though this can be avoided and reduced to O(n) by using temp as reference vector.
// But Worst space taken for the subset can be atmost n by temp
// Our answer array stores upto 2^n powerset so we can suppose we have all the sets length n , then total space by 2D vector is :n*2^n and combining stack calls total space becomes : O(n*2^n) + O(n)
// Total Space : O(n*2^n)
// The technique used here is the DFS.
void subSet(vector<int> &nums, int index, int n, vector<vector<int>> &ans, vector<int> temp)
{
    if (index == n)
    {
        ans.push_back(temp);
        return;
    }
    subSet(nums, index + 1, n, ans, temp); // Choice of No
    temp.push_back(nums[index]);           // We stored this number , so we are taking it as a "YES" now
    subSet(nums, index + 1, n, ans, temp);
    // We can write temp.pop_back() here if we are using reference temp vector<> which saves memory and space.
}

// Recursion and Iterative approach both work at same time complexity for generation of combinations and almost same space.
// However writing code with recursive approach is a bit easier than iterative.

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    vector<vector<int>> ans;
    vector<int> temp;
    subSet(v, 0, v.size(), ans, temp);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

// Recurrence Relation Solving :
/*
The Recurrence Relation
Let's use T(k) to represent the time taken to process the remaining elements when our index is at a distance of k steps away from the base case n (which means k = n - index).
Every time we call the subSet function, our code does a tiny bit of constant work, which takes O(1) time, and makes two recursive calls to the next index. This drops the remaining steps from k down to k - 1.
So, the formula for a normal step is:
T(k) = 2 * T(k - 1) + O(1)

The Base Case
When k = 0 (which means our index is equal to n), we finally reach our base case. Inside this base case, our code copies the temp vector into our final ans vector.

Because we are passing temp by value in our function signature (vector temp), C++ is already making a brand new copy of temp at every single level of the recursion tree anyway. By the time we reach the very bottom of the tree at the base case, copying that temp vector into our answer list takes O(n) time in the worst case.
So, the exact time taken at the base case is:
T(0) = O(n)

Unrolling the Relation to Find Complexity
If we break down the formula T(n) = 2 * T(n - 1) + 1 step-by-step all the way down to the base case, a clear geometric pattern appears:

First step:
T(n) = 2 * T(n - 1) + 1

Second step:
T(n) = 2 * (2 * T(n - 2) + 1) + 1 = 4 * T(n - 2) + 2 + 1

Third step:
T(n) = 8 * T(n - 3) + 4 + 2 + 1

If we follow this multiplying pattern all the way down to the base case T(0), the equation expands into:
T(n) = (2^n * T(0)) + (2^(n-1) + 2^(n-2) + ... + 4 + 2 + 1)

Now we substitute our values into this pattern:
We know that T(0) is equal to O(n) because of the vector copying at the leaf nodes.
The second half of the equation (2^(n-1) + 2^(n-2) + ... + 1) is a geometric series that simply adds up to O(2^n).

Putting it together:
T(n) = 2^n * O(n) + O(2^n)

Since 2^n * n grows much faster than just 2^n, the smaller term drops out, leaving us with our final time complexity:
Total Time Complexity = O(n * 2^n)
*/