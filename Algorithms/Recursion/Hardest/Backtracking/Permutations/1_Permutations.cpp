#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Permutations (or Anagrams)
/*
Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// Here (1,2,3) and (1,3,2) are not the same even though the combination is same yet order matters.
*/
// In mathematics , permutation is of 'n' out of 'k' is represented as : nPk = n!/(n-k)!.
// We are here to generate all the nPn permutations , without repetitions.
// For all permutations we have : nP0 + nP1 + nP2 +...+ nPn = eN! where e is euler's constant.
// nPn actually represents also n! (Full Permutation)

void Permutations(vector<int> &nums, int n, vector<vector<int>> &ans, vector<int> &temp, vector<bool> &visited); // Forward Declaration

// We will use again the same choice technique inclusion-exclusion (DFS).
// We create a temp array to store our permutations.
// We also create a visited array so that it marks which numbers have been visited or not.
// Then we run a loop for numbers in array.
// Each loop iteration will check if visited is marked or not.
// If unmarked , then we mark it first and then we make our choice of selecting the first number.
// Then temp stores this and we make another function call , but now this time for i = 0 , it was marked check so it won't store the same value.
// Now it goes to next i = 1 , and sees it unchecked so it stores it and again runs the same function call.
// Each time the function call runs , it also checks if temporary array size is equal to our original array because each permutation size is same (n).
// So when that happens we store that in our answer and backtrack by returning and also popping the value and marking the visited as 0 because now we have checked and stored one path i.e {1,2,3}, now we go and check the other path as well.
// We keep going back i.e from {1,2,3} to {1,2} then {1} , and then we check another path of {1,3} then explore this one as well.
// Because once we selected [1, _ , _] , we had two choices , so we selected previously 2, now we select 3 to make it [1,3,_] and then exploring it.
// Now this runs and explores the path [1,3,2] and again backtracks.
// Once it does , it comes back to [1,3] and then [1].
// Then once a number is completed , our first iteration of for loop() ends and now it goes to the next number in the array i.e [2] and now it keeps exploring for [2] also.
/*
                             [_,_,_]                                -> 3!/3! = 6/6      (3P0)
                  /            |                 \
            [1,_,_]         [2,_,_]            [3,_,_]              -> 3!/2! = 6/2      (3P1)
          /       \          /     \             /    \
        [1,2,_]  [1,3,_]  [2,1,_]   [2,3,_]   [3,1,_] [3,2,_]       -> 3!/1! = 6        (3P2)
        |         |         |        |           |     |
        [1,2,3]  [1,3,2]  [2,1,3]   [2,3,1]   [3,1,2]  [3,2,1]      -> 3!/0! = 6        (3P3)
*/
// This resembles a tree like this for [1,2,3]
// At first we have 3 choices , then for each of the 3 choices we have 2 choices , and then we have only 1 choice.
// So total permutations are actually 3*2*1 = 6.
// Though the tree in actual may be bit more deeper , it can be visualized like above , how it explores each path.

// Time Complexity :
// We traverse the whole array in each node or in each function call (we just skipped parts due to being visited otherwise each value fixed / function call was being traversed from i = 0 to n-1)
// So total time will be n*total nodes.
// Now we need to know total nodes.
// At Level 0 , the number of nodes are the choices we have i.e 'n'.
// At level 1 , we have n-1 choices.
// At level 2 , we have n-2 choices.
// At level n-1 or n , we have only 1 choice or none.
// For each of the levels starting from n or n-1 , we have n! , then n! , then (n-1)! then (n-2)! nodes.
// So if we consider the nodes at last level as n! and other upper levels nodes having n! (although they are less than n!) , then we can say that total nodes in the whole tree are approx n!.
// So time will be O(n*n!)

// Space Complexity :
// Total Maximum Depth of this tree goes upto 'n' approx and all others are used as reference variables , so we can say our maximum depth is so recursive space used is O(n)
// We can see that the temp array can also atmost go upto the size 'n' and temp is also reference so it is only single vector used , not being copied in 'n' level times in all places.
// So at last level 'n' , the size of stack becomes n (stack) + n (temp) + n (bool array)  = 3n = O(n)
// But our answer array stores total of n! all permutations.
// For each permutation , it is of length 'n'.
// So space for our ans becomes : n*n!
// Total Space complexity therefore is : O(n*n!).
vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    vector<int> temp;
    vector<bool> visited(nums.size(), 0);
    Permutations(nums, nums.size(), ans, temp, visited);
    return ans;
}

