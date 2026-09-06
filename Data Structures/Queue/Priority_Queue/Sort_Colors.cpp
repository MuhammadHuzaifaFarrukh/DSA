#include <iostream>
#include <queue>

using namespace std;

/*
You are given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.
We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
You must solve this problem without using the library's sort function.

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
Explanation:
The array has two 0s, two 1s, and two 2s. Sorting them in-place places all 0s first, then all 1s, then all 2s.

Input: nums = [2,0,1]
Output: [0,1,2]
Explanation:
The array has one each of 0, 1, and 2, arranged in-place in the order 0, 1, 2.
*/

// 1) Sort the Array using any sorting algorithm.
// Time : O(n^2) O(nlogn)
// Space : O(n) or O(logn) or O(1) depending on the sorting algorithm used.

// 2) We use counting sort here.
// Time : O(n)
// Extra Space : O(3) = O(1)
// Total Space : O(1)
void sortColors(vector<int> &nums)
{
    vector<int> count(3, 0);
    for (int i = 0; i < nums.size(); i++)
    {
        count[nums[i]]++;
    }

    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            nums[k++] = i;
        }
    }
}

// 3) We can do this using priority queue ,
// Still it takes O(nlogn) time and O(n) space.
void sortColors2(vector<int> &nums)
{
    priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());

    int i = 0;
    while (!pq.empty())
    {
        nums[i++] = pq.top();
        pq.pop();
    }
}

// The Best Method : (Use DNF Algorithm)
// void sortColors(vector<int> &nums)
// {
//     int low = 0;
//     int mid = 0;
//     int high = nums.size() - 1;

//     while (mid <= high)
//     {
//         if (nums[mid] == 0)
//         {
//             // Found a Red: Swap it to the front
//             swap(nums[low], nums[mid]);
//             low++;
//             mid++;
//         }
//         else if (nums[mid] == 1)
//         {
//             // Found a White: It's in the right place, just move forward
//             mid++;
//         }
//         else
//         { // nums[mid] == 2
//             // Found a Blue: Swap it to the back
//             swap(nums[mid], nums[high]);
//             high--;
//             // NOTE: We don't increment mid here because the swapped
//             // element from 'high' needs to be checked!
//         }
//     }
// }

//
int main()
{
    vector<int> v= {2,2,2,1,0,1,1};
    
    return 0;
}