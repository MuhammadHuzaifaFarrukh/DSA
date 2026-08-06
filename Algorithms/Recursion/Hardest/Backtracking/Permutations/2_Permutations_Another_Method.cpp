#include <iostream>
#include <string>
#include <vector>

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

/*
In this method we will use swapping because we have to make changes inside the given array.
For (1,2,3) , we have 3 choices so we will swap each index with first one so we can get 3 choices of (1,_,_) and (2,_,_) and (3,_,_).
Then at the next level , we have 2 choices to fix , so we will swap the next index with all the index other than previous past indices. like : for (1,2,3) , we swap 2 with 2 and 2 with 3 so we have 2 choices for this : (1,2,3) and (1,3,2).
We keep going to generate all the choices until the index becomes larger than array so we backtrack and we undo swapping also just like popped out value for undoing changes.
For these we send a starting index value first as 0 (starting of array).
Then the function calls start and we keep swapping with a value that we passing as index+1 for our next call.
(1,2,3) swaps 1 with 1 and then goes next to swap 2 with 2 and 3 with 3 and then it is saved in answer.
Then it backtracks to come at 3 with 3 but that loop ends , then it comes at 2 with 2 swap , it has still one more choice , so it swaps 2 with 3 in next iteration to make it (1,3,2).
After saving our answer (1,3,2) , this loop also ends and then we backtrack at swap 2 with 2 , then swap 1 with 1 , and now we will be at our first call which we made.
Now we swap 1 with 2 and repeat this whole process and similary after some backtracks , we swap 1 with 3 , thus we easily generate all the permutations by swapping the and fixing their positions.
We swapped 1 with 1 at first to keep its position fixed , then 1 with 2 , then 1 with 3 , and when we fixed 1 position , we repeat the whole process again , until the index is reached.
We also swap with the values of index increased by 1 so that swapping occurs from that index , not previous past indices.
Also after swapping and coming from a function call back we undo it by swapping once more.
Once fixing an element's position , we swap number of times excluding that element.
We can also say that at each level , there are approx n! swaps.

*/

/*Swapping in terms of index :
                             [1,2,3]                                -> 3!/3! = 6/6      (3P0)
        Swap 0 with 0       Swap 0 with 1       Swap 0 with 2       (3 Choices at first)
                  /            |                 \
            [1,2,3]         [2,1,3]            [3,2,1]              -> 3!/2! = 6/2      (3P1)
                Swap 1 with 1           Swap 1 with 2               (2 Choices for 2nd)
          /       \          /     \             /    \
        [1,2,3]  [1,3,2]  [2,1,3]   [2,3,1]   [3,2,1] [3,1,2]       -> 3!/1! = 6        (3P2)
                            Swap 2 with 2                           (1 Choices at the end)
        |         |         |        |           |     |
        [1,2,3]  [1,3,2]  [2,1,3]   [2,3,1]   [3,2,1]  [3,1,2]      -> 3!/0! = 6        (3P3)
*/

// Time Complexity :
/*
We traverse the array from index (0) to n for each value to be swapped.
At first level , 1 was swapped with 1,2 and 3.
Next level , 2 was swapped with 2 and 3.
Last Level , 3  was swapped with 3.
So on average we can say that the loop ran approx 'n' times for each value to be swapped.
So the time taken in each function call / value to be swapped was from that new index to n-1 approx -> O(n)
Total Nodes we have on average n! (although some being less in the upper levels)
Time Complexity : Total Node * Work in each Node = n!*n = O(n*n!)
*/

// Space Complexity :
/*
Space taken by our answer array is n!
Each row of our answer array is at max n.
Total Space becomes : O(n*n!)
No Auxiliary Space now.
*/

vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> ans;
    Permutations(nums, ans, 0, nums.size());
    return ans;
}

// We can just make the changes in same code to make it for nPk or generate all the permutations all the way from nP0 to nPn
void Permutations(vector<int> &nums, vector<vector<int>> &ans, int index, int n)
{
    // For any k nPk , just write temp.size() == k
    // We just wrote the below condition to save our temp answer like having a base case.
    // Otherwise if we don't write it , there's no issue and our code will also generate full tree structure but answer won't be saved here.
    // If we don't write this condition then we will have to save our answer inside the for loop and that would also save the partial permutations as well.
    // However for simplicity we usually write the condition of base case here and only write / save answer for cases if we want to save all the permutations or specific 'k'.
    if (index == n)
    {
        ans.push_back(nums);
        return;
    }
    for (int i = index; i < nums.size(); i++)
    {
        swap(nums[i], nums[index]);
        // vector<int> current_slice(nums.begin(), nums.begin() + index + 1);
        // ans.push_back(current_slice);
        // We can save nPn here as well , but that would break the simplicity of the code.
        // Saving here and not writing above is also fine and code runs well , but we maintain a structure to write base cases usually at the top or before.
        Permutations(nums, ans, index + 1, n);
        swap(nums[i], nums[index]);
    }
}

int main()
{
    vector<int> v = {1, 2, 3};
    cout << " Permutations : " << endl;
    vector<vector<int>> ans = permute(v);
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

// Recurrence Relation :
/*
The Swapping Recurrence Relation
For this problem, the work depends on how many elements we still have left to permute. Let's use m to represent the remaining elements available for swapping, where m = n - index.
When we call the Permutations function at a specific index, our code runs a loop that executes exactly m times (from i = index to i = nums.size() - 1).
Inside this loop, we do a constant amount of work for the two swap operations, and then we make a recursive call to process the remaining elements, which drops the count of remaining elements from m down to m - 1.
Because the loop spawns m separate recursive branches, our recurrence relation for a normal step is:
T(m) = m * T(m - 1) + O(m)
The O(m) term represents the work done by the loop itself, running m times and doing constant-time swaps during each iteration.

The Base Case
When m = 0 (which means our index is equal to n), we hit the base case at the top of our function. Inside this base case, we take our modified nums vector and copy it into our final ans vector.
Since the nums vector always contains exactly n elements, copying it takes O(n) time.
So, the exact time taken at the base case is:
T(0) = O(n)

Unrolling the Relation to Find Complexity
If we look at how this tree expands, it acts as a factorial multiplier:
At the top level (index 0), we have n choices, creating n branches.
At the next level (index 1), each of those branches creates n - 1 branches.
This continues all the way down until we have generated a total of n-factorial individual paths.

At the very bottom of each of these n-factorial paths, we hit our base case and spend O(n) time for each of the nodes. (loop traverse from index to n for each)
Putting it together, the total work spent at the leaf nodes is n-factorial multiplied by n, while the work spent on swaps inside the internal nodes of the tree is a smaller geometric fraction of that total.

This gives us our final time complexity:
Total Time Complexity = O(n * n-factorial)
*/