// We can just make the changes in same code to make it for nPk or generate all the permutations all the way from nP0 to nPn
void Permutations(vector<int> &nums, int n, vector<vector<int>> &ans, vector<int> &temp, vector<bool> &visited)
{
    // For any k nPk , just write temp.size() == k
    // We just wrote the below condition to save our temp answer like having a base case.
    // Otherwise if we don't write it , there's no issue and our code will also generate full tree structure but answer won't be saved here.
    // If we don't write this condition then we will have to save our answer inside the for loop and that would also save the partial permutations as well.
    // However for simplicity we usually write the condition of base case here and only write / save answer for cases if we want to save all the permutations or specific 'k'.

    if (temp.size() == n)
    {
        ans.push_back(temp);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            visited[i] = 1;
            temp.push_back(nums[i]);
            // For saving all the permutations we can just write ans.push_back().
            // ans.push_back(temp)
            // We can save nPn here as well , but that would break the simplicity of the code.
            // Saving here and not writing above is also fine and code runs well , but we maintain a structure to write base cases usually at the top or before.
            Permutations(nums, n, ans, temp, visited);
            temp.pop_back();
            visited[i] = 0;
        }
    }
}

int main()
{
    vector<int> v = {1, 2, 3};
    vector<vector<int>> ans = permute(v);

    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }

    // There is also a C++ function std::next_permutation(v.begin(),v.end()); that gives the next permutation of the vector in the lexicographically (if it exists).
    /*
    do
    {
        for (int i : v)
        {
            cout << i << " ";
        }
        cout << endl;
    } while (next_permutation(v.begin(), v.end()));
    */

    return 0;
}

// Why Recursion is better than iterative for() loops for permutations ?
/*
Permutations of (1,2,3) using 3 Nested Loops :
If we have exactly 3 elements, we can write 3 nested loops.
Each loop represents choosing an element for position 1, position 2, and position 3.
While this is extremely simple and easy to understand, it has a fatal flaw:
It is not dynamic.
If the user suddenly inputs (1,2,3,4) our 3 nested loops will completely ignore the 4 because we need 4 nested loops to find permutations of size 4.
If the user inputs a vector of size n, we would need to write n nested loops.
Since we cannot dynamically generate nested loops at runtime based on an input variable, nested loops are practically useless for general-purpose code.

Recursion is essentially a mechanism that allows the computer to dynamically nest loops at runtime.
When our recursive function calls itself, it is pushing a new "virtual nested loop" onto the call stack.
If N=3, it calls itself 3 levels deep (3 nested loops). If N=10 it calls itself 10 levels deep (10 nested loops).

*/

// However there is an algorithm for finding the next permutation in O(n)
// Since there are total n! permutations , this will also take time : O(n*n!)
// But it saves us from the recursive stack approach of O(n) space , since it modifies in array , it is O(1) Space.
// Generating all the Permutations Iteratively

/*
 */
// Dictionary Algorithm :
/*
To get all permutations iteratively:
Sort the input array in ascending order.
This represents our very first permutation (e.g., [1, 2, 3]).
Repeatedly calculate the "Next Lexicographical Permutation" in-place using a loop until the array becomes sorted in descending order (the last permutation, [3, 2, 1]).

To find the immediate next permutation of any array (e.g., [1, 3, 5, 4, 2]):
Array: [ 1,  3,  5,  4,  2 ]
             ^
          1. Scan from right to left to find the first element that is smaller than the element to its right.
          Pivot (3) is the first element from the right that decreases.

Array: [ 1,  3,  5,  4,  2 ]
                         ^
                      2. Successor (4) is the smallest element on the right larger than 3.

Array: [ 1,  4,  5,  3,  2 ]
             ^-------^
          3. Swap Pivot and Successor.

Array: [ 1,  4,  2,  3,  5 ]
                 ^--------^
              4. Reverse everything to the right of the pivot's old index.
*/
// Implementation :
// Helper function: Finds the next permutation in-place.
// Returns false if we have reached the absolute last permutation.

/*
bool getNextPermutation(vector<int> &nums)
{
    int n = nums.size();
    if (n <= 1)
    {
        return false;
    }

    // Step 1: Find the first decreasing element from the right (the pivot)
    int i = n - 2;
    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }

    // If no such element is found, we are at the last permutation (e.g., [3, 2, 1])
    if (i < 0)
    {
        return false;
    }

    // Step 2: Find the smallest element to the right of the pivot that is larger than the pivot
    int j = n - 1;
    while (nums[j] <= nums[i])
    {
        j--;
    }

    // Step 3: Swap them
    swap(nums[i], nums[j]);

    // Step 4: Reverse the sequence after the pivot's index
    reverse(nums.begin() + i + 1, nums.end());

    return true;
}

vector<vector<int>> permuteIterative(vector<int> &nums)
{
    vector<vector<int>> ans;

    // 1. Start by sorting so we begin at the absolute lexicographical first state
    sort(nums.begin(), nums.end());

    // 2. Loop iteratively to capture each permutation state
    do
    {
        ans.push_back(nums);
    } while (getNextPermutation(nums));

    return ans;
}
*/