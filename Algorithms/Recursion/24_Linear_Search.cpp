#include <iostream>
#include <vector>

using namespace std;

// Linear Search
// Top-Down Approach :
// We find our index if target is present or not

// linearSearch(arr,6,4) = Comparison + linearSearch(arr,5,4) = 3
// linearSearch(arr,5,4) = Comparison + linearSearch(arr,4,4) = 3
// linearSearch(arr,4,4) = Comparison + linearSearch(arr,3,4) = 3
// linearSearch(arr,3,4) = Comparison + linearSearch(arr,2,4) = 3

// Base Case : When Index is negative

// linearSearch(arr,n,4) = Comparison + linearSearch(arr,n-1,4) where n is the array size - 1.

// Time : O(n) , Space : O(n)
int linearSearch(vector<int> &arr, int n, int target)
{
    if (n < 0)
    {
        return -1;
    }
    if (arr[n] == target)
    {
        return n;
    }
    return linearSearch(arr, n - 1, target);
}

int main()
{
    vector<int> v = {9, 7, 1, 4, 5, 2};
    int target = 4;
    cout << " Element present at index : " << linearSearch(v, v.size() - 1, target) << endl;

    return 0;
}