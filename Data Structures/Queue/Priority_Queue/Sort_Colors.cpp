#include <iostream>
#include <queue>

using namespace std;

// Can be done by writing our own sort function like bubble or selection or merge or quick sort -> O(n^2) or O(nlogn)
// Counting Sort (O(n) Time) but Space O(K) where K is the number of Unique Elements.
// Sorting method is not written here as using any sort will work.

// We can do this using priority queue , still it takes O(nlogn) time and O(n) space.

void sortColors(vector<int> &nums)
{

    priority_queue<int, vector<int>, greater<int>> pq;
    for (int num : nums)
    {
        pq.push(num);
    }

    int i = 0;
    while (!pq.empty())
    {
        nums[i++] = pq.top();
        pq.pop();
    }
}

// The Best Method : (Use DNF Algorithm)
void sortColors(vector<int> &nums)
{
    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;

    while (mid <= high)
    {
        if (nums[mid] == 0)
        {
            // Found a Red: Swap it to the front
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        }
        else if (nums[mid] == 1)
        {
            // Found a White: It's in the right place, just move forward
            mid++;
        }
        else
        { // nums[mid] == 2
            // Found a Blue: Swap it to the back
            swap(nums[mid], nums[high]);
            high--;
            // NOTE: We don't increment mid here because the swapped
            // element from 'high' needs to be checked!
        }
    }
}

//
int main()
{
    return 0;
}