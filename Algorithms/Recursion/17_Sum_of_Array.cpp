#include <iostream>
#include <vector>

using namespace std;

// Bottom-Up Approach :

// sum(arr,0,5) = arr[0] + sum(arr,1,5) = 3 + 20 = 23
// sum(arr,1,5) = arr[1] + sum(arr,2,5) = 4 + 16 = 20
// sum(arr,2,5) = arr[2] + sum(arr,3,5) = 2 + 14 = 16
// sum(arr,3,5) = arr[3] + sum(arr,4,5) = 6 + 8 = 14
// sum(arr,4,5) = arr[4] + sum(arr,5,5) = 8 + 0 = 8
// sum(arr,5,5) = 0;
// Base Case : When index == Size.

// sum(arr,index,n) = arr[index] + sum(arr,index+1,n)
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)

int sum(vector<int> &arr, int index, int n)
{
    if (index >= n)
    {
        return 0;
    }
    return arr[index] + sum(arr, index + 1, n);
}

// Top-Down Approach (More Efficient because we passed less arguments)

// sum2(arr,4) = arr[4] + sum2(arr,3)  = 8 + 15 = 23
// sum2(arr,3) = arr[3] + sum2(arr,2)  = 6 + 9 = 15
// sum2(arr,2) = arr[2] + sum2(arr,1)  = 2 + 7 = 9
// sum2(arr,1) = arr[1] + sum2(arr,0)  = 4 + 3 = 7
// sum2(arr,0) = arr[1] + sum2(arr,-1) = 3 + 0 = 3
// sum2(arr,-1) = 0
// Base Case : Index becomes negative

// sum2(arr,n) = arr[n] + sum2(arr,n-1) where n is array.size()-1.
// We solve only 1 case and rest of the cases are handled with that.

// Time : O(n) , Space : O(n)
int sum2(vector<int> &arr, int n)
{
    if (n < 0)
    {
        return 0;
    }
    return arr[n] + sum2(arr, n - 1);
}

int main()
{
    vector<int> v = {3, 4, 2, 6, 8};
    // cout << sum(v, 0, v.size());
    // cout << sum2(v, v.size() - 1);
    return 0;
}