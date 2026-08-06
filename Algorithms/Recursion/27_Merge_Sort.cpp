#include <iostream>
#include <vector>

using namespace std;

// Forward Declaration :
void merge(vector<int> &arr, int start, int mid, int end);

// Merge Sort (Divide & Merge ):
// We keep dividing the array until there is only 1 element left.
// When only 1 element is left , it is sorted.
// Now we go back and take 2 sorted arrays (even if length 1) and sort them.
// This sorting takes the time of O(Sum of the lengths of Arrays there).
// We keep bringing the sorted arrays upwards and keep joining them.
// For this we make a separate merge function that runs in O(a+b) where a = left part of array and b = right part of array.

/*
// Now for Time Complexity :
// Our Total Array size was 'n' and we kept dividing it :
                        n               -> Level 0
                     /     \
                  n/2       n/2         -> Level 1
                /    \      /  \
              n/4   n/4    n/4  n/4     -> Level 2
              and So on until we are left with 1 element only.

Maximum Depth of this tree is logn (total levels max can go upto logn).
Work Done in each node is not constant due to merge function.
We cannot find work done in each node separately.
We can find the work done at each level.
Let's take a look for n/4 (level 2).
When we are going upwards , the merge function takes 2 n/4 sorted arrays and merges them into worst time of n/2.
Similary the other 2 n/4 sorted arrays are also merged into n/2 array.
Total time taken for 4 n/4 sorted arrays to become 2 n/2 sorted arrays is n/4+n/4+n/4+n/4 = n.
Hence work done at level 2 is n.
Similarly work done at other levels while merge becomes n.
So Work done at each level takes time 'n'.
Total levels at max : logn
Multiply them we get : n*logn = O(nlogn)

// Recurrence Relation :
// T(n) = 2T(n/2) + Theta(n) where T(1) = Theta(1)
// T(n) = 2T(n/2) + cn where 'c' represents the constant cost.
// For T(n/2) = 2T(n/4) + c(n/2)
// T(n) = 2(2T(n/4) + c(n/2)) + cn
// T(n) = 2^2T(n/2^2) + 2cn
// T(n) = 2^kT(n/2^k) + k(cn)
Put n/2^k = 1 , we get :
// logn = k or k = logn
// T(n) = 2^logn*T(n/2^logn) + logn(cn)
// T(n) = (n)*T(n/n) + c(nlogn)
// T(n) = nT(1) + c(nlogn)
// T(n) = n + c(nlogn) = O(nlogn)

*/
/*
// Space Complexity :
We can see that stack goes into maximum depth for logn steps.
So for joining at last level elements , we create a temp array of size 2.
For joining elements of 2nd last level , we create a temp array of size 4.
If we keep this then for joining of elements of 1st level , we need to create a temporary array of size 'n'.
So this makes our worst case space comp at O(n).
We can see that maximum depth (levels) go upto logn but the temp array at that level is just of size 2 or n/2 or divided into much more.
But the array made for joining the elements at 1st level is of size 'n' so dominating term between 'n' and logn is total 'n' so our space is O(n).
We don't count how much space is taken at each level , instead we see how much max space our temp array can hold in any of the logn levels because other than that our space is constant for all levels.
*/
// Top-Down Approach

// Time : O(nlogn) , Space : O(n) , For Best / Avg / Worst case it remains same.
void mergeSort(vector<int> &arr, int start, int end)
{
    if (start == end)
    {
        return; // Return when there is single element , it is already sorted.
    }
    int mid = start + (end - start) / 2;
    mergeSort(arr, start, mid);   // Division from Left side
    mergeSort(arr, mid + 1, end); // Division from Right side
    merge(arr, start, mid, end);  // Merge and sort the sorted left and right halves.
}

// This gives us a sorted array from 2 sorted parts of the array.
// E.g if we had : [3,7,1,9] and now we give this function the parts : [3,7] and [1,9] , then it will :
// It will sort using two-pointer approach and give us [1,3,7,9]
// Time : O(a+b) , Space : O(a+b) where a is the left part of the array and b is the right part of the array.
void merge(vector<int> &arr, int start, int mid, int end)
{
    int left = start, right = mid + 1;
    int index = 0;
    vector<int> temp(end - start + 1);

    while (left <= mid && right <= end)
    {
        if (arr[left] <= arr[right])
        {
            temp[index] = arr[left];
            index++;
            left++;
        }
        else
        {
            temp[index] = arr[right];
            index++;
            right++;
        }
    }

    // If Left Portion is still left
    while (left <= mid)
    {
        temp[index] = arr[left];
        index++;
        left++;
    }

    // If Right Portion is still left
    while (right <= end)
    {
        temp[index] = arr[right];
        index++;
        right++;
    }

    // Fill Values into the Array from the temp array
    index = 0;
    while (start <= end)
    {
        arr[start] = temp[index];
        index++;
        start++;
    }
}
int main()
{
    vector<int> v = {6, 4, 7, 2, 9, 8, 3, 5};
    mergeSort(v, 0, v.size() - 1);
    cout << "Sorted Array : " << endl;
    for (int i : v)
    {
        cout << i << " ";
    }
    return 0;
}

/*
            6, 4, 7, 2, 9, 8, 3, 5
                    /       \
            6, 4, 7, 2      9, 8, 3, 5
                /  \           /   \
            6, 4   7, 2,    9, 8   3, 5
             / \    / \      / \    /  \
            6   4   7   2    9 8    3   5
Once the elements are single , they begin to backtrack and start to get sorted.

*/