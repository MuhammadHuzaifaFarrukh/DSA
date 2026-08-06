#include <iostream>
#include <vector>

using namespace std;

// Top-Down Approach :
// We apply the two pointers same as binary search :

// binarySearch(arr,0,5,5) = Comparisons + binarySearch(arr,3,5,5) = 3
// binarySearch(arr,0,3,5) = Comparisons + binarySearch(arr,3,3,5) = 3
// binarySearch(arr,3,3,5) = Return the Answer above if Found , otherwise keep going
// Base Case : When start pointer goes ahead of end pointer.

// binarySearch(arr,start,end,target) = Comparisons + binarySearch(arr, mid+1 , mid-1 ,target)
// Or we can also write it as :
// T(n) = 1 + T(n/2) where n shows the size of array being half at each step.
// T(n/2) = 1 + T(n/4) = 1 + 1 + T(n/8) = 2 + T(n/8)
// T(n/4) = 1 + T(n/8)
// T(n) = 1 + 2 + T(n/8) = 3 + T(n/8) = 3 + T(n/2^3)
// T(n) = k + T(n/2^k)
// Put n/2^k = 1 , 
// n = 2^k
// logn  = k or k = logn
// T(n) = logn + T(1) = logn + 1 = O(logn)

// Time : O(logn) , Space : O(logn)
int binarySearch(vector<int> &arr, int start, int end, int target)
{
    if (start > end)
    {
        return -1;
    }
    int mid = (start) + (end - start) / 2;
    if (arr[mid] == target)
    {
        return mid;
    }
    else if (arr[mid] < target)
    {
        return binarySearch(arr, mid + 1, end, target);
    }
    else
    {
        return binarySearch(arr, start, mid - 1, target);
    }
}

int main()
{
    vector<int> v = {1, 2, 4, 5, 7, 9};
    int target = 5;
    cout << " Element present at index : " << binarySearch(v, 0, v.size() - 1, target) << endl;

    return 0;
